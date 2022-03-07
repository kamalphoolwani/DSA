#include<iostream>
#include<unordered_map>

using namespace std;

class LRUCache{
    //Defining Node structure
    struct Node{
        int key;
        int value;
        Node *prev;
        Node *next;
        Node(int _key,int _value){
            key=_key;
            value=_value;
        }
    };
    
    //Adding new node
    void addNode(Node *nodetoAdd){
        nodetoAdd->next = front->next;
        front->next->prev = nodetoAdd;
        front->next = nodetoAdd;
        nodetoAdd->prev = front;
    }

    //Delete Node
    void deleteNode(Node *nodeToDelete){
        nodeToDelete->next->prev = nodeToDelete->prev;
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    unordered_map<int,Node*> cache;
    //pointers to keep track of front and rear
    Node* front = new Node(0,0);
    Node* rear = new Node(-1,-1);
    int capacity;

    public:
        LRUCache(int cap){
            capacity = cap;
            front->next = rear;
            rear->prev = front;
        }

        //Get the value of key if present
        int get(int key){
            if(cache.find(key)!=cache.end()){
                Node *ans = cache[key];
                int value = ans->value;
                cache.erase(key);
                deleteNode(ans);
                addNode(ans);
                cache[key]=front->next;
                return value;
            }
            return -1;
        }

        //To enter the key in cache or updating already present key value
        void set(int key, int value){
            if(cache.find(key)!=cache.end()){
                Node *inCache = cache[key];
                deleteNode(inCache);
                inCache->value=value;
                addNode(inCache);
                return;
            }

            if(cache.size()==capacity){
                int keyToDelete = rear->prev->key;
                Node* nodeToDelete = rear->prev;
                cache.erase(keyToDelete);
                deleteNode(nodeToDelete);
            }

            Node* nodetoAdd = new Node(key,value);
            addNode(nodetoAdd);
            cache[key] = front->next;  
        }
};

int main(){
    int capacity;
    cin>>capacity;
    LRUCache *cache = new LRUCache(capacity);
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