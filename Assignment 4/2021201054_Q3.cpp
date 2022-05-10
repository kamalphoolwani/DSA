#include <iostream>

using namespace std;

class maxXor{
    struct Node{
        int end;
        Node* next[2];
        Node(){
            this->end=0;
            this->next[0]=NULL;
            this->next[1]=NULL;
        }
    };

    Node *root = new Node();

    public:
        
        void insert(long long int x){
            Node *temp = root;
            long long int i=63;
            while(i>=0){
                long long int bit = (x>>i&1);
                if(!temp->next[bit])
                    temp->next[bit] = new Node;
                temp = temp->next[bit];
                i-=1;
            }
            temp->end=1;
        }

        long long int findMaxXor(long long int x){
            Node* temp=root;
            long long int i=63;
            long long int maxm = 0;
            while(i>=0){
                long long int bit = (x>>i &1);
                long long int nextMov = bit ^ 1;
                if(temp->next[nextMov] != NULL){
                    maxm = maxm + (1<<i);
                    temp = temp->next[nextMov];
                }
                else{                                    
                    temp = temp->next[bit];
                }
                i-=1;
            }
            return (maxm);
        }
};

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    maxXor m;

    long long int n,q;
    cin>>n>>q;
    long long int temp;
    while(n--){
        cin>>temp;
        m.insert(temp);
    }

    while(q--){
        cin>>temp;
        cout<<m.findMaxXor(temp)<<endl;
    }
    return 0;
}