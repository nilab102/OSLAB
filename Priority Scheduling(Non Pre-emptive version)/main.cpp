#include <iostream>
#include <queue>
using namespace std;
struct Proccess {
    int pId;
    int arrivalTIme;
    int brustTime;
    int priorityTime;

    Proccess(int pid, int artime, int btime,int ptTime) {
        pId = pid;
        arrivalTIme = artime;
        brustTime = btime;
        priorityTime=ptTime;
    }


};
struct Comparearr {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.arrivalTIme > p2.arrivalTIme;
    }
};
struct Comparept {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.priorityTime > p2.priorityTime;
    }
};
void getinput(int x, priority_queue<Proccess, vector<Proccess>, Comparearr> *Q){

    queue<int> cputime;
    queue<int> arivtime;
    queue<int> priotiytime;
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

    cout<<endl<<"Enter the Priority";

    for (int y=0;y<x;y++){
        int con ;
        cin>>con;
        priotiytime.push(con);
    }


    for (int y=0;y<x;y++){
        Q->push(Proccess(y+1,arivtime.front(),cputime.front(),priotiytime.front()));
        cputime.pop();
        arivtime.pop();
        priotiytime.pop();
    }


}
int main() {
    int time = 0 ;
    auto avgWaitTime=0.00,avgTurnAroundTime=0.00;

    priority_queue<Proccess, vector<Proccess>, Comparearr> Q;
    priority_queue<Proccess, vector<Proccess>, Comparept> mQ;
    cout<<"Enter Number Of Process ";
    int x;
    cin>>x;

    getinput(x,&Q);

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