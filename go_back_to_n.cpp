//Go back to N
#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	vector<int> packets{1,2,3,4,5,6,7,8,9};
	int n=packets.size();			// number of packets to send
	int window_size=4,ack,temp,cnt=0;
	int left=0;				//position of the window
	cout<<"In progress...\n\n";
	while(cnt<n)
	{
		temp=0;
		for(int i=left;i<left+window_size&&i<n;i++)
			cout<<"Frame "<<i+1<<" sent\n";
		for(int i=left;i<left+window_size&&i<n;i++)
		{
			ack=rand()%2;
			if(ack==0)
			{
				cout<<"Acknowledgement not received for frame "<<i+1<<"\nRetransmitting window....\n\n";
				break;
			}
			else
			{
				cout<<"Acknowledgement received for frame "<<i+1<<" \n";
				temp++;
			}
		}
		left=left+temp;
		cnt=cnt+temp;
	}

	cout<<"\n\nSuccessful";
}

