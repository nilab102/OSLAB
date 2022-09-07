#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct file {
    string name;
    int size;
    int address;

} ;

int main() {
    int blocks;
    int remain;;
    int insertaddress=0;

    int SIZE;
    int searxh_size=2;
            cout<<"Enter how many files you want to create: \n";
            cin>>SIZE;
    cout<<"Enter total number of blocks: \n";
    cin>>blocks;
    remain=blocks;
    struct file  files[10000];
    for(int i = 0; i <SIZE; i++)
    {
        cout<<"\nEnter filename: ";
        string name1 ;
        cin>>name1;

        cout<<"\nEnter file size: ";
        int size  ;
        cin>>size ;
        if(size  < remain && (insertaddress+size ) < blocks)
        {
            files[i].name=name1;
            files[i].address=insertaddress;
            files[i].size=size ;
            insertaddress+=size ;
            cout<<"\nFile "<<name1<<" created";
        }
        else{
            cout<<"\nNot enough memory";
        }
    }

    for(int i=0; i<searxh_size; i++)
    {
        bool isFound = false;
        cout<<"Search filename :";
        string name1;
        cin>>name1;
        for(file f : files)
        {
            if( f.name.compare(name1)==0)
            {
                isFound = true;
                cout<<"File found in the blocks : ";
                for(int j=0; j<f.size; j++)
                {
                    cout<<f.address+j<<" , \n";
                }

            }
        }
        if( isFound==false )
        {
            cout<<"File not found\n";

        }
    }

    return 0;
}
