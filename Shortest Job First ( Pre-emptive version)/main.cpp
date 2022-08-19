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
struct compareID {
    bool operator()(Proccess const &p1, Proccess const &p2) {

        return p1.pId > p2.pId;
    }
};
priority_queue<Proccess, vector<Proccess>, compareID> idQ;
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
        idQ.push(Proccess(y+1,arivtime.front(),cputime.front()));
        cputime.pop();
        arivtime.pop();
    }


}
int main() {
    int time = 0 ;
    auto avgWaitTime=0.00,avgTurnAroundTime=0.00;
    priority_queue<Proccess, vector<Proccess>, Comparearr> Q;
    priority_queue<Proccess, vector<Proccess>, Comparebrst> mQ;

    vector< pair<int ,int>> vec,final,wait;
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
            if(mQ.top().brustTime==0)mQ.pop();
            else{
                time++;
                vec.push_back(make_pair(mQ.top().pId,time));
                int id=mQ.top().pId;
                int at=mQ.top().arrivalTIme;
                int bt=mQ.top().brustTime-1;
                mQ.pop();
                mQ.push(Proccess(id,at,bt));
                cout<<id<<"  "<<time<<endl;
            }

            while(mQ.empty()==false&&Q.empty()==true){
                if(mQ.top().brustTime==0)mQ.pop();
                else{

                    time++;
                    vec.push_back(make_pair(mQ.top().pId,time));
                    int id=mQ.top().pId;
                    int at=mQ.top().arrivalTIme;
                    int bt=mQ.top().brustTime-1;
                    mQ.pop();
                    mQ.push(Proccess(id,at,bt));
                    cout<<id<<"  "<<time<<endl;

                }
            }
            //  4 8 4 9 5 0 1 2 3

        }
    }
    cout<<endl<<"**************";
    final.push_back(make_pair(vec.begin()->first,0));
    for(int i=0;i<vec.size();i++)    if(vec[i].first!=vec[i+1].first ) final.push_back(make_pair(vec[i+1].first,vec[i].second));
    vec.clear();

 for(int i=0;i<final.size()-1;i++) cout<<endl<<final[i].first<<" " <<final[i].second;
cout<<endl<<"**************";


    for(int j=0;j<x;j++){
        int wtime=0,id;
        int lastfinish=0;
        //response time ber korte hoile flag set kore first value nile hbe
        for(int i=0;i<final.size()-1;i++) {

            if(final[i].first==j+1){
                 wtime=wtime+final[i].second-lastfinish;
                 lastfinish=final[i+1].second;
                 id=i;
                //cout<<endl<<final[i].first<<" " <<wtime;

            }


        }

        wait.push_back(make_pair(final[id].first,wtime));

    }
   for(int i=0;i<x;i++) {
       avgWaitTime=wait[i].second - idQ.top().arrivalTIme+avgWaitTime;
       avgTurnAroundTime=wait[i].second - idQ.top().arrivalTIme+Q.top().brustTime+avgTurnAroundTime;
       cout << endl <<"PID : "<< wait[i].first << "  " <<" Waiting Time : "<< wait[i].second - idQ.top().arrivalTIme<<" Turnaround TIme : "<<wait[i].second - idQ.top().arrivalTIme+Q.top().brustTime;
       idQ.pop();
   }
    cout<<endl;
    cout<<"Average Waiting Time:"<<avgWaitTime/x<<endl;
    cout<<"Average Turnaround Time:"<<avgTurnAroundTime/x<<endl;
    return 0;
}