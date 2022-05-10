#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

vector<long long int> inpArr(10000000);

struct Node{
    long long int val;
    int index;
};

class MinHeap{
    vector<Node> root;
    void minHeapify(int index){
        int left = 2*index + 1;
        int right = 2*(index + 1);
        int small = index;
        if(left<heap_size && root[left].val < root[small].val)
            small = left;
        if(right<heap_size && root[right].val < root[small].val)
            small = right;
        if(small != index){
            Node temp = root[index];
            root[index] = root[small];
            root[small] = temp;
            minHeapify(small);
        }
        return;
    }
    public:
        int heap_size;
        MinHeap(vector<Node> inp){
            root = inp;
            heap_size = inp.size();
            int i = (heap_size - 1)/2;
            while(i>=0){
                minHeapify(i);
                i-=1;
            }
        }

        Node getMin(){
            return root[0];
        }

        void replaceNode(Node temp){
            root[0] = temp;
            minHeapify(0);
            return;
        }

};

void deleteTempFile(int fileNum){
    string fileName = "temp_";
    // cout<<"Deleting Temporary Files!!"<<endl;
    for(int i=0; i<fileNum; i++){
        fileName += to_string(i) + ".txt";
        remove(fileName.c_str());
        fileName="temp_";
    }
    // cout<<"Temporary Files Deleted!!"<<endl;
}

void mergeKFiles(int numFiles, string outputName){
    ofstream outFile;
    vector<ifstream> inpfiles(numFiles);
    string inpName = "temp_";
    for(int i=0;i<numFiles; i++){
        inpName += to_string(i) + ".txt";
        inpfiles[i].open(inpName,ios::in);
        inpName = "temp_";
    }
    string temp;
    vector<Node> input(numFiles);
    for(int i=0; i<numFiles; i++){
        getline(inpfiles[i],temp,',');
        input[i].val = atoll(temp.c_str());
        input[i].index = i;
    }

    MinHeap mp(input);
    int count = 0;
    outFile.open(outputName,ios::out);
    Node atTop;
   
    int firstVal = 0;
    // cout<<"Final Merge in file: "<<outputName<<endl;
    while(count!=numFiles){
        atTop = mp.getMin();
        if(!firstVal){
            outFile<<to_string(atTop.val);
            firstVal=1;
        }
        else
            outFile<<","<<to_string(atTop.val);

        if(getline(inpfiles[atTop.index],temp,',')){
            atTop.val = atoll(temp.c_str());
            mp.replaceNode(atTop);
        }
        else{
            atTop.val = 10e12;
            mp.replaceNode(atTop);
            count+=1;
        }
    }
    for(int i=0; i<numFiles; i++){
        inpfiles[i].close();
    }
    outFile.close();
    // cout<<"Meging Done!!"<<endl;
    return;
}

int createTempFiles(string inp){
    ifstream inpfile;
    string temp;
    inpfile.open(inp,ios::in);
    int more_out = 1;
    int fileNum = 0;
    string tempFile = "temp_";
    int i;
    while(more_out==1){
        for(i=0; i<10000000; i++){
            if(getline(inpfile,temp,',')){
                inpArr[i] = atoll(temp.c_str());
            }
            else{
                more_out = 0;
                break;
            }
        }
        if(i>0){
            sort(inpArr.begin(),inpArr.begin() + i);
            tempFile += to_string(fileNum) + ".txt";
            ofstream outFile;
            outFile.open(tempFile,ios::out);
            for(int j=0; j<i; j++){
                if(j==i-1){
                    outFile<<to_string(inpArr[j]);
                }
                else{
                    outFile<<to_string(inpArr[j])<<",";
                }
            }
            outFile.close();
            // cout<<"Created Temporary File: temp_"<<fileNum<<".txt"<<endl;
            
            fileNum+=1;
            tempFile="temp_";
        }
    }
    inpfile.close();
    return fileNum;
}

int main(int argc, char* argv[]){
    if(argc!=3){
        cout<<"Invalid Number of Arguments!!"<<endl;
        return 0;
    }
    string inp = string(argv[1]);
    string out = string(argv[2]);
    // cout<<"Input File: "<<inp<<" ";
    // cout<<"Output File: "<<out<<endl;
    int fileNum;
    fileNum = createTempFiles(inp);
    if(fileNum>0){
        mergeKFiles(fileNum,out);
        deleteTempFile(fileNum);
    }
    

    return 0;
}