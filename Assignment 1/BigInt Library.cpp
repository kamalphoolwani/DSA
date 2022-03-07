#include<iostream>

using namespace std;

class bigInt{
    // to long long int
    long long int strtoint(string b){
        long long int res = 0;
        for(int i=0; i<b.length(); i++){
            res = res*10 + (b[i]-'0');
        }

        return res;
    }

    string maximum(string a, string b){
        while(a[0] == '0' && a.size()!=1)
            a.erase(0,1);
        
        while(b[0] == '0' && b.size()!=1)
            b.erase(0,1);
        
        long long int la = a.size();
        long long int lb = b.size();

        if(la>lb)
            return a;
        else if(lb>la)
            return b;

        else{
            for(int i=0; i<la; i++){
                if(a[i]>b[i])
                    return a;
                else if(b[i]>a[i])
                    return b;
                else    
                    continue;
            }
        }
        return a;
    }

    //checks if str1 > str2 numerically
    bool s_maximum(string a, string b) {    
        if(a == b)
            return false;

        if(a == maximum(a, b))
            return true;

        return false;
    }

    //BigInt arithmetic modulos

    string mod(string a, string b) {
        long long int la = a.size();
        long long int lb = b.size();
        string tempa;

        while(s_maximum(a,b)){
            if(la>lb){
                tempa=a.substr(0,lb+1);
            }
            else{
                tempa = a.substr(0,lb);
            }
            long long int toconcat = tempa.size();
            la = a.size();
            while(s_maximum(tempa,b)){
                    tempa=sub(tempa,b);
            }
            if(tempa==b)
                tempa=sub(tempa,b);
            
            if(toconcat>=la)
                a=tempa;
            else
                a = tempa + a.substr(toconcat);

            while(a[0]=='0' && a.size()!=1) 
                    a.erase(0,1);
        }
        return a;
    }

    //to check if following character isOperator or not
    bool isOperator(char c){
        if(c=='+' || c=='-' || c=='x'){
            return true;
        }
        return false;
    }

    public:

        // addition bigInteger

        string add(string a, string b){
            string s = "";
            string ans="";
            int i = a.size()-1;
            int j = b.size()-1;
            int isum=0,carry=0;

            while(i>=0  && j>=0){
                isum = (a[i] - '0') + (b[j]-'0') + carry;
                s += to_string(isum%10);
                carry = isum/10;
                i-=1;
                j-=1;
            }

            while(i>=0){
                isum = (a[i]-'0') + carry;
                s += to_string(isum%10);
                carry = isum/10;
                i-=1;
            }

            while(j>=0){
                isum = (b[j]-'0') + carry;
                s += to_string(isum%10);
                carry = isum/10;
                j-=1;
            }

            while(carry){
                s += to_string(carry%10);
                carry = carry/10;
            }

            for(i = s.size()-1; i>=0; i--){
                ans+=s[i];
            }

            //erasing any leading zero
            while(ans[0] == '0' && ans.size()!=1)
                ans.erase(0,1);

            return ans;

        }

        //bigIntegerSubtraction
        string sub(string a, string b){

            if(b==maximum(a,b)){
                string temp = b;
                b = a;
                a = temp;
            }

            string s ="";
            string ans="";
            int i = a.size() - 1;
            int j = b.size() - 1;
            int curr_sub = 0,curr_a=0,curr_b=0,trail_zero=0;

            while(j>=0){
                curr_a = a[i] - '0';
                curr_b = b[j] - '0';

                // case where upper digit is smaller than lower and we need to take borrow
                if(curr_a<curr_b){
                    curr_sub = 10 + (a[i]-'0') - (b[j]-'0');
                    a[i-1]-=1;
                }
                else{
                    curr_sub = (a[i]-'0') - (b[j]-'0');
                }
                s+=to_string(curr_sub);
                i-=1;
                j-=1;
            }

            //Appending remaining digit of first number
            if(i>=0){
                while(i>=0){
                    curr_a = a[i]-'0';
                    if(curr_a<0){
                        s+=to_string(curr_a+10);
                        a[i-1]-=1;
                    }
                    else if(curr_a>=0)
                        s+=to_string(curr_a);
                    i-=1;
                }
            }

            //reversing traversing string to get the answer
            for(i = s.size()-1; i>=0; i--){
                ans+=s[i];
            }

            // erase leading zeros
            while(ans[0]=='0' && ans.size()!=1) 
                ans.erase(0,1);
            
            return ans;
        }

        //bigInt Multiplication

        string multiply(string a, string b)
        {
            if(a.size() > b.size()) {
                string temp = b;
                b = a;
                a = temp;
            }

            string ans = "0";
            for(int i=a.length()-1; i>=0; --i)
            {
                string temp = b;
                int curr = a[i]-'0';
                int carry = 0, tm=0;

                for(int j=temp.size()-1; j>=0; --j)
                {
                    tm = ((temp[j]-'0') * curr) + carry;

                    if(tm > 9)
                    {
                        carry = tm/10;
                        tm = tm%10;
                    }
                    else
                        carry = 0;

                    temp[j] = (char)(tm + '0');
                }

                if(carry > 0)
                    temp.insert(0, 1, (carry+'0'));
                
                // appending 0 to shift the digit
                temp.append((a.size()-i-1), '0');

                ans = add(ans, temp);
            }

            //erasing any leading zero
            while(ans[0] == '0' && ans.size()!=1)
                ans.erase(0,1);

            return ans;
        }

        //power
        string pow(string a, string b){
            string res = "1";
            long long int temp = strtoint(b);
            while(temp>0){
                if(temp%2==1)
                    res = multiply(res,a);
                a = multiply(a,a);
                temp = temp/2;
            }
            return res;
        }

        // BigInt factorial
        string fact(string n) {                     
            if(n=="0")
                return "1";
            string ans = "1",tn="";
            int t = stoi(n);
            for(int i=2; i<=t; i++) {
                tn = to_string(i);
                ans = multiply(ans, tn);
            }
            return ans;
        }

        // BigInt GCD
        string gcd(string a, string b){
            string temp,ans;
            if(a==b)
                return a;

            if(s_maximum(b,a)){
                swap(a,b);
            }

            while(b!="0"){
                temp = mod(a,b);
                a = b;
                b = temp;
            }
            
            ans=a;
            return ans;
        }

        // Calculator evaluation
        string calculator(string expression){
            int i=0;
            int curr =0;
            int prev = -1;
            string operand1="", operand2="",ans;

            //Firstly calculating all multiplication. Since it has highest precedence from addition and substraction
            while(expression[i]!='\0'){
                while(!(isOperator(expression[i])) && (expression[i]!='\0') ){
                    operand1+=expression[i];
                    i+=1;
                    curr=i;
                }

                if(expression[i]=='+' || expression[i]=='-'){
                    prev=curr;
                    operand1="";
                    i+=1;
                }

                else if(expression[i]=='x'){
                    i+=1;
                    while(!(isOperator(expression[i])) && (expression[i]!='\0')){
                        operand2+=expression[i];
                        i+=1;
                        curr=i;
                    }
                    ans = multiply(operand1,operand2);
                    expression = expression.substr(0,prev+1) + ans + expression.substr(curr);
                    operand1="";
                    operand2="";
                    i=prev+1;
                }
            }

            //Calculating addition and substraction
            operand1="",operand2="";
            prev=-1,curr=0,i=0;
            while(expression[i]!='\0'){
                //Storing operand1
                while(!(isOperator(expression[i])) && (expression[i]!='\0') ){
                    operand1+=expression[i];
                    i+=1;
                    curr=i;
                }

                //Evaluating additon
                if(expression[i]=='+'){
                    i+=1;
                    while(!(isOperator(expression[i])) && (expression[i]!='\0')){
                        operand2+=expression[i];
                        i+=1;
                        curr=i;
                    }
                    ans = add(operand1,operand2);
                    expression = ans + expression.substr(curr);
                    operand1=ans;
                    operand2="";
                    i=ans.size();
                }

                //evaluating substraction
                if(expression[i]=='-'){
                    i+=1;
                    while(!(isOperator(expression[i])) && (expression[i]!='\0')){
                        operand2+=expression[i];
                        i+=1;
                        curr=i;
                    }
                    ans = sub(operand1,operand2);
                    expression = ans + expression.substr(curr);
                    operand1=ans;
                    operand2="";
                    i=ans.size();
                }
            }

            return ans;
        }

};

int main(){
    int option;
    cin>>option;
    bigInt operation;

    // Exponentiation
    if(option==1){
        string base,exponent;
        cin>>base>>exponent;
        cout<<operation.pow(base,exponent)<<endl;
    }

    // GCD 
    else if(option==2){
        string a,b;
        cin>>a>>b;
        cout<<operation.gcd(a,b)<<endl;
    }

    // Factorial
    else if(option==3){
        string num;
        cin>>num;
        cout<<operation.fact(num)<<endl;
    }

    // Calculator
    else{
        string expression;
        cin>>expression;
        cout<<operation.calculator(expression)<<endl;
    }
    return 0;
}


