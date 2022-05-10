#include<iostream>

using namespace std;

class puzzleSolver{
    // Trie Node structure
    struct Node{
        char data;
        int wordend;
        Node* nextAlpha[26];
        string word;
        Node(char a){
            data = a;
            wordend = 0;
            int i=0;
            while(i<26){
                nextAlpha[i]=NULL;
                i+=1;
            }
        }
    };

    //root Node of Trie
    Node *root= new Node('/');

    //Insert function to enter value in trie
    void insert(string word){
        if(word.length() <= 0)
            return;
        int index , i=0;
        Node *temp = root;

        while(word[i]){
            index = word[i]-'a';
            if(temp->nextAlpha[index] == NULL){
                temp->nextAlpha[index] = new Node(word[i]);
            }
            temp = temp->nextAlpha[index];
            i+=1;
        }
        temp->wordend=1;
        temp->word=word;
    }

    // Partion function to return where to partition array
    int partition(string wordsArr[],int start, int end)
    {
        string pivot = wordsArr[end];
        string temp;

        int j = start;
        int i = start - 1;

        while(j<end){
            if(wordsArr[j]<pivot){
                i+=1;
                temp=wordsArr[i];
                wordsArr[i]=wordsArr[j];
                wordsArr[j]=temp;
            }
            j+=1;
        }
        temp=wordsArr[i+1];
        wordsArr[i+1]=wordsArr[end];
        wordsArr[end]=temp;

        return i+1;
    }

    // Quicksort to sort the array of strings
    void quicksort(string wordsArr[],int left, int right)
    {
        if (left < right)
        {
            int pivot = partition(wordsArr, left, right);
            quicksort(wordsArr, left, pivot - 1);
            quicksort(wordsArr, pivot + 1, right);
        }
    }

    // to check whether i,j to traverse are within grid
    bool isValid(int i,int j){
        if(i<0 || i>=r || j<0 || j>=c)
            return false;
        return true;
    }

    public:
        long long int r, c;   //Rows and Columns
        char** grid; 
        int** isVisited;
        string* words;
        string ans[1000];
        int x[4]={1,0,-1,0};
        int y[4]={0,1,0,-1};
        int anslen=0;
        long long int lenWordArr;

        //Constructor;
        puzzleSolver(int rows,int cols){
            r = rows;
            c = cols;
            grid = new char* [r];
            isVisited = new int*[r]{0};
            for(int i =0; i<r; i++){
                grid[i] = new char[c];
                isVisited[i] = new int[c]{0};
            }
            
        }


        void insertGrid(char inp, int i, int j){
            grid[i][j] = inp;
        }

        
        void intializeWordArray(long long int len){
            lenWordArr = len;
            words = new string[len];
        }
        void insertWord(string inp, int i){
            words[i] = inp;
        }

        // Search Words in Grid (Find Word Helper)
        void search(Node* temp,long long int i, long long int j){
            int index = grid[i][j] - 'a';
            if(isVisited[i][j] || (temp->nextAlpha[index])==NULL)
                return;
            
            temp = temp->nextAlpha[index];
            if(temp->wordend){
                ans[anslen++] = temp->word;
                temp->wordend=0;
            }
            char ch = grid[i][j];

            isVisited[i][j] = 1;
            for(int k=0; k<4; k++){
                if(isValid(i+x[k],j+y[k]))
                    search(temp,i+x[k],j+y[k]);
            }
            isVisited[i][j] = 0;
            return;
        }

        // Find the words which can be formed in grid
        void findWords(){
            for(int i=0; i<lenWordArr; i++)
                insert(words[i]);
            long long int i = 0, j=0;
            Node *temp = root;
            while(i<r){
                j=0;
                while(j<c){
                    search(temp,i,j);
                    j+=1;
                }
                i+=1;
            }
            quicksort(ans,0,anslen-1);
      
        }


        void displayWords(){
            for(int i=0; i<lenWordArr; i++){
                cout<<words[i]<<" ";
            }
        }


};


int main(){

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    long long int rows,cols,X;

    cin>>rows>>cols;
    puzzleSolver p(rows,cols);
    for(int i=0;i<rows; i+=1){
        for(int j=0; j<cols; j++){
            char inp;
            cin>>inp;
            p.insertGrid(inp,i,j);
        }
    }
    cin>>X;
    p.intializeWordArray(X);

    for(int i=0; i<X; i++){
        string inp;
        cin>>inp;
        p.insertWord(inp,i);
    }

    p.findWords();
    for(int i=0; i<p.anslen; i++){
        cout<<p.ans[i]<<" ";
    }

    return 0;
}
