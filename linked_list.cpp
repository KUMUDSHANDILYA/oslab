#include<bits/stdc++.h>

#include<limits>

#include<time.h>

using namespace std;

typedef struct node

{

int data;

int next;

node()

{

data=next=0;

}

}node;

class file

{

public:

string file_name;

int start;

int end;

int length;

file()

{

cout<<"enter the file name: ";

cin>>file_name;

cout<<"enter the starting of the file: ";

cin>>start;

cout<<"enter the ending of the file: ";

cin>>end;

cout<<"enter the length of the file: ";

cin>>length;

}

void display()

{

cout<<file_name<<"\t"<<start<<"\t"<<end<<endl;

}

};

void showmemory(node memory[],int n,vector<file> files)

{

if(files.size()!=0)

cout<<"file name \t start \t end\n";

for(int i=0;i<files.size();i++)

{

file f=files.at(i);

f.display();

}

for(int i=0;i<n;i++)

{

if(i%20==0 && i!=0)

cout<<endl;

cout<<memory[i].data<<" ";

}

cout<<endl;

}

void linkedlist(node memory[],int n,vector<file> &files)

{

file fi;

int count;

for(int i=fi.start;i<fi.end;i++)

{

if(memory[i].data==0)

count++;

}

if(count>=fi.length)

{

count=0;

int old=fi.start;

while(count<fi.length)

{

int random=fi.start+(rand()%(fi.end-fi.start+1));

if(count==0)

{

memory[fi.start].data=1;

memory[fi.start].next=random;

}

else if(count==fi.length-1)

{

memory[old].next=fi.end;

memory[fi.end].data=1;

}

else

{

if(memory[old].data==0 && old!=fi.end)

{

memory[old].data=1;

memory[old].next=random;

}

}

cout<<memory[old].next<<" ";

old=random;

count++;

}

cout<<"\nmemory has been successfully allocated to the file.\n";

files.push_back(fi);

}

else

{

cout<<"\n there was not enough space in the disk.\n";

}

cin.ignore(numeric_limits<streamsize>::max(),'\n');

char ans;

cout<<"do you want to store more files?\n";

cout<<"enter 'y' for yes and 'n' for no: ";

cin>>ans;

if(ans=='y')

linkedlist(memory,n,files);

}

int main()

{

//cout<<time(NULL)<<endl;

srand(time(NULL));

node memory[500];

int starting=(rand()%100)+(rand()%50)+1;

int ending=150+(rand()%50);

//allocating memory to os and user files/data

for(int i=starting;i<ending;i++)

memory[i].data=1;

vector<file> files;

cout<<"memory before storage allocation.\n";

showmemory(memory,500,files);

linkedlist(memory,500,files);

cout<<"memory after storage allocation.\n";

showmemory(memory,500,files);

return 0;

}
