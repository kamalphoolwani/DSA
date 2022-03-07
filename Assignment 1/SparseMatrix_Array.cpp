#include<iostream>
using namespace std;

template<class X>
class vector_sparseMatrix{
    
    X sparse[500][3];
    public:
        int rows,cols,sparse_rows;
        bool flag=true;
        vector_sparseMatrix(int r, int c){
            rows=r;
            cols=c;
            sparse_rows=0;
            
            if(r<=0 || r>500 || c<=0 || c>500){
                flag=false;
                return;
            }
        }

        void accept_matrix(){   
            X temp=0;
            for(int i=0; i<rows; i++){
                for (int j = 0; j<cols; j++)
                {
                    cin>>temp;
                    if(temp!=0)
                        insert(i+1,j+1,temp);
                }
            }
        }

        //creation of sparse matrix
        
        void insert(int r, int c, X val){
            if(r<=0 || r>rows  || c<=0 || c>cols){
                return;
            }
            sparse[sparse_rows][0]=r;
            sparse[sparse_rows][1]=c;
            sparse[sparse_rows][2]=val;
            sparse_rows+=1; 
        }

        // void print_matrix();

        void print_sparse_matrix(){
            for(int i=0; i<sparse_rows; i++){
                for (int j = 0; j <3; j++){
                        cout<<sparse[i][j]<<" ";
                }
                cout<<endl;
            }           
        }
        void add(vector_sparseMatrix &b){
            if(rows!=b.rows || cols!=b.cols){
                cout<<"Matrix cannot be added!!"<<endl;
                return;
            }

            X result[500][3];
            int s_row_a = sparse_rows;
            int s_row_b = b.sparse_rows;
            int i=0,j=0,k=0;
            while(i<s_row_a && j<s_row_b){
                //Condition for checking if both have same row value
                if(sparse[i][0]==b.sparse[j][0]){
                    //For checking if corresponding columns are same
                    if(sparse[i][1]==b.sparse[j][1]){
                        X temp = sparse[i][2] + b.sparse[j][2];
                        // if addition of both results in non zero value then only we will add to result
                        if(temp!=0){
                            result[k][0]=sparse[i][0];
                            result[k][1]=sparse[i][1];
                            result[k][2]=temp;
                            k+=1;
                        }
                        i+=1;
                        j+=1;
                    }
                    //if columns are different
                    else{
                        //if column value of matrix 'a' smaller than matrix 'b'. We add data of a in result
                        if(sparse[i][1]<b.sparse[j][1]){
                            result[k][0]=sparse[i][0];
                            result[k][1]=sparse[i][1];
                            result[k][2]=sparse[i][2];
                            k+=1;
                            i+=1;
                        }
                        //if column value of matrix 'b' smaller than matrix 'a'. We add data of b in result
                        else{
                            result[k][0]=b.sparse[j][0];
                            result[k][1]=b.sparse[j][1];
                            result[k][2]=b.sparse[j][2];
                            k+=1;
                            j+=1;
                        }
                    }
                }
                //if value of rows are different in both a & b
                else{
                    //vale of row of a smaller than row of b
                    if(sparse[i][0]<b.sparse[j][0]){
                            result[k][0]=sparse[i][0];
                            result[k][1]=sparse[i][1];
                            result[k][2]=sparse[i][2];
                            k+=1;
                            i+=1;
                    }
                    else{
                        result[k][0]=b.sparse[j][0];
                        result[k][1]=b.sparse[j][1];
                        result[k][2]=b.sparse[j][2];
                        k+=1;
                        j+=1;
                    }
                }
            }

            while(i<s_row_a){
                result[k][0]=sparse[i][0];
                result[k][1]=sparse[i][1];
                result[k][2]=sparse[i][2];
                k+=1;
                i+=1;  
            }

            while(j<s_row_b){
                result[k][0]=b.sparse[j][0];
                result[k][1]=b.sparse[j][1];
                result[k][2]=b.sparse[j][2];
                k+=1;
                j+=1;        
            }

            for(i=0; i<k; i++){
                for(j=0; j<3; j++){
                    cout<<result[i][j]<<" ";
                }
                cout<<endl;
            }
        }

        //Matrix transpose
        vector_sparseMatrix transpose(int flag){
            int total[cols];
            int index[cols+1];
            for(int i=0; i<cols;i++){
                total[i]=0;
                index[i]=0;
            }
            index[cols+1]=0;
            int loc,temp_col;
            vector_sparseMatrix<X>result(sparse_rows,3);

            for(int i=0; i<sparse_rows; i++){
                temp_col = sparse[i][1];
                total[temp_col]+=1;
            }
            for(int i=1; i<=cols;i++){
                index[i]=index[i-1]+total[i-1];
            }

            for(int i=0;i<sparse_rows;i++){
                temp_col=sparse[i][1];
                loc=index[temp_col];
                result.sparse[loc][0]=sparse[i][1];
                result.sparse[loc][1]=sparse[i][0];
                result.sparse[loc][2]=sparse[i][2];
                index[temp_col]+=1;
            }
            
            //storing value of sparse_rows of original matrix in resultant matrix(transpose matrix)
            result.sparse_rows=sparse_rows;

            //flag=1 : Output to print  else only return the tranpose
            if(flag==1){
                for(int i=0; i<sparse_rows;i++){
                    for(int j=0; j<3; j++){
                        cout<<result.sparse[i][j]<<" ";
                    }
                    cout<<endl;
                }
                return result;
            }

            return result;
        }

        void multiply(vector_sparseMatrix &b){
            if(cols!=b.rows){
                cout<<"Invalid Dimesnsion!!";
                return;
            }
            int i=0,j=0,k=0;
            vector_sparseMatrix<X>b_transpose(sparse_rows,3);
            int b_sparse_rows = b.sparse_rows;
            b_transpose=b.transpose(0);
            int pos_size = 0;

            //possible number of rows in output
            for(i=0; i<sparse_rows; i++){
                for(j=0; j<b_sparse_rows;j++){
                    if(sparse[i][1]==b_transpose.sparse[j][1])
                        pos_size+=1;
                }
            }

            X temp_result[pos_size][3];
            
            X sum=0;
    
           //storing all the produict term in result where column of both matrix are same
            for(i=0;i<sparse_rows;i++){
                for(j=0;j<b_sparse_rows;j++){
                    if(sparse[i][1]==b_transpose.sparse[j][1]){
                        temp_result[k][0]=sparse[i][0];
                        temp_result[k][1]=b_transpose.sparse[j][0];
                        temp_result[k][2]=sparse[i][2]*b_transpose.sparse[j][2];
                        k+=1;
                    }
                }
            }

            //sorting the resultant matrix on basis of both row and column
            sort(temp_result,pos_size);

            //array for storing final result after merging and adding values of same row and column
            X ans[pos_size][3];
            i=0;
            k=0;
            ans[k][0]=temp_result[i][0];
            ans[k][1]=temp_result[i][1];
            ans[k][2]=temp_result[i][2];
            i+=1;
            while(i<pos_size){
                if((temp_result[i][0]==ans[k][0]) && (temp_result[i][1]==ans[k][1])){
                    ans[k][2]=temp_result[i][2] + ans[k][2];    
                }
                else{
                    k+=1;
                    ans[k][0]=temp_result[i][0];
                    ans[k][1]=temp_result[i][1];
                    ans[k][2]=temp_result[i][2];
                    
                }
                i+=1;
            }
            //to print the final output
            for(i=0;i<=k;i++){
                for(j=0;j<3;j++){
                    cout<<ans[i][j]<<" ";
                }
                cout<<endl;
            }
        }

        //sort the array by row and column
        void sort(X a[][3],int pos_size){
            //sorting by row
            int temp;
            X temp_value;
            for(int i=0; i<pos_size-1; i++){
                for(int j=i+1;j<pos_size;j++){
                    if(a[i][0]>a[j][0]){
                        temp=a[i][0]; 
                        a[i][0]=a[j][0]; 
                        a[j][0]=pos_size; 
                        temp=a[i][1]; 
                        a[i][1]=a[j][1]; 
                        a[j][1]=temp; 
                        temp_value=a[i][2]; 
                        a[i][2]=a[j][2]; 
                        a[j][2]=temp_value; 
                    }
                }
            }

            //sorting by column
            temp=0;
            temp_value=0;
            for(int i=0; i<pos_size; i++){
                for(int j=i+1; j<pos_size;j++){
                    //If row value equal then we check for column and do swap
                    if(a[i][0]==a[j][0]){
                        if(a[i][1]>a[j][1]){
                            temp=a[i][0]; 
                            a[i][0]=a[j][0]; 
                            a[j][0]=temp; 
                            temp=a[i][1]; 
                            a[i][1]=a[j][1]; 
                            a[j][1]=temp; 
                            temp_value=a[i][2]; 
                            a[i][2]=a[j][2]; 
                            a[j][2]=temp_value;
                        }
                    }
                }
            }
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
        vector_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        // ROW and COLUMN input for matrix b
        cin>>rows>>cols;
        vector_sparseMatrix<double>b(rows,cols);
        b.accept_matrix();
        a.add(b);
    }

    // TRANSPOSE
    else if(operation==2){
        cin>>rows>>cols;
        vector_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        a.transpose(1);    //Pass 1 to print output . 0 to return output as object vector_sparsematrix 
    }

    // MULTIPLICATION
    else if(operation==3){
        cin>>rows>>cols;
        vector_sparseMatrix<double>a(rows,cols);
        a.accept_matrix();
        cin>>rows>>cols;
        vector_sparseMatrix<double>b(rows,cols);
        b.accept_matrix();
        a.multiply(b);
    }    
    return 0;
}