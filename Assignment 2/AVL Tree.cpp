#include<iostream>
#include <sstream>

using namespace std;

template<class X>

class Compare{
    public:
        int operator ()(X a, X b){
            if(a>b)
                return 1;
            else if(a<b)
                return -1;
            return 0;
        }
};

template<class X, class C=Compare<X>>
class avl{
    struct Node{
        X data;
        int height;
        Node* right;
        Node* left;
        int count;
        Node(X data){
            this->data=data;
            right=NULL;
            left=NULL;
            height=1;
            count=1;
        }
    };

    C comparison;

    int compare(X a, X b){
            return comparison(a,b);
    }

    string tostring(X data){
        ostringstream streamObj;
        streamObj << data;
        string k = streamObj.str();
        return k;
    }



    string strmin(string a, string b){
        if(a<b)
            return a;
        return b;
    }

    int closeFlag = 0;
    X t;
    public:
        Node *h;
        avl(){
            h=NULL;
            
        }

        int height(Node *root){
            if(root == NULL){
                return 0;
            }
            
            return root->height;
        }

        int setHeight(Node *root){
            if(root==NULL)
                return 0;
            
            int leftH = root->left ? root->left->height : 0;
            int rightH = root->right ? root->right->height : 0;
            return 1 + max(leftH,rightH);
        }
    
        Node* leftRotate(Node* node){
            Node *nroot = node->right;
            node->right = nroot->left;
            nroot->left = node;
            node->height = setHeight(node);
            nroot->height = setHeight(nroot);
            return nroot;
        }

        Node* rightRotate(Node* node){
            Node *nroot = node->left;
            node->left = nroot->right;
            nroot->right = node;
            node->height = setHeight(node);
            nroot->height = setHeight(nroot);
            return nroot;
        }

        int balance(Node *node){
            if(!node)
                return 0;
            int lh = height(node->left);
            int rh = height(node->right);
            return (lh - rh);
        }

        //INSERT NODE
        Node* append(X data, Node *node){
            if(node==NULL){
                node = new Node(data);
                return node;
            }
            if(compare(data,node->data)==0){
                node->count += 1;
                return node;
            }
            else if(compare(data,node->data)==-1){
                node->left= append(data,node->left);
            }
            else{
                node->right = append(data,node->right);
            }

            node->height = setHeight(node);

            int b = balance(node);

            if(b>1){
                if(compare(data,node->left->data)==-1){
                    return rightRotate(node);
                }
                else if(compare(data,node->left->data)==0){
                    return rightRotate(node);
                }

                else{
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                }
            }

            else if(b<-1){
                if(compare(data,node->right->data)==1){
                        return leftRotate(node);
                }
                else{
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }

            }
                return node;

        }

        void insert(X data){
            h = append(data,h);
        }


        Node* findSuccessor(Node *node){
            if (!node)
                return node;
            Node *temp = node->right;
            while(temp->left){
                temp=temp->left;
            }

            return temp;

        }

        
        //deletion of node
        Node* deleteNode(Node *node, X data){
            if(!node)
                return node;
            if(compare(data,node->data) == -1)
                node->left = deleteNode(node->left,data);
            else if(compare(data,node->data)==1)
                node->right = deleteNode(node->right,data);
            else{
                if( !(node->left) ||!(node->right))
                    {
                        Node *temp;
                        if(node->left)
                            temp = node->left;
                        else
                            temp = node->right;
            
                        // No child case
                        if (temp == NULL)
                        {
                            temp = node;
                            node = NULL;
                        }
                        else // One child case
                        *node = *temp;
                        free(temp);
                }

                else{
                    Node *temp = findSuccessor(node);
                    node->data = temp->data;

                    node->right = deleteNode(node->right,temp->data);
                }
            }


            if(!node)
                return node;
            
            node->height=setHeight(node);
            int bf = balance(node);

            if(bf>1){
                if(balance(node->left)>=0)
                    return rightRotate(node);
                else{
                    node->left = leftRotate(node->left);
                    return rightRotate(node);
                
                }
            }

            else if(bf<-1){
                if(balance(node->right)<=0)
                    return leftRotate(node);
                
                else{
                    node->right = rightRotate(node->right);
                    return leftRotate(node);
                }
            }

            return node;

        }

        void deletion(X data){
            h = deleteNode(h,data);
        }

        //search
        bool searchNode(Node *node, X data){
            if(!node)
                return false;
            else if(compare(data,node->data)== -1)
                return searchNode(node->left,data);
            else if(compare(data,node->data) == 1)
                return searchNode(node->right,data);

            return true;

        }

        bool search(X data){
            return searchNode(h,data);
        }

        //count occurence
        int countNode(Node *node, X data){
            if(!node)
                return 0;
            else if(compare(data,node->data)==0){
                return node->count;
            }
            else if(compare(data,node->data)== -1){
                return countNode(node->left,data);
            }
            return countNode(node->right,data);
        }

        int count(X data){
            return countNode(h,data);
        }

        //lower bound
        string lowerBoundNode(Node *node, X data){
            if(!node)
                return "-1";
            if(compare(data,node->data)==0){
                return tostring(node->data);
            }

            else if(compare(data,node->data)==-1){
                string k = lowerBoundNode(node->left,data);
                if(k == "-1"){
                    return tostring(node->data);
                }
                return k;
            }

            return lowerBoundNode(node->right,data);
        }

        string lower_bound(X data){
           // X ans;
            return lowerBoundNode(h, data);
           // return ans;
        }

       // upper bound
        string upperBoundNode(Node *node, X data){
            if(!node){
                return "-1";
            }
            else if(compare(data,node->data)== -1){
                string k = upperBoundNode(node->left,data);
                if(k == "-1"){
                    return tostring(node->data);
                }
                return k;
            }

           else if(compare(data,node->data)== 1)
                return upperBoundNode(node->right,data);
            
           return upperBoundNode(node->right,data);
            
        } 

        string upper_bound(X data){
            return upperBoundNode(h,data);
        }

        
        //closestElement
        string closestNode(Node *node, X data){
            if(!node){
                return "-1";
            }
            
            Node *temp;
            temp = node;
            
            string ans,tmp;
            int mindiff = INT_MAX,te;
            while(temp){
                te = abs(temp->data - data);
                if(mindiff>=te){
                    mindiff = te;
                    ans = tostring(temp->data);
                }

                if(compare(temp->data,data)==0)
                    return tostring(data);
                else if(compare(data,temp->data)== -1){
                    temp = temp->left;
                }
                else{
                    temp=temp->right;
                }
            }

            return ans;
        }

        string closest(X data){
            return closestNode(h,data);
        }

        //kth largest
        void klargestNode(Node *node, int &k, X &ans, int &flag){
            if(node==NULL || k<=0)
                return;
            
            klargestNode(node->right,k,ans,flag);
            if(node->count >= 1 && flag){
                if((k -(node->count))<=0){
                    k=0;
                }
                
                else{
                    k = k - node->count;
                }
            }

            if(k==0  && flag){
                ans = node->data;
                flag = 0;
                return;
            }

            klargestNode(node->left,k,ans,flag);
        }

        X klargest(int k){
            X ans;
            int flag = 1;
            klargestNode(h,k,ans,flag);
            return ans;
        }

        //COUNT NODES IN RANGE
        int countRangeNode(Node *node, X low, X high){
            if(!node)
                return 0;
            if(compare(low,node->data)==0 && compare(high,node->data)==0)
                return node->count;
            else if(((compare(node->data,high)==-1) || (compare(node->data,high)==0)) &&
                   ((compare(node->data,low)==1) || (compare(node->data,low)==0)))
                   return node->count + countRangeNode(node->left,low,high) + countRangeNode(node->right,low,high);
            else if(compare(node->data,low)==-1)
                return countRangeNode(node->right,low,high);
            
            return countRangeNode(node->left,low,high);
        }

        int countRange(X low, X high){
            return countRangeNode(h,low,high);
        }


        //inORDER
        void inOrder(Node *root)
        {
            if(root != NULL)
            {
                inOrder(root->left);
                cout << root->data <<" ";
                inOrder(root->right);
            }
        }

        void display(){
            inOrder(h);
            cout<<endl;
        }
};


/**************************** For struct datatype. ********************************/
struct t{
    int id;
    int data;
    string b="default";
    friend ostream & operator << (ostream &out, const t &c);
    int operator - (t t2){
        return data - t2.data;
    }
};


// cout overload
ostream & operator << (ostream &out, const t &c)
{
    out << c.data;
    //out << "+i" << c.imag << endl;
    return out;
}

//struct compare function
class structCmp{
    public:
    int operator ()(t t1, t t2){
        if(t1.data<t2.data)
            return -1;
        else if(t1.data>t2.data)
            return 1;
        return 0;
        
    }
};
/********************************************************************************************/

/******************************** PAIR DATATYPE *********************************************/

class pairCmp{
    public:
    int operator ()(pair<int,int> t1, pair<int,int> t2){
        if(t1.first<t2.first)
            return -1;
        else if(t1.first>t2.first)
            return 1;
        else if(t1.first == t1.first){
            if(t1.second<t2.second)
                return -1;
            if(t1.second>t2.second)
                return 1;
        }
        return 0;
        
    }

};

template <class T, class D>
ostream& operator<<(std::ostream& os, pair<T, D> &lst) {
        os << lst.first << " " << lst.second<<" ";
    
    return os;
}

template <class T, class U>
int operator - (const pair<T,U> & l,const pair<T,U> & r) { 
    int x = (l.first - r.first) * (l.first - r.first);
    int y = (l.second-r.second) * (l.second-r.second);
    return x +y;                                    
}      


/***********************************************************************************/


/********************************** MAIN *******************************************/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    /***************** FUNCTION *******************************/
    /* 


    1. insert(data)
    2. deletion(data);
    3. search(data);
    4. count(data);  //count occurence
    5. lower_bound(data);
    6. upper_bound(data);
    7. closest(data);
    8. klargest(k);
    9. countRange(low,high);

    */

    /************* PAIR DECLARATION ***************************************/
    // avl<pair<int,int>,pairCmp> p;
    /************************** Struct **************************************/
    // avl<t,structCmp> a;
    // avl<pair<int,int>,pairCmp> a;
    // pair<int,int> temp = {2,0};

    int low,high,k,key,t;
	//string key;
	avl<int> tree;
	//AVL <string> tree;
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key;
		        tree.insert(key);
				break;
			case 2:
				cin>>key;
				tree.deletion(key);
				break;
			case 3:
				cin>>key;
				
				cout<<tree.count(key)<<endl;
				break;
			case 4:
				cin>>key;
				cout<<tree.search(key)<<endl;
				break;
			case 5:
				cin>>key;
				cout<<tree.lower_bound(key)<<endl;
				break;
			case 6:
				cin>>key;
				cout<<tree.upper_bound(key)<<endl;
				break;
			case 7:
				cin>>key;
				cout<<tree.closest(key)<<endl;
				break;
			case 8:
				cin>>k;
				cout<<tree.klargest( k)<<endl;
				break;
			case 9:
				cin>>low>>high;
				cout<<tree.countRange(low,high)<<endl;	
				break;
		}
		tree.display();



    // a.insert({1,2});
    // a.insert({0,2});
    // a.insert({2,1});
    // a.insert({4,1});
    // a.display();

    // cout<<"Closest: "<<a.closest(temp)<<endl;
    // return 0;
    //avl<int> a;
    // a.insert(4);
    // a.insert(2);
    // a.insert(6);
    // a.insert(5);
    // a.insert(0);
    // a.insert(3);
    // a.insert(7);
    // a.insert(8);
    // a.insert(4);
    // a.insert(5);
    //  a.insert(5);
    //   a.insert(5);
    //    a.insert(5);
    //     a.insert(5);
    // a.display();
    // a.deletion(5);
    // a.display();
    // a.deletion(4);
    // a.display();
    // cout<<a.search(00)<<endl;
   // a.display();
    // bool s = a.search(2);
    // string ans = s?"true":"false";
    // cout<<ans<<endl;
    // s = a.search(9);
    // ans = s?"true":"false";
    //cout<<ans;



  // cout<<a.lower_bound(3)<<endl;
    // t t9;
    // t9.data = 44;
    // ostringstream streamObj;
    // streamObj << t7;
    // string k = streamObj.str();
    // cout<<k<<endl;
  //  cout<<a.upper_bound(t9)<<endl;
    // cout<<"Count: "<<a.count(5)<<endl;
    // cout<<"Count: "<<a.count(3)<<endl;
    // cout<<"Count: "<<a.count(10)<<endl;


    // cout<<"Kth largest "<<a.klargest(8).a<<endl;
    // cout<<"cOUNT IN rANGE "<<a.countRange(t3,t7);

}



