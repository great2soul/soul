// aes.h & aes_x86core.c & couple of other files are from openssl
#include "erl_nif.h"
#include "aes.h"
#include <memory.h>
#include <string.h>

static ERL_NIF_TERM aes_ecb_encrypt(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary in, out, key;
    unsigned char* to_encode;

    // First argument must be a binary key
    if(!enif_inspect_binary(env, argv[0], &key)) {
        return enif_make_badarg(env);
    }
    // Key size must be 16 bytes
    if(key.size != 16) {
        return enif_make_badarg(env);
    }
    // Second argument must be a binary
    if(!enif_inspect_binary(env, argv[1], &in)) {
    return enif_make_badarg(env);
    }

    // Pad with PKCS5Padding
    unsigned char padding =(unsigned char) (16 - in.size % 16);
    to_encode = (unsigned char*)malloc(sizeof(unsigned char) * in.size + padding);
    strncpy(to_encode, (unsigned char*)(in.data), in.size);
    int j = 0;
    for(j = 0; j < padding; j++) {
        to_encode[in.size + j] = padding;
    }
    // If allocation fails we return badarg because there is no API for general errors.
    if(!enif_alloc_binary(in.size + padding, &out)) {
        free(to_encode);
        return enif_make_badarg(env);
    }
    //Init the key
    struct aes_key_st* encrypt_key = (struct aes_key_st*)malloc(sizeof(AES_KEY));
    memset(encrypt_key, 0, sizeof(AES_KEY));
    AES_set_encrypt_key((unsigned char*)(key.data), 128, encrypt_key);
    //Encode!
    int i = 0;
    for(i = 0; i < in.size + padding; i += 16) {
        AES_encrypt((unsigned char*)&to_encode[i], (unsigned char*)&out.data[i], encrypt_key);
    }
    free(to_encode);
    free(encrypt_key);
    return enif_make_binary(env, &out);
}

static ERL_NIF_TERM aes_ecb_decrypt(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary in, out, key;
    // key must be binary
    if(!enif_inspect_binary(env, argv[0], &key)) {
        return enif_make_badarg(env);
    }
    // key size should be 16 byte
    if(key.size != 16) {
      return enif_make_badarg(env);
    }
    // cipher must be binary
    if(!enif_inspect_binary(env, argv[1], &in)) {
      return enif_make_badarg(env);
    }
    // cipher shoule be 16 byte block
    if(in.size % 16) {
      return enif_make_badarg(env);
    }

    unsigned char* decoded = (unsigned char*)malloc(sizeof(unsigned char)*in.size);

    struct aes_key_st* decrypt_key = (struct aes_key_st*)malloc(sizeof(AES_KEY));
    memset(decrypt_key, 0, sizeof(AES_KEY));
    AES_set_decrypt_key((unsigned char*)(key.data), 128, decrypt_key);

    int i = 0;
    for(i = 0; i < in.size; i += 16) {
      AES_decrypt((unsigned char*)&in.data[i], (unsigned char*)&decoded[i], decrypt_key);
    }
    //Remove padding
    unsigned char padding = (unsigned char) decoded[in.size-1];

    if(!enif_alloc_binary(in.size - padding, &out)) {
        free(decoded);
        free(decrypt_key);
        return enif_make_badarg(env);
    }

    strncpy((unsigned char*)out.data, decoded, in.size - padding);

    free(decoded);
    free(decrypt_key);
    return enif_make_binary(env, &out);
}

static ErlNifFunc nif_funcs[] =
{
    {"aes_ecb_encrypt", 2, aes_ecb_encrypt},
    {"aes_ecb_decrypt", 2, aes_ecb_decrypt}
};
ERL_NIF_INIT(util_aes,nif_funcs,NULL,NULL,NULL,NULL)