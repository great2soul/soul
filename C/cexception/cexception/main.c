//
//  main.c
//  cexception
//
//  Created by soul on 8/31/14.
//  Copyright (c) 2014 soul. All rights reserved.
//

#include <stdio.h>
#include "try_catch.h"

static void foo(int,int,int,int);
static void bar(void);

static jmp_buf jmpbuffer;
static int globval;

#define FOO_EXCEPTION (1)
#define BAR_EXCEPTION (2)
#define BAZ_EXCEPTION (3)

int main(int argc, const char * argv[])
{
//    int autoval;
//    register int regival;
//    volatile int volaval;
//    static int statval;
//    globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;
//    
//    if (setjmp(jmpbuffer) != 0) {
//        printf("after lonejmp:\n");
//        printf("globval=%d,autoval=%d,regival=%d,volaval=%d,statval=%d\n",
//               globval,autoval,regival,volaval,statval);
//        exit(0);
//    }
//    
//    // change values after setjmp before longjmp
//    globval = 101; autoval = 102; regival = 103; volaval = 104; statval = 105;
//    foo(autoval, regival, volaval, statval);
    
    //    do{
    //        jmp_buf ex_buf__;
    //        switch( setjmp(ex_buf__) ){
    //            case 0:
    //                while (1) {
    //                    printf("In Try Statement\n");
    //                    longjmp(ex_buf__, 1);
    //                    printf("I do not appear\n");
    //                    break;
    //                case 1:
    //                    printf("Got Foo!\n");
    //                    break;
    //                case 2:
    //                    printf("Got Bar!\n");
    //                    break;
    //                }
    //            default:
    //                printf("...et in arcadia Ego\n");
    //        }
    //    } while(0);

    TRY
    {
        printf("In Try Statement\n");
        THROW( BAR_EXCEPTION );
        printf("I do not appear\n");
    }
    CATCH( FOO_EXCEPTION )
        printf("Got Foo!\n");
    CATCH( BAR_EXCEPTION )
        printf("Got Bar!\n");
    CATCH( BAZ_EXCEPTION )
        printf("Got Baz!\n");
    FINALLY
        printf("...et in arcadia Ego\n");
    ETRY;
  
    return 0;
}

static void foo(int i, int j, int k, int l)
{
    printf("in foo:\n");
    printf("globval=%d,autoval=%d,regival=%d,volaval=%d,statval=%d\n",
        globval,i,j,k,l);
    bar();
}
static void bar(void)
{
    longjmp(jmpbuffer, 1);
}

