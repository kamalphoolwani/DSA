#include <iostream>
#include<cstring>
using namespace std;

template<class X>

class deque{
    X *arr;
    int head;
    int rear;
    int curr_size;
    int asize;
    char temp;

    public:
        deque(){
            arr = new X[100000];
            head = -1;
            rear = -1;
            asize = 100000;
            curr_size=0;
            
        }

        deque(int n, X x){
            arr = new X[n];
            asize = n;
            curr_size=n;
            head = 0;
            for(int i=0; i<n; i++){
                arr[i] = x;
                rear = i;
            }
        }

        void push_back(X x){
            if(isFull()){
                increase();
                rear += 1;
                arr[rear] = x;
            }

            else if(empty()){
                head = 0;
                rear = 0;
                arr[rear] = x;
            }
            else if(rear == asize-1){
                rear = 0;
                arr[rear] = x;
            }
            else{
                rear += 1;
                arr[rear] = x;
            }
            curr_size += 1;
            return;
        }

        void pop_back(){
            if(empty())
                return;
            else if(head == 0 && rear == 0){
                head = -1;
                rear = -1;
                curr_size -= 1;
                return;
            }
            else if(rear==0){
                rear=asize-1;
                curr_size-=1;
                return;
            } 
            rear-=1;
            curr_size -=1;
            return;
        
        }

        void push_front(X x){
            if(isFull()){
                increase();
                head = asize - 1;
                arr[head] = x;
                
            }
            else if(empty()){
                head = 0;
                rear = 0;
                arr[head]=x;
            }
            else if(head==0){
                head = asize - 1;
                arr[head] = x;

            }
            else{
                head-=1;
                arr[head]=x;
            }
            curr_size+=1;
            return;
        }

        void pop_front(){
            if(empty())
                return;
            else if(head == 0 && rear == 0){
                head = -1;
                rear = -1;
                curr_size-=1;
                return;
            }
            head = (head + 1) % asize;
            curr_size -=1;
            return;

        }
        
        X front(){
            if(empty())
                return 0;
            return arr[head];
        }


        X back(){
            if(empty())
                return 0;
            return arr[rear];
        }

        bool empty(){
            if(curr_size)
                return false;
            return true;
        }
        
        bool isFull(){
            if((curr_size == asize)|| (head==0 && rear == asize - 1) || (head == (rear + 1)%asize))
                return true;
            return false;
        }

        int size(){
            return curr_size;
        }

        void increase(){
            int nsize = 2*asize;
            int index = 0,i=0;
            X *temp = new X[nsize];
            while(i<curr_size){
                index = (head + i) % asize;
                temp[i] = arr[index];
                i++;
            }
            head = 0;
            rear = curr_size - 1;
            delete []arr;
            arr = temp;
            asize = nsize;
            return;
        }

        void resize(int x, X d){
            if(x<curr_size){
                int diff = curr_size - x;
                for(int i=1; i<=diff; i++)
                    pop_back();
            }

            else if(x>curr_size){
                int diff = x-curr_size;
                for(int i=1; i<=diff; i++)
                    push_back(d);
            }

            return;
        }

        void clear(){
            head = -1;
            rear = -1;
            curr_size=0;
        }

        X operator [](int n){
            int index = (head + n)%asize;
            return arr[index];
        }

        void diplay(){
            int i = head;
            while(i!=rear+1){
                cout<<arr[i]<<" ";
                if(i==asize-1){
                    i=0;
                    continue;
                }
                i = i+1; 
            }
            cout<<endl;
        }
        

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    deque<float> d;
    cout<<"Empty: "<<d.empty()<<endl;
    d.push_back(1.33);
    d.push_front(2.89);
    d.diplay();
    cout<<"Size: "<<d.size()<<endl;
    cout<<d.back();

   // deque<int> q;
   //deque<int> q(size,dummy);
    // int ch,n,k,indx;
    // int num,dummy,dummy1;
    // while(1){
	// 	//cout<<"enter choice : ";
	// 	cin>>ch;
	// 	switch(ch){
	// 		case 1:
	// 			cin>>num;
	// 			q.push_front(num);
	// 			break;	
	// 		case 2:
	// 			cout<<q.pop_front()<<endl;
	// 			break;	
	// 		case 3:
	// 			cin>>num;
	// 			q.push_back(num);
	// 			break;
	// 		case 4:
	// 			cout<<q.pop_back()<<endl;
	// 			break;		
	// 		case 5:
	// 			Q.front();
	// 			break;
	// 		case 6:
	// 			Q.back();
	// 			break;
	// 		case 7:
	// 			if(Q.empty())
	// 				cout<<"true"<<endl;
	// 			else
	// 				cout<<"false"<<endl;
	// 			break;
	// 		case 8:
	// 			cout<<q.size()<<endl;
	// 			break;
	// 		case 9:
	// 			cin>>k>>dummy;
	// 			q.resize(k,dummy1);
	// 			break;
	// 		case 10:
	// 			q.clear();
	// 			break;
	// 		case 11:
	// 			//cout<<"enter n : ";
	// 			cin>>indx;
	// 			cout<<Q[indx]<<endl;
	// 			break;
	// 		case 12:
	// 			q.display();
	// 			break;			

	// 	}
	// }

    return 0;
}