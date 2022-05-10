#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class spellChecker{
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

    string toLower(string word){
        transform(word.begin(),word.end(),word.begin(),::tolower );
        return word;
    }

    Node *root= new Node('/');

    void searchWords(Node *temp,vector<string> &autoWords, string word){
        if(temp==NULL)
            return;
        if(temp->wordend){
            autoWords.push_back(word);
        } 
        int i = 0;
        while(i<26){
            if(temp->nextAlpha[i]!=NULL){
                searchWords(temp->nextAlpha[i],autoWords,word + char('a' + i));
            }
            i+=1;
        }
    }

    // set<string> words;
    
    public:
        int maxdis = 3;
        set<pair<int,string>> autoCorrWord;
        void insert(string word){
            if(word.length() <= 0)
                return;
            word = toLower(word);
            // words.insert(word);
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
            temp->word = word;
        }

        int search(string word){
            if(word.length() <= 0)
                return 0;
            word = toLower(word);
            Node *temp = root;
            int i = 0,index;
            while(word[i]){
                index = word[i]-'a';
                if(temp->nextAlpha[index] == NULL)
                    return 0;
                temp = temp->nextAlpha[index];
                i+=1;
            }
            return (temp->wordend);
        }

        vector<string> autoComplete(string word){
            word = toLower(word);
            vector<string> autoWords;
            Node *temp = root;
            int index, i=0;
            while(word[i]){
                index = word[i] - 'a';
                if(temp->nextAlpha[index]== NULL)
                    return autoWords;
                temp = temp->nextAlpha[index];
                i+=1;
            }

            searchWords(temp,autoWords,word);
            return autoWords;
        }


        void calcDistance(Node *temp,int index, string word, vector<int>&pdp){
            vector<int>cdp(pdp.size(),0);
            cdp[0] = pdp[0] + 1;
            int i = 1;
            int minm = cdp[0];
            int wlen = pdp.size();
            while(i<pdp.size()){
                if(word[i-1]==char(index + 'a'))
                    cdp[i] = pdp[i-1];
                else{
                    cdp[i] = min(min(cdp[i-1],pdp[i-1]),pdp[i]) + 1;
                }
                minm = min(minm,cdp[i]);
                i+=1;
            }

            if(cdp[wlen-1]<=maxdis && temp->wordend)
                autoCorrWord.insert({cdp[wlen-1],temp->word});
            if(minm<=maxdis){
                int j = 0;
                while(j<26){
                    if(temp->nextAlpha[j] != NULL){
                        calcDistance(temp->nextAlpha[j],j,word,cdp);
                    }
                    j+=1;
                }
            }
        }

        vector<string> autoCorrect(string word){
            vector<string> ans;
            vector<int>dp(word.length() + 1);
            Node *temp = root;
            int i = 0;
            while(i<dp.size()){
                dp[i]=i;
                i+=1;
            }

            i=0;
            while(i<26){
                if(temp->nextAlpha[i] != NULL){
                    calcDistance(temp->nextAlpha[i],i,word,dp);
                }
                i+=1;
            }

            for(auto itr : autoCorrWord){
                ans.push_back(itr.second);
            }
            return ans;
        }


};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    spellChecker s; 
    /* Driver Code */
    int numWords;
    cin>>numWords;
    for(int i=0; i<numWords; i++){
        string temp;
        cin>>temp;
        s.insert(temp);
    }
    int options;
    string input;
    cin>>options>>input;
    if(options==1){
        if(s.search(input)){
            cout<<"1"<<endl;
        }
        else{
            cout<<"0"<<endl;
        }
    }
    else if(options==2){
        vector<string> ans;
        ans = s.autoComplete(input);
        cout<<ans.size()<<endl;
        for(auto i: ans){
            cout<<i<<endl;
        }

    }
    else if(options==3){
        vector<string> ans;
        ans = s.autoCorrect(input);
        sort(ans.begin(),ans.end());
        cout<<ans.size()<<endl;
        for(auto i: ans){
            cout<<i<<endl;
        }
        
    }
    else{
        cout<<"Invalid Input!!";
    }

    return 0;
}