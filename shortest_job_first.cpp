#include<bits/stdc++.h>
using namespace std;

struct process{
    int id;
    int At;
    int Ct;
    int Wt;
    int Bt;
    int Rt;
};


void arrange_as_SJF(process arr[],int n){
    int l=0;
    for(int i=0;i<n-1;i++){
            l=i;
        for(int j=i+1;j<n;j++){
            if(arr[j].At < arr[l].At){
                l=j;
            }
            else if(arr[j].At==arr[l].At){
                if(arr[j].Bt<arr[l].Bt){
                    l=j;
                }
            }
        }
        swap(arr[i],arr[l]);
    }

}

void calculate_CT_RT_WT(process arr[],int n){
    arr[0].Wt=0;
    arr[0].Rt=0;
    int curr;
    int totime=arr[0].At;
    arr[0].Ct=arr[0].At + arr[0].Bt;
    for(int i=1;i<n;i++){


        totime+= arr[i-1].Bt;

        curr=i;
        for(int j=i+1;j<n;j++){
            if(arr[j].At<=totime){
                if(arr[j].Bt<arr[curr].Bt){
                    curr=j;
                }
            }
        }
        swap(arr[curr],arr[i]);
        if(arr[i].At > totime){
            arr[i].Wt=0;
            arr[i].Rt=0;
            totime= arr[i].At;
        }
        else{
            arr[i].Wt = totime-arr[i].At;
            arr[i].Rt =  arr[i].Wt;
        }
        arr[i].Ct= totime+ arr[i].Bt;
    }
}

void processes_after_SJF(process arr[],int n){
    cout<<"pid\tarrival time     burst time     Waiting time     Completion time\n";
    for(int i=0;i<n;i++){
        cout<<arr[i].id<<"\t"<<arr[i].At<<"\t\t"<<arr[i].Bt<<"\t\t"<<arr[i].Wt<<"\t\t"<<arr[i].Ct<<endl;
    }
}
int main(){
    int n;
    srand(time(0));
    n = rand()%10 +10;
    process arr[n];
    for(int i=0;i<n;i++){
        arr[i].id=i+1;
        arr[i].At = rand()%10 +1;
        arr[i].Bt = rand()%10 +1;
    }
    arrange_as_SJF(arr,n);
    calculate_CT_RT_WT(arr,n);
    cout<<"After arrange_as_SJF and processing: \n";
    processes_after_SJF(arr,n);
    int sum=0,sumr=0,sumt=0;
    for(int i=0;i<n;i++){
        sum+=arr[i].Wt;
        sumr+=arr[i].Rt;
        sumt+= arr[i].Ct - arr[i].At;
    }
    float ART,AWT,ATAT;
    ART=(sumr*1.0)/n;
    AWT=(sum*1.0)/n;
    ATAT=(sumt*1.0)/n;
    cout<<endl<<"AWT :"<<AWT<<endl<<"ART : "<<ART<<endl<<"ATAT : "<<ATAT;
    cout<<endl<<"GANTT CHART :\n";
    cout<<" AT:"<<arr[0].At<<" | P_ID:"<<arr[0].id<<" | CT:"<<arr[0].Ct<<"|  ";
    for(int i=1;i<n;i++){
        cout<<" | P_ID:"<<arr[i].id<<" | CT:"<<arr[i].Ct<<"|   ";
    }
}

