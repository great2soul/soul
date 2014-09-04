class HashEntry;

class HashEntry {
private:
	int key;
	char* value;
	HashEntry* next;
public:
	HashEntry(int key, char* value) {
		this->key 	= key;
		this->value = value;
		this->next 	= null;
	}
	int getkey() {
		return this->key;
	}
	char* getvalue() {
		return this->value;
	}
	HashEntry *next() {
		this->next;
	}
};

const int TABLE_SIZE = 128;
class HashMap {
private:
	HashEntry** table;
	int hash(int key);
public:
	char* get(int key) {
		HashEntry *ptr = table[hash(key)];
		if (ptr->getkey() == key)
			return table[i]->getvalue();
		
		while(ptr->next()) {
			ptr = ptr->next();
			if (ptr->getkey() == key)
				return table[i]->getvalue();
		}
		return NULL;
			
	};
	void put(int key, char *value) {
		HashEntry *ptr = table[hash(key)];
		if (ptr) {
			ptr = new HashEntry(key, value);
		}
		while (ptr->next()) 
			ptr = ptr->next();
		ptr->next() = new HashEntry(key, value);
	}

	~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++)
              if (table[i] != NULL)
                    delete table[i];
        delete[] table;
      }
};