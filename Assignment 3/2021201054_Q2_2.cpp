#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include <algorithm>

using namespace std;

class Graph{
    public:
    int vertex;
    list<pair<int,int>> *adjList;

    Graph(int v){
        this->vertex = v;
        adjList = new list<pair<int,int>>[vertex];
    }

    void addEdge(int u, int v, int dis){
        adjList[u].push_back({v,dis});
        adjList[v].push_back({u,dis});
    }

    void kShortest(int src,int des,vector<int> &visited,vector<pair<int,string>>&res,vector<int> &curr_dis,int dist,vector<int> &curr_path){
        visited[src] = 1;
        curr_path.push_back(src);
        curr_dis.push_back(dist);
        if(src==des){
            string path = "";
            int dist = 0;
            path=to_string(curr_path[0]);
            for(int i=1; i<curr_path.size(); i++){
                path += " " + to_string(curr_path[i]);
                dist += curr_dis[i];
            }
            res.push_back({dist,path});
        }

        else{
            list<pair<int,int>>::iterator it;
            for(it=adjList[src].begin();it!=adjList[src].end();it++){
                if(visited[it->first]==0){ 
                    kShortest(it->first,des,visited,res,curr_dis,it->second,curr_path) ;
                }
            }
        }
        curr_dis.pop_back();
        curr_path.pop_back();
        visited[src] = 0;
    }
};

bool comparator(const pair<int,string> &itr1, const pair<int,string> &itr2){
    if(itr1.first < itr2.first)
        return true;
    else if(itr1.first == itr2.first){
        if(itr1.second <= itr2.second)
            return true;
        else
            return false;   
    }

    return false;
}


int main(){

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    int N,M;
    cin>>N>>M;
    Graph g(N);
    list<pair<int,int>> *Graph = new list<pair<int,int>>[N];
    vector<pair<int,string>> allPath;
    for(int i=0;i<M; i++){
        int u,v,dis;
        cin>>u>>v>>dis;
        g.addEdge(u,v,dis);
    }
    int K;
    cin>>K;

    vector<pair<int,string>> ans;
    vector<int>visited(N,0);
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            vector<int>visited(N,0);
            vector<int> path;
            vector<int> curr_dis;
            g.kShortest(i,j,visited,ans,curr_dis,0,path);
        }
    }

    sort(ans.begin(),ans.end(),comparator);
    int i=0;
    for(auto itr:ans){
        if(i >=K){
            break;
        }
        // cout<<itr.second<<" Distance: "<<itr.first<<endl;
        cout<<itr.second<<endl;
        i+=1;
    }
}