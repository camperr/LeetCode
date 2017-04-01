#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
const int HASH_BASE = 1000001;
struct Entry{
    int key;
    int v;
    Entry* prev;
    Entry* next;
    Entry(int key, int v, Entry* prev, Entry* next):key(key), v(v), prev(prev), next(next){}
};
struct HashNode{
    int key;
    HashNode *next;
    Entry* data;
    HashNode(int key, HashNode* next, Entry* data):key(key), next(next), data(data){}
};
class LRUCache {
public:
    HashNode* hash_table[HASH_BASE];

    Entry* head;
    Entry* tail;
    int capacity;
    int curt_size;

    LRUCache(int capacity) {
        this->capacity = capacity;
        init();
    }
    
    int get(int key) {
        HashNode* node = hash_search(key);
        if(node != NULL && node->data != NULL){
            entry_update(node->data, node->data->v);
            return node->data->v; 
        }
        return -1;
    }
    
    void put(int key, int value) {
        HashNode* node = hash_search(key);
        if(node == NULL){
            if(curt_size + 1 > capacity && tail != NULL){
                hash_delete(tail->key);
                Entry* et_del = entry_cut(tail);
                delete et_del;
                curt_size --;
            }
            HashNode* node = hash_insert(key);
            Entry* et = new Entry(key, value, NULL, NULL);
            node->data = et;
            entry_insert_front(et);
            curt_size ++;
        }else{
            entry_update(node->data, value);
        }
    }

private:
    void init(){
        int i;
        for(i=0; i<HASH_BASE; i++) hash_table[i] = NULL;

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
        HashNode* node = hash_table[h];
        while(node != NULL && node->key != key) node = node->next;
        return node;
    }
    HashNode* hash_insert(int key){
        int h = hash_to(key);
        HashNode* node = new HashNode(key, hash_table[h], NULL);
        hash_table[h] = node;
        return node;
    }
    void hash_delete(int key){
        int h = hash_to(key);
        HashNode* prev = NULL;
        HashNode* curt = hash_table[h];

        while(curt != NULL && curt->key != key){
            prev = curt;
            curt = curt->next;
        }

        if(hash_table[h] == curt){
            if(curt != NULL) hash_table[h] = curt->next;
            else hash_table[h] = NULL;
        }
        if(curt != NULL && prev != NULL){
            prev->next = curt->next;
            delete curt;
        }
    }
    Entry* entry_cut(Entry* et){
        if(et == NULL) return NULL;
        if(et == head) head = et->next;
        if(et == tail) tail = et->prev;
        if(et->prev != NULL) et->prev->next = et->next;
        if(et->next != NULL) et->next->prev = et->prev;
        return et;
    }
    Entry* entry_insert_front(Entry* et){
        et->next = head;
        et->prev = NULL;
        if(head != NULL) head->prev = et;
        if(tail == NULL) tail = et;
        head = et;
        return et;
    }
    int entry_update(Entry* et, int v){
        Entry* old_et = entry_cut(et);
        int old_v = old_et->v;
        old_et->v = v;
        entry_insert_front(old_et);
        return old_v;
    }
};

int main(){
    LRUCache* cache = new LRUCache(5);

    cache->put(1, 1);
    cache->put(5, 5);
    cache->put(2, 2);
    cache->put(6, 6);
    cache->put(7, 7);
    cout<<cache->get(1)<<endl;       // returns 1
    cache->put(3, 3);    // evicts key 2
    cout<<cache->get(5)<<endl;       // returns -1 (not found)
    cout<<cache->get(2)<<endl;       // returns -1 (not found)
    cache->put(4, 4);    // evicts key 1
    cout<<cache->get(6)<<endl;       // returns -1 (not found)
    cout<<cache->get(1)<<endl;       // returns -1 (not found)
    cout<<cache->get(3)<<endl;       // returns 3
    cout<<cache->get(4)<<endl;       // returns 4
}