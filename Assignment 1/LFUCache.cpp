#include<iostream>
#include<unordered_map>

using namespace std;

class LFUCache{
    struct Node{
        int key,value,freq;
        Node* next;
        Node* prev;
        Node(int _key, int _value){
            key = _key;
            value = _value;
            freq = 1;
        }
    };

    struct List{
        int size;
        Node* front;
        Node* rear;
        List(){
            front = new Node(0,0);
            rear = new Node(-1,-1);
            front->next = rear;
            rear->prev = front;
            size=0;
        }
        void addNode(Node *nodeToAdd){
            nodeToAdd->next = front->next;
            front->next->prev = nodeToAdd;
            nodeToAdd->prev = front;
            front->next = nodeToAdd;
            size+=1;
        }
        void deleteNode(Node *nodeToDelete){
            nodeToDelete->next->prev = nodeToDelete->prev;
            nodeToDelete->prev->next = nodeToDelete->next;
            size-=1;
        }
    };

    int capacity;
    int minFreq;
    int currCapacity;
    unordered_map<int,List*> freq_keylist;
    unordered_map<int,Node*> cache;
    public:
        LFUCache(int cap){
            capacity=cap;
            minFreq=0;
            currCapacity=0;
        }
        int get(int key){
            if(cache.find(key)!=cache.end()){
                Node *res = cache[key];
                int ans = res->value;
                cache.erase(res->key);
                freq_keylist[res->freq]->deleteNode(res);
                if(res->freq==minFreq && freq_keylist[res->freq]->size==0)
                    minFreq+=1;

                int node_next_freq = res->freq + 1;
                if(freq_keylist.find(node_next_freq) != freq_keylist.end()){
                    res->freq=node_next_freq;
                    freq_keylist[node_next_freq]->addNode(res);
                    cache[res->key] = res;
                }
                else{
                    List *next_freq_keylist = new List();
                    res->freq=node_next_freq;
                    next_freq_keylist->addNode(res);
                    cache[res->key] = res;
                    freq_keylist[res->freq] = next_freq_keylist;
                }
                return ans;
            }
            return -1;
        }

        void set(int key, int value){
            if(capacity==0)
                return;
            if(cache.find(key)!=cache.end()){
                Node* res = cache[key];
                res->value = value;
                freq_keylist[res->freq]->deleteNode(res);
                if(res->freq==minFreq && freq_keylist[res->freq]->size==0)
                    minFreq+=1;
                List *next_freq_keylist = new List();
                int node_next_freq = res->freq + 1;
                if(freq_keylist.find(node_next_freq) != freq_keylist.end()){
                    next_freq_keylist = freq_keylist[node_next_freq];
                }
                res->freq+=1;
                next_freq_keylist->addNode(res);
                freq_keylist[res->freq] = next_freq_keylist;
            }
            else{
                List *list = new List();
                if(capacity == currCapacity){
                    cache.erase(freq_keylist[minFreq]->rear->prev->key);
                    freq_keylist[minFreq]->deleteNode(freq_keylist[minFreq]->rear->prev);
                    currCapacity-=1;
                }
                currCapacity+=1;
                minFreq=1;
                if(freq_keylist.find(minFreq)!=freq_keylist.end())
                    list = freq_keylist[minFreq];

                Node *node = new Node(key,value);
                cache[key]=node;
                list->addNode(node);
                freq_keylist[minFreq]=list;
            }
        }
};

int main(){
    int capacity;
    cin>>capacity;
    LFUCache *cache = new LFUCache(capacity);
    int operations;
    cin>>operations;
    while(operations--){
        int option;
        cin>>option;
        if(option==1){
            int key,value;
            cin>>key>>value;
            cache->set(key,value);
            cout<<endl;
        }
        else if(option==2){
            int key;
            cin>>key;
            cout<<cache->get(key)<<endl;
        }
    }

    return 0;
}