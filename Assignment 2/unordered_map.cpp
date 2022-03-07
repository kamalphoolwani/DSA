#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

template <class T, class U>

class map
{
  struct Node
  {
    U val;
    T key;
    Node *next;
  };
  Node *arr[99787];
  const int M = 99787;
  int index = 0;

  public:
    T keymp;
    U valmp;
    map()
    {
      for (int i = 0; i < 99787; i++)
        arr[i] = NULL;
    }

    void insert(T k, U new_data)
    {
      index = hashVal(k);
      Node *new_node = new Node();
      new_node->val = new_data;
      new_node->key = k;
      new_node->next = NULL;
      if (arr[index] == NULL)
      {
        arr[index] = new_node;
        return;
      }
      else
      {
        Node *last = arr[index];
        while (last->next != NULL)
        {
          if (last->key == k)
          {
            last->val = new_data;
            return;
          }
          last = last->next;
        }
        if (last->key == k)
        {
          last->val = new_data;
          return;
        }
        last->next = new_node;
        return;
      }
    }

    int hashVal(T key)
    {
      ostringstream streamObj;
      string k = "";
      streamObj << key;
      k = streamObj.str();
      int i, hVal = 0, j = 0, len = k.length();
      for (i = 0; i < len; i++)
      {
        int temp = (k[i] * pow(31, i));
        temp = temp % M;
        hVal = (hVal + temp) % M;
      }
      return hVal;
    }

    bool find(T key)
    {
      int hash_val = hashVal(key);

      Node *temp = arr[hash_val];
      while (temp != NULL)
      {
        if (temp->key == key)
          return true;
        temp = temp->next;
      }
      return false;
    }

    void erase(T key)
    {
      int hValue = hashVal(key);
      Node *temp = arr[hValue];
      Node *prev = NULL;

      // If head node itself holds
      // the key to be deleted
      //cout<<"step 1";
      if (temp != NULL && temp->key == key)
      {
        // cout<<"step 2";
        arr[hValue] = temp->next; // Changed head
        delete temp;              // free old head
        return;
      }

      // Else Search for the key to be deleted,
      // keep track of the previous node as we
      // need to change 'prev->next' */
      else
      {
        // cout<<" step 3";
        while (temp != NULL && temp->key != key)
        {
          prev = temp;
          temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL)
          return;

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
        return;
      }
    }

    U operator[](T key)
    {
      static U  defaultValue;
      int hash_val = hashVal(key);

      Node *temp = arr[hash_val];
      while (temp != NULL)
      {
        if (temp->key == key)
          return temp->val;
        temp = temp->next;
      }
      return defaultValue;
    }

    void print()
    {
      for (int i = 0; i < 99787; i++)
      {
        Node *temp = arr[i];
        if (temp != NULL)
        {
          cout << "HashValue-" << i << "  "; //check map;
          while (temp != NULL)
          {
            cout << "key-" << temp->key << " value-" << temp->val << "     ";
            temp = temp->next;
          }
          cout << endl;
        }
      }
      return;
    }
};

/**************************** COUNT DISTINCT *****************************************/

template<typename T>
vector<int> countDistinct(vector<T> arr,int size, int k){
    // cout<<"Functio Start"<<endl;
    int i=0, count=0,t;
    map<T,int> mp;
    vector<int> ans;
    if(size==0)
        return ans;
    if(k>size)
        return ans;

    while (i < k)
    {
        if ((t = mp[arr[i]]) == 0)
        {
            count += 1;
        }

        t += 1;
        mp.insert(arr[i], t);

        i += 1;
    }

    // cout<<count<<endl;
    ans.push_back(count);

    while (i < size)
    {
        if ((t = mp[arr[i - k]]) == 1)
        {
            count -= 1;
        }
        t -= 1;
        mp.insert(arr[i - k], t);

        if ((t = mp[arr[i]]) == 0)
        {
            count += 1;
        }

        mp.insert(arr[i], t + 1);
        // cout<<count<<endl;
        ans.push_back(count);
        i += 1;
    }
    // cout<<"Function End"<<endl;
    return ans;
}



int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    vector<string> arr;
    vector<int> res;
    string temp; 
    /* 
        string temp;
        vector<string> arr;
        int temp;
        vector<int> arr;
        float temp;
        vector<float> arr;
    */
    int n,k;
    cin>>n>>k;
    for(int i=0; i<n; i++){
        cin>>temp;
        arr.push_back(temp);
    }

   res = countDistinct<string>(arr,n,k);
    
    for(int i : res)
        cout<<i<<" ";
    

    /*** MAP FUNCTIONALITY *********/
    // map<int, int> m;
    // int c;
    // int key, val;
    // vector<int> vec;
    // vector<int> v;
    // while (1)
    // {
    //     cin >> c;
    //     switch (c)
    //     {
    //     case 1:
    //         cin >> key >> val;
    //         m.insert(key, val);
    //         break;
    //     case 2:
    //         cin >> key;
    //         m.erase(key);
    //         break;
    //     case 3:
    //         cin >> key;
    //         if (m.find(key))
    //         {
    //             cout << "present\n";
    //         }
    //         else
    //         {
    //             cout << "Not present \n";
    //         }
    //         break;
    //     case 4:
    //         cin >> key;
    //         cout << m[key] << endl;
    //         break;
    //     }
    // }

    return 0;
}
