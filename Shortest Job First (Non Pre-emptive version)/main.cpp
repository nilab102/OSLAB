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
struct Comparearr {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.arrivalTIme > p2.arrivalTIme;
    }
};
struct Comparebrst {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.brustTime > p2.brustTime;
    }
};
void getinput(int x,queue<int>cputime,queue<int>arivtime, priority_queue<Proccess, vector<Proccess>, Comparearr> *Q){


    cout<<endl<<"Enter The Cpu Time";

    for (int y=0;y<x;y++){
        int con ;
        cin>>con;
        cputime.push(con);
    }
    cout<<endl<<"Enter the arrival times";

    for (int y=0;y<x;y++){
        int con ;
        cin>>con;
        arivtime.push(con);
    }


    for (int y=0;y<x;y++){
        Q->push(Proccess(y+1,arivtime.front(),cputime.front()));
        cputime.pop();
        arivtime.pop();
    }


}
int main() {
    int time = 0 ;
    auto avgWaitTime=0.00,avgTurnAroundTime=0.00;

    priority_queue<Proccess, vector<Proccess>, Comparearr> Q;
    priority_queue<Proccess, vector<Proccess>, Comparebrst> mQ;
    cout<<"Enter Number Of Process ";
    int x;
    cin>>x;
    queue<int> cputime;
    queue<int> arivtime;
    getinput(x,cputime,arivtime,&Q);

    while(Q.empty()== false ){
        while(Q.top().arrivalTIme<=time && Q.empty()== false) {
            mQ.push(Q.top());
            Q.pop();

        }

            if(mQ.empty()==false){
                int con =time -mQ.top().arrivalTIme;
                cout<<"PId = "<<mQ.top().pId<<" waitting time "<<con<<" Turnaround Time: "<<con+mQ.top().brustTime<<endl;
                avgWaitTime=time-mQ.top().arrivalTIme+avgWaitTime;
                avgTurnAroundTime=con+mQ.top().brustTime+avgTurnAroundTime;
                time=time+mQ.top().brustTime;
                mQ.pop();

            }
            if (Q.empty()==true && mQ.empty()==false){
                while(mQ.empty()==false){
                    int con =time -mQ.top().arrivalTIme;
                    cout<<"PId = "<<mQ.top().pId<<" waitting time "<<con<<" Turnaround Time: "<<con+mQ.top().brustTime<<endl;
                    avgWaitTime=time-mQ.top().arrivalTIme+avgWaitTime;
                    avgTurnAroundTime=con+mQ.top().brustTime+avgTurnAroundTime;
                    time=time+mQ.top().brustTime;
                    mQ.pop();
                }

            }

        }
    cout<<"Average Waiting Time:"<<avgWaitTime/x<<endl;
    cout<<"Average Turnaround Time:"<<avgTurnAroundTime/x<<endl;



    return 0;
}