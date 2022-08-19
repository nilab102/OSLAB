#include <iostream>
#include <stack>
using namespace std;
stack<int> s;
void PrintStack()
{
    stack<int> temp;
    while (s.empty() == false)
    {
        temp.push(s.top());
        cout << s.top() << " ";
        s.pop();

    }

    while (temp.empty() == false)
    {
        int t = temp.top();
        temp.pop();
        s.push(t);
    }
}
void StackTransfer()
{
    stack<int> temp;
    int flag=0;
    while (s.empty() == false)
    {
        temp.push(s.top());
        s.pop();

    }

    while (temp.empty() == false)
    {
        int t = temp.top();

        temp.pop();

        // To restore contents of
        // the original stack.
       if(flag) s.push(t);
       flag=1;
    }
}
void StackDelete (int x)
{
    stack<int> temp;
    while (s.empty() == false)
    {
        temp.push(s.top());
        s.pop();

    }

    while (temp.empty() == false)
    {
        int t = temp.top();

        temp.pop();

        // To restore contents of
        // the original stack.
        if(x!=t) s.push(t);
    }
}
bool contains (int x)
{
    bool flag=false;
    stack<int> temp;
    while (s.empty() == false)
    {
        temp.push(s.top());
        s.pop();

    }

    while (temp.empty() == false)
    {
        int t = temp.top();
        if(t==x)flag=true;
        temp.pop();

        // To restore contents of
        // the original stack.
       s.push(t);
    }
    return flag;
}


int main() {
    int frame=3;
    int arr[] ={7,0,1,2,0,3,0,4,2,3,0,3,0,3,2,1,2,0,1,7,0,1};
    int n=sizeof(arr)/sizeof (arr[0]);
    int check=0;
    int count_pageFault=0,count_Hit=0;
   for (int i=0;i<n;i++){

       if(contains(arr[i])){
           StackDelete(arr[i]);
           s.push(arr[i]);
           PrintStack();
           cout<<endl;
           count_Hit++;
       }
       else{
           if(s.size()<frame && check==0){
               s.push(arr[i]);
               PrintStack();
               cout<<endl;
               count_pageFault++;

           }else{
               check=1;
               StackTransfer();
               s.push(arr[i]);
               PrintStack();
               cout<<endl;
           }
           count_pageFault++;
       }

   }
    cout<<"\nTotal Page fault "<<count_pageFault;
    cout<<"\nTotal Page Hit "<<count_Hit;

}
