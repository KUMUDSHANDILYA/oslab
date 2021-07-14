
//program for contiguous file allocation

#include<bits/stdc++.h>

#include<time.h>

#include<limits>

using namespace std;

//class file to store the name and other properties of file.

class file

{

public:

string file_name;

int start_block;

int length;

public:

file()

{

cout<<"enter the file name: ";

cin>>file_name;

cout<<"enter the starting block of the file: ";

cin>>start_block;

cout<<"enter the length of the file: ";

cin>>length;

}

void display()

{

cout<<file_name<<"\t\t"<<start_block<<"\t\t\t"<<length<<endl;

}

};

//function to display the disk memory.

void showmemory(int memory[],int n,vector<file> files)

{

if(files.size()!=0)

cout<<"file name \t starting block \t length\n";

for(int i=0;i<files.size();i++)

{

file f=files.at(i);

f.display();

}

for(int i=0;i<n;i++)

{

if(i%20==0 && i!=0)

cout<<endl;

cout<<memory[i]<<" ";

}

cout<<endl;

}

//function to store each file.

void contiguous(int memory[],int n,vector<file> &files)

{

int len=0;

file fi;

int end=fi.start_block+fi.length;

//to check that the memory has enough space or not.

for(int j=fi.start_block;j<end;j++)

if(memory[j]==0)

len++;

//if the disk memory has enough space.

if(len==fi.length)

{

int j=0;

for( j=fi.start_block;j<end;j++)//make that space filled in the disk.

{

if(memory[j]==0)

memory[j]=1;

}

if(j==end-1)

cout<<"space has been allocated to the memory successfully.\n";

files.push_back(fi);//to store the files.

}

else

{

cout<<"\nthere was not enough space in disk.\n";

}

cin.ignore(numeric_limits<streamsize>::max(),'\n');

char ans;

cout<<"do you want to enter more files?\n";

cout<<"enter 'y' for yes and 'n' for no.: ";

cin>>ans;

if(ans=='y')

contiguous(memory,n,files);

else

return;

}

int main()

{

srand(time(NULL));

int memory[500]={0};

int start=(rand()%100)+(rand()%50)+1;

int end=150+(rand()%50);

//allocating memory to os and user files/data

for(int i=start;i<end;i++)

memory[i]=1;

vector<file> files;

cout<<"memory before storage allocation.\n";

showmemory(memory,500,files);

contiguous(memory,500,files);

cout<<"memory after storage allocation.\n";

showmemory(memory,500,files);

return 0;

}
