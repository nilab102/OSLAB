#include<iostream>
#include<cstdlib>
#include<climits>
#include<cstring>
#include<vector>
#include<iomanip>
using namespace std;
int total_head_movement=0;
int findclosestCylinder(int initial_pos, vector<bool> visited,vector<int> request_queue,int n)
{
    int min=INT_MAX,min_index=-1;
    for(int i=0;i<n;i++)
    {
        if(visited[i] == false && abs(initial_pos - request_queue[i]) < min)
        {
            min = abs(initial_pos - request_queue[i]);
            min_index = i;
        }
    }
    return min_index;

}

int applySSTFAlgo(vector<int> request_queue, int initial_pos,vector<bool> visited,vector<int> &seek_sequence,int n)
{
    int i=0;
    int completed=0,total_head_movement=0;
    while(completed!=n)
    {
        int min_index=findclosestCylinder(initial_pos,visited,request_queue,n);
        total_head_movement += abs(initial_pos - request_queue[min_index]);
        initial_pos = request_queue[min_index];
        seek_sequence[i++] = request_queue[min_index];
        visited[min_index]=true;
        completed++;
    }

    return total_head_movement;
}


int main()
{
    int n=8;
    vector<int> request_queue{ 176, 79, 34, 60, 92, 11, 41, 114 };
    int initial_pos = 50;

    vector<bool> visited(n,false);
    vector<int> seek_sequence(8);

    total_head_movement = applySSTFAlgo(request_queue,initial_pos,visited,seek_sequence,n);
    cout<<"\nSeek Sequence: ";
    for(int i=0;i<n;i++)
        cout<<seek_sequence[i]<<" ";
    cout<<"\nTotal No. of Head Movements: "<<total_head_movement;
    cout<<"\nAverage head movements:"<<total_head_movement/n;

    return 0;
}
