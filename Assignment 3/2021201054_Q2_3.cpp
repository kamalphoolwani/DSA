#include<iostream>
#include<vector>
#include<queue>

using namespace std;

bool isValid(int x, int y , int r, int c){
    if(x<0 || y<0 || x>= r || y>=c)
        return false;
    return true;
}

void graphTraversal(vector<vector<char> > grid, vector<vector<int> > &visited){
    int srcx = 1;
    int srcy = 0;

    int movx[4] = {1,0,-1,0};
    int movy[4] = {0,1,0,-1};
    queue<pair<int,int> > q;
    int row = grid.size();
    int col = grid[0].size();
    pair<int,int> onTop;
    q.push({srcx,srcy});
    while(!q.empty()){
        onTop = q.front();
        q.pop();
        int x = onTop.first;
        int y = onTop.second;
        for(int i=0; i<4; i++){
            int nextx = x+movx[i];
            int nexty = y+movy[i];
            if(isValid(nextx,nexty,row,col) && (visited[nextx][nexty]==-1) && (grid[nextx][nexty]!='#')){
                visited[nextx][nexty] = visited[x][y] + 1;
                q.push({nextx,nexty});
            }
        }
    }

    return;

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
    vector<vector<char>> grid(N,vector<char>(M,'0'));
    char temp;
    vector<pair<int,int>> riderPos;
    pair<int,int> sourcePos;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>temp;
            grid[i][j]=temp;
            if(temp=='R')
                riderPos.push_back({i,j});
            else if(temp=='A'){
                sourcePos = {i,j};
            }
        }
    }

    vector<vector<int>> visited(N,vector<int>(M,-1));
    visited[1][0] = 0;
    graphTraversal(grid,visited);

    int minmRiderDis = INT_MAX;
    int minmSourceDis = visited[sourcePos.first][sourcePos.second];
    for(int i=0; i<riderPos.size(); i++){
        minmRiderDis = min(visited[riderPos[i].first][riderPos[i].second],minmRiderDis);
    }
    
    if(minmRiderDis<minmSourceDis || visited[sourcePos.first][sourcePos.second] == -1){
        cout<<"No";
    }
    else{
        cout<<"Yes"<<endl;
        cout<<minmSourceDis<<endl;
    }

    
    return 0;
}