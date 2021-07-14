#include<bits/stdc++.h>
using namespace std;

typedef struct process{
    int id,At,Ct,Wt,Bt,Rt,q,remaining_time;
    bool flag=false;
}process;
void arrange_as_MQS(process arr[],int n){
    int x=0,i,j;
    for(i=0;i<n-1;i++){
            x=i;
        for(j=i+1;j<n;j++){
            if(arr[j].At < arr[x].At)
                x=j;
            else if(arr[j].At==arr[x].At){
                if(arr[j].q <arr[x].q)
                    x=j;
            }
        }
        swap(arr[i],arr[x]);
    }
}
void calculate_RT_WT_CT(process arr[],int n){
   int total_time=0,cprocess_count=0,current;
    while(cprocess_count<n){
        for(int i=0;i<n;i++){
            if( arr[i].remaining_time>0 ){
                current=i;
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(arr[i].At<=total_time && arr[i].remaining_time>0){
                if(arr[i].q<arr[current].q)
                    current=i;
            }
        }
        if( arr[current].At <= total_time){
            if( arr[current].flag == false){
                arr[current].Rt=total_time - arr[current].At;
                arr[current].flag=true;
            }
            arr[current].remaining_time--;
            if(arr[current].remaining_time ==0 ){
                cprocess_count++;
                arr[current].Ct=total_time+1;
                arr[current].Wt = arr[current].Ct - arr[current].At - arr[current].Bt;
            }
        }
        total_time++;
    }
}

void processes_after_MQS(process arr[],int n){

    cout<<"Pid\tArrival time\tBurst Time\tQueue\tWaiting Time\tResponse Time\tCompletion Time"<<endl;
    for(int i=0;i<n;i++)
        cout<<arr[i].id<<"\t"<<arr[i].At<<"\t\t"<<arr[i].Bt<<"\t\t"<<arr[i].q<<"\t\t"<<arr[i].Wt<<"\t\t"<<arr[i].Rt<<"\t\t"<<arr[i].Ct<<endl;

}
int main(){
    int n;
    float ART,AWT,ATAT;
    srand(time(NULL));
    n = rand()%10 +10;
    process arr[n];
    for(int i=0;i<n;i++){
        arr[i].id=i+1;
        arr[i].q = rand()%10 +1;
        arr[i].At = rand()%10 +1;
        arr[i].Bt = rand()%10 +1;
        arr[i].remaining_time=arr[i].Bt;
    }
    arrange_as_MQS(arr,n);
    calculate_RT_WT_CT(arr,n);
    cout<<"After Arranging and Evaluating: \n";
    processes_after_MQS(arr,n);
    int a=0,b=0,c=0;
    for(int i=0;i<n;i++){
        a+=arr[i].Wt;
        b+=arr[i].Rt;
        c+= arr[i].Ct - arr[i].At;
    }
    ART=(b*1.0)/n;
    AWT=(a*1.0)/n;
    ATAT=(c*1.0)/n;
    cout<<"\nAWT :"<<AWT<<endl<<"ART : "<<ART<<endl<<"ATAT : "<<ATAT<<endl<<endl;
    cout<<"GANTT CHART :\n";
    cout<<" AT:"<<arr[0].At<<" | P_ID:"<<arr[0].id<<" | CT:"<<arr[0].Ct<<"|  ";
    for(int i=1;i<n;i++){
        cout<<" | P_ID:"<<arr[i].id<<" | CT:"<<arr[i].Ct<<"|   ";
    }
    return 0;
}


