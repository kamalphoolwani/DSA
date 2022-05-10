#include<iostream>
#include<vector>
#include<list>
#include<queue>

using namespace std;

// Heap Node
struct heapNode{
    int v;
    int dis;
    heapNode();
    heapNode(int v, int dis){
        this->v = v;
        this->dis = dis;
    }
};

// Min Heap Class
class minHeap{

    public:
        int capacity;
        int curr_size;
        heapNode** arr;
        int *pos;
        minHeap(int cap){
            this->capacity=cap;
            arr = new heapNode*[capacity];
            curr_size=0;
            pos = new int[capacity];
        }

    void minHeapify(int index){
        int minm, left,right;
        minm = index;
        left = 2*index + 1;
        right =  2*index +2;
        if(left<curr_size && arr[left]->dis < arr[minm]->dis)
            minm = left;
        if(right<curr_size && arr[right]->dis < arr[minm]->dis)
            minm =right;
        
        if(minm != index){
            heapNode* minmNode = arr[minm];
            heapNode* tempNode = arr[index];
            pos[minmNode->v] = index;
            pos[tempNode->v] = minm;

            //Swap Node
            heapNode *temp = arr[minm];
            arr[minm] = arr[index];
            arr[index] = temp;
            minHeapify(minm);

        }
    }

    heapNode* extractMin(){
        if(curr_size==0)
            return NULL;
        heapNode* root = arr[0];

        heapNode* lastNode = arr[curr_size-1];
        arr[0] = lastNode;
        pos[root->v] = curr_size - 1;
        pos[lastNode->v] = 0;
        curr_size -=1 ;
        minHeapify(0);
        return root;
    }

    void decreaseKey(int v, int dist){
        int index = pos[v];
        arr[index]->dis = dist;
        while(index>0 && arr[(index - 1) / 2]->dis > arr[index]->dis)
        {
            // Swap the node with parent as it is smaller 
            pos[arr[index]->v] = (index-1)/2;
            pos[arr[(index-1)/2]->v] = index;

            // Swap Node
            heapNode *temp = arr[index];
            arr[index] = arr[(index - 1) / 2];
            arr[(index - 1) / 2] = temp;

            // move One index up
            index = (index - 1) / 2;
        }

    }
};


// Graph Class

class Graph{
    int vertex;
    list<pair<int,int>> *adjList;
    
    public:
        Graph(int numVertex){
            vertex = numVertex;
            adjList = new list<pair<int,int>>[vertex];
        }

        void addEdge(int u, int v, int dis){
            adjList[u].push_back({v,dis});
            adjList[v].push_back({u,dis});
        }

        void shortestPath(int source){  
            vector<int> dist(vertex,INT_MAX);
            vector<int> parent(vertex);
            vector<vector<string>> pathToNode(vertex,vector<string>(1,""));
            minHeap *priority_queue=new minHeap(vertex);
           
            parent[source]=-1;
            for(int i=0; i<vertex; i++){
                priority_queue->arr[i] = new heapNode(i,dist[i]);
                priority_queue->pos[i] = i;
                pathToNode[i][0] = to_string(i);
            }
            dist[source]=0;
            priority_queue->curr_size=vertex;
            priority_queue->decreaseKey(source,dist[source]);

            while(priority_queue->curr_size){
                heapNode* minDisNode = priority_queue->extractMin();
                int u = minDisNode->v;
                list<pair<int,int>>::iterator itr;
                for(itr= adjList[u].begin(); itr!=adjList[u].end();itr++){
                    int v = itr->first;
                    int dis = itr->second;
                    if(priority_queue->pos[v]<priority_queue->curr_size && dist[u]!=INT_MAX){
                        if((dist[v] > dist[u] + dis)){
                            dist[v] = dist[u] + dis;
                            parent[v]=u;
                            priority_queue->decreaseKey(v,dist[v]);
                            pathToNode[v][0] = to_string(v) + " " + pathToNode[u][0];
                        }
                        else if(dist[v] == dist[u] + dis){
                            if(parent[v]!=u){
                                string temp = to_string(v) + " " + pathToNode[u][0];
                                if(temp<pathToNode[v][0]){
                                    pathToNode[v][0] = temp;
                                    parent[v]=u;
                                }
                            }
                        }
                    }

                }
            }
            //Printing paths to all nodes
            for (unsigned i = 0; i < vertex; i++) {
                if(i!=source){
                    string temp = to_string(i);

                    if(pathToNode[i][0]!=temp){
                        cout<<pathToNode[i][0];
                        cout<<'\n'; 
                    }
                }    
            }

        }


};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    /*************** DRIVER CODE ******************************/
    int N, M;
    cin>>N>>M;
    Graph g(N);
    while(M--){
        int u,v,dis;
        cin>>u>>v>>dis;
        g.addEdge(u,v,dis);
    }
    int src;
    cin>>src;
    g.shortestPath(src); 
    return 0;
}