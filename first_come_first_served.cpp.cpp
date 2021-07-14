#include<bits/stdc++.h>
using namespace std;

struct process{
    int id;
    int AT;
    int CT;
    int WT;
    int BT;
    int RT;
};


void arrange_according_to_AT(process arr[],int n){
    int l=0;
    for(int i=0;i<n-1;i++){
            l=i;
        for(int j=i+1;j<n;j++){
            if(arr[j].AT < arr[l].AT){
                l=j;
            }
        }
        swap(arr[i],arr[l]);
    }

}

void calculate_WT_RT_CT(process arr[],int n){
    arr[0].WT=0;
    arr[0].RT=0;
    int totime=arr[0].AT;
    arr[0].CT=arr[0].AT + arr[0].BT;
    for(int i=1;i<n;i++){
        totime+= arr[i-1].BT;
        if(arr[i].AT > totime){
            arr[i].WT=0;
            arr[i].RT=0;
            totime= arr[i].AT;
        }
        else{
            arr[i].WT = totime-arr[i].AT;
            arr[i].RT =  arr[i].WT;
        }
        arr[i].CT= totime+ arr[i].BT;
    }
}
void show_ordered_processes(process arr[],int n){
    cout<<"pid\tarrival time     burst time     Waiting time     Completion time\n";
    for(int i=0;i<n;i++){
        cout<<arr[i].id<<"\t"<<arr[i].AT<<"\t\t"<<arr[i].BT<<"\t\t"<<arr[i].WT<<"\t\t"<<arr[i].CT<<endl;
    }
}
int main(){
    int n;
    srand(time(0));
    n = rand()%10 +10;
    process p[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        p[i].AT = rand()%10 +1;
        p[i].BT = rand()%10 +1;
    }
    cout<<"Processes :\n";
    arrange_according_to_AT(p,n);
    calculate_WT_RT_CT(p,n);
    cout<<"Ordered as FCFS: \n";
    show_ordered_processes(p,n);
    int sum=0,sumr=0,sumt=0;
    for(int i=0;i<n;i++){
        sum+=p[i].WT;
        sumr+=p[i].RT;
        sumt+= p[i].CT - p[i].AT;
    }
    float ART,AWT,ATAT;
    ART=(sumr*1.0)/n;
    AWT=(sum*1.0)/n;
    ATAT=(sumt*1.0)/n;
    cout<<endl<<"AWT :"<<AWT<<endl<<endl<<"ART : "<<ART<<endl<<endl<<"ATAT : "<<ATAT<<endl;
    cout<<endl<<"GANTT CHART :\n";
    cout<<" AT:"<<p[0].AT<<" | P_ID:"<<p[0].id<<" | CT:"<<p[0].CT<<"|  ";
    for(int i=1;i<n;i++){
        cout<<" | P_ID:"<<p[i].id<<" | CT:"<<p[i].CT<<"|   ";
    }
    cout<<endl<<endl;
    return 0;
}

