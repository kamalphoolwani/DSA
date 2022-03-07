#include<iostream>
using namespace std;


template<class X>

class ll_sparseMatrix{
    struct Node{
    int row,col;
    X val;
    Node* next;
    };
    public:

        int rows,cols,sparse_rows;
        X value;
        Node *head;
        ll_sparseMatrix(){
            head=NULL;
        }
        ll_sparseMatrix(int row,int col){
            head=NULL;
            rows = row;
            cols = col;
            sparse_rows=0;
        }

        void accept_matrix(){
            X temp;
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols;j++){
                    cin>>temp;
                    if(temp!=0){
                        insert(i+1,j+1,temp);
                        cout<<"Row: "<<i+1<<" Column: "<<j+1<<" "<<temp;
                    }
                }
            }
        }

        void addNode(Node* node){
            if(head==NULL){
                head=node;
                return;
            }
            Node *temp = head;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next = node;
            return;
        }

        void insert(int row, int col, X data){
            Node *newNode = new Node();
            newNode->row = row;
            newNode->col = col;
            newNode->val = data;
            newNode->next = NULL;
            addNode(newNode);
            sparse_rows+=1;
            return;
        }

        void printMatrix(){
            Node* temp = head;
            while(temp){
                cout<<temp->row<<" "<<temp->col<<" "<<temp->val<<endl;
                temp=temp->next;
            }
        }

        void add(ll_sparseMatrix &b){
            if(rows!=b.rows || cols!=b.cols){
                cout<<"Matrix cannot be added!!";
                return;
            }

            Node *bhead = b.head;
            Node *ahead = head;
            ll_sparseMatrix res;
            X tempsum=0;

            while(ahead!=NULL || bhead!=NULL){
                if(ahead->row == bhead->row){
                    if(ahead->col == bhead->col){
                        tempsum = ahead->val + bhead->val;
                        if(tempsum!=0)
                            res.insert(ahead->row,ahead->col,tempsum);
                        ahead = ahead->next;
                        bhead = bhead->next;
                    }

                    else if(ahead->col > bhead->col){
                        res.insert(bhead->row,bhead->col,bhead->val);
                        bhead = bhead->next;
                    }
                    else{
                        res.insert(ahead->row,ahead->col,ahead->val);
                        ahead = ahead->next;
                    }
                }
                
                else if(ahead->row < bhead->row){
                        res.insert(ahead->row,ahead->col,ahead->val);
                        ahead = ahead->next;
                }

                else{
                    res.insert(bhead->row,bhead->col,bhead->val);
                    bhead = bhead->next;
                }
            }

            while(ahead){
                res.insert(ahead->row,ahead->col,ahead->val);
                ahead = ahead->next;
            }

            while(bhead){
                res.insert(bhead->row,bhead->col,bhead->val);
                bhead = bhead->next;
            }

            res.printMatrix();

        }

        Node *merge(Node *first, Node *second){
            Node* temp = new Node;
            Node* mergehead = temp;
            Node *firsthead = first;
            Node *secondhead = second;
            while(firsthead!=NULL && secondhead!=NULL){
                if(firsthead->row == secondhead->row){
                    if(firsthead->col <= secondhead->col){
                        temp->next=firsthead;
                        firsthead = firsthead->next;
                    }
                    else{
                        temp->next=secondhead;
                        secondhead = secondhead->next;
                    }
                }

                else if(firsthead->row < secondhead->row){
                    temp->next=firsthead;
                    firsthead = firsthead->next;
                }
                else{
                    temp->next=secondhead;
                    secondhead = secondhead->next;
                }
                temp = temp->next;
            }
            while(firsthead){
                temp->next=firsthead;
                firsthead=firsthead->next;
                temp=temp->next;
            }

            while(secondhead){
                temp->next=secondhead;
                secondhead=secondhead->next;
                temp=temp->next;
            }

            return mergehead->next;

        }
        

        Node *findMid(Node *head){
            Node* f = head;
            Node* s = head;
            while(s!=NULL && f->next!=NULL && f->next->next!=NULL){
                f = f->next->next;
                s = s->next;
            }
            return s;
        }

        Node* sort(Node* head){
            if(!head->next)
                return head;
            
            Node* middle = new Node;
            middle = findMid(head);
            Node* sechead = middle->next;
            middle->next = NULL;
            Node *firsthalf = sort(head);
            Node *sechalf = sort(sechead);
            Node  *final = merge(firsthalf,sechalf);
            return final;

        }

        ll_sparseMatrix transpose(int flag){
            ll_sparseMatrix transp;
            transp.rows=cols;
            transp.cols=rows;
            Node* temp = head;
            while(temp){
                transp.insert(temp->col,temp->row,temp->val);
                temp=temp->next;
            }
            
            transp.head = sort(transp.head);
            transp.rows=cols;
            transp.cols=rows;

            //if flag == 1 it will print transpose otherwise only return it.
            if(flag==1){
                transp.printMatrix();
                return transp;
            }
            return transp;
            
        }

		// Multiply
        void multiply(ll_sparseMatrix &b){
            if(cols!=b.rows){
                return;
            }
            ll_sparseMatrix result(rows,b.cols);
            b=b.transpose(0);
            Node *ahead = head;
            X multiply=0;
            while(ahead){
                Node *bhead = b.head;
                while(bhead){
                    if(ahead->col == bhead->col){
                        multiply = ahead->val * (bhead->val);
                        result.insert(ahead->row,bhead->row,multiply);
                    }
                    bhead=bhead->next;
                }
                ahead=ahead->next;
            }

            result.head = sort(result.head);
            Node *fw,*prev;
            prev = result.head;
            fw = result.head->next;
            X temp_sum=0;
            while(fw){
                if(fw->row == prev->row && fw->col == prev->col){
                    temp_sum = fw->val + prev->val;
                    if(temp_sum!=0){
                        prev->val = temp_sum;
                        Node *temp = fw;
                        prev->next = fw->next;
                        free(temp);
                        fw = prev->next;
                    }
                    else{
                        fw=fw->next;
                        prev->row = fw->row;
                        prev->col = fw->col;
                        prev->val = fw->val;
                        prev->next = fw->next;
                        free(fw);
                        fw = prev->next;
                    }
                }
                else{
                    prev=prev->next;
                    fw = fw->next;
                }
            }

            result.printMatrix();
        }
};

int main(){

    // 1. Addition 2. Transpose 3. Multiplication
    int operation,rows,cols;
    cin>>operation;

    // ADDITION
    if(operation==1){
        // ROW and COLUMN input for matrix a
        cin>>rows>>cols;
        ll_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        // ROW and COLUMN input for matrix b
        cin>>rows>>cols;
        ll_sparseMatrix<double>b(rows,cols);
        b.accept_matrix();
        a.add(b);
    }

    // TRANSPOSE
    else if(operation==2){
        cin>>rows>>cols;
        ll_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        a.transpose(1);    //Pass 1 to print output . 0 to return output as object vector_sparsematrix 
    }

    // MULTIPLICATION
    else if(operation==3){
        cin>>rows>>cols;
        ll_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        cin>>rows>>cols;
        ll_sparseMatrix<double>b(rows,cols);
        b.accept_matrix();
        a.multiply(b);
    }    
    return 0;

}
