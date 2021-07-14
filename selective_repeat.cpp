//selective repeat
#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	vector<int> packets{1,2,3,4,5,6,7,8,9};
	int n=packets.size();			// number of packets to send
	int buffer_size=4,ack,temp,cnt=0,strt=0,i;
	vector<int> resend;			//to keep track of the packets which need to be resend , originally they will be in the buffer
	temp=0;
	cout<<"In progress...\n\n";
	while(cnt<n)
	{
		for(i=0;i<resend.size();i++)
			cout<<"Frame "<<resend[i]+1<<" resent\n";
		for(i=strt;i<strt+buffer_size-resend.size()&&i<n;i++)
			cout<<"Frame "<<i+1<<" sent\n";
		temp=i;
		for(i=0;i<resend.size();i++)
		{
			ack=rand()%2;
			if(ack==0)
			{
				cout<<"Acknowledgement not received for frame "<<resend[i]+1<<"\n";
			}
			else
			{
				cout<<"Acknowledgement received for frame "<<resend[i]+1<<" \n";
				resend.erase(resend.begin()+i);
				i--;
				cnt++;
			}
		}
		for(i=strt;i<temp&&i<n;i++)
		{
			ack=rand()%2;
			if(ack==0)
			{
				cout<<"Acknowledgement not received for frame "<<i+1<<"\n";
				resend.push_back(i);
			}
			else
			{
				cout<<"Acknowledgement received for frame "<<i+1<<" \n";
				cnt++;
			}
		}
		strt=temp;
	}

	cout<<"\n\nSuccessful";
}

