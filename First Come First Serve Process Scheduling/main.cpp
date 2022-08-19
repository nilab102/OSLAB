#include <iostream>
#include <queue>
using namespace std;
struct Proccess {
    int pId;
    int arrivalTIme;
    int brustTime;

    Proccess(int pid, int artime, int btime) {
        pId = pid;
        arrivalTIme = artime;
        brustTime = btime;
    }


};
struct Compare {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.arrivalTIme > p2.arrivalTIme;
    }
};
void getinput(int x,queue<int>cputime,queue<int>arivtime, priority_queue<Proccess, vector<Proccess>, Compare> *Q){


    cout<<endl<<"Enter The Cpu Time";

    for (int y=0;y<x;y++){
        int temp ;
        cin>>temp;
        cputime.push(temp);
    }
    cout<<endl<<"Enter the arrival times";

    for (int y=0;y<x;y++){
        int temp ;
        cin>>temp;
        arivtime.push(temp);
    }


    for (int y=0;y<x;y++){
        Q->push(Proccess(y+1,arivtime.front(),cputime.front()));
        cputime.pop();
        arivtime.pop();
    }


}
int main() {
    int time = 0 ;
    auto totalWaitTime=0.00,totalTurnAroundTime=0.00;

    priority_queue<Proccess, vector<Proccess>, Compare> Q;
    cout<<"Enter Number Of Process ";
    int x;
    cin>>x;
    queue<int> cputime;
    queue<int> arivtime;
    getinput(x,cputime,arivtime,&Q);


while(Q.empty()== false){
    if(Q.top().arrivalTIme<=time){
        int wait=time -Q.top().arrivalTIme;
        cout<<"PId = "<<Q.top().pId<<" waitting time "<<wait<<" Turnaround Time: "<<wait+Q.top().brustTime<<endl;
        totalWaitTime=time-Q.top().arrivalTIme+totalWaitTime;
        totalTurnAroundTime=wait+Q.top().brustTime+totalTurnAroundTime;
    }

    time=time+Q.top().brustTime;

    Q.pop();
  }
cout<<"Average Waiting Time:"<<totalWaitTime/x<<endl;
    cout<<"Average Turnaround Time:"<<totalTurnAroundTime/x<<endl;



    return 0;
}