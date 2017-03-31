#include <cstdio>
#include <cstdlib>
#include <iostream>
const int HASH_BASE = 10001;
struct HashNode{
    int key;
    HashNode *next;
    Entry* data;
};
struct Entry{
    int key;
    int v;
    Entry* prev;
    Entry* next;
};
class LRUCache {
public:
    HashNode* hash[HASH_BASE];

    Entry* head;
    Entry* tail;
    int capacity;
    int curt_size;

    LRUCache(int capacity) {
        this.capacity = capacity;
        init();
    }
    
    int get(int key) {
        HashNode* node = hash_search(key);
        if(node != NULL && node->data != NULL){
            return node->data->v; 
        }
        return -1;
    }
    
    void put(int key, int value) {
        HashNode* node = hash_search(key);
        if(node == NULL){
            if(curt_size + 1 >= capacity && tail != NULL){
                HashNode* node = hash_delete(tail->key)
                entry_cut(tail);
            }
            HashNode* node = hash_insert(key);
            Entry* et = new Entry(key, value, NULL, NULL);
            node->data = et;
            entry_insert_front(et);
        }else{
            entry_update(node->data, value);
        }
    }

private:
    void init(){
        int i;
        for(i=0; i<HASH_BASE; i++) hash[i] = NULL;

        curt_size = 0;
        head = NULL;
        tail = NULL;
    }
    int hash_to(int key){
        if(key < 0) key = -key;
        return key % HASH_BASE;
    }
    HashNode* hash_search(int key){
        int h = hash_to(key);
        HashNode* node = hash[h];
        while(node != NULL && node->key != key) node = node->next;
        return node;
    }
    HashNode* hash_insert(int key){
        int h = hash_to(key);
        HashNode* node = new HashNode(key, hash[h], NULL);
        h[h] = node;
        return node;
    }
    HashNode* hash_delete(int key){
        int h = hash_to(key);
        HashNode* prev = NULL;
        HashNode* curt = hash[h];
        while(curt != NULL && curt->key != key){
            prev = curt;
            curt = curt->next;
        }
        if(curt != NULL){
            prev->next = curt->next;
            delete curt;
        }
        return curt;
    }
    Entry* entry_cut(Entry* et){
        if(et == NULL) return NULL;
        if(et == tail) {
            tail = et->prev;
            delete tail;
        }
        if(et->prev != NULL) et->prev->next = et->next;
        if(et->next != NULL) et->next->prev = et->prev;
        return et;
    }
    Entry* entry_insert_front(Entry* et){
        et->next = head;
        et->prev = NULL;
        if(head != NULL) head->prev = et;
        head = et;
        return et;
    }
    int entry_update(Entry* et, int v){
        Entry* old_et = entry_cut(et);
        int old_v = old_et->v;
        old_et->v = v;
        entry_insert(old_et);
        return old_v;
    }
};
