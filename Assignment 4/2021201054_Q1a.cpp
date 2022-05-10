#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct suffix{
    int index;
    int rank1;
    int rank2;
};

int cmp(suffix a, suffix b)
{

    if(a.rank1 == b.rank1){
        if(a.rank2 < b.rank2)
            return 1;
        else
            return 0;
    }
    else if(a.rank1 < b.rank1)
        return 1;
    return 0;
}

void suffixArray(string str,vector<int> &suffixArr){
    int rank,prev_rank;
    int n = str.length();
    vector<int> index(n);
    vector<suffix> suff(n);
    int i=0;
    while(i<n){
        suff[i].index = i;
        suff[i].rank1= str[i];
        suff[i].rank2 =((i+1)<n)?str[i+1]:str[(i+1)%n];
        i+=1;
    }

    sort(suff.begin(), suff.end(), cmp);
    
    int k=4,next_idx;
    while(k<2*n){
        rank = 0;
        prev_rank = suff[0].rank1;
        suff[0].rank1 = rank;
        index[suff[0].index] = rank;
        i=1;
        while(i<n){
            if(suff[i].rank1 == prev_rank && suff[i].rank2 == suff[i-1].rank2){
                prev_rank = suff[i].rank1;
                suff[i].rank1 = rank;
            }
            else{
                prev_rank = suff[i].rank1;
                rank = rank + 1;
                suff[i].rank1 = rank;
            }
            index[suff[i].index]=rank;
            i+=1;
        }

        i=0;
        while(i<n){
            next_idx = suff[i].index + k/2;
            suff[i].rank2 = (next_idx<(n))?index[next_idx]:index[next_idx%n];
            i+=1;
        }
        sort(suff.begin(), suff.end(), cmp);
        k=k*2;
    }

    i=0;
    while(i<n){
        suffixArr.push_back(suff[i].index);
        i+=1;
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
    string inp;
    cin>>inp;
    int n=inp.size();
    vector<int> suffixArr;
    suffixArray(inp,suffixArr);
    string ans = inp.substr(suffixArr[0]) + inp.substr(0,suffixArr[0]);
    cout<<ans;
    return 0;

}