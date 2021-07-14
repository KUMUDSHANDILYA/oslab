#include<bits/stdc++.h>

#include<time.h>

#include<limits.h>

using namespace std;

class file

{

public:

string file_name;

int length;

int index;

file()

{

cout<<"enter the file name: ";

cin>>file_name;

cout<<"enter the length of the file: ";

cin>>length;

cout<<"enter the index of the file: ";

cin>>index;

}

void display()

{

cout<<file_name<<"\t\t\t"<<index<<"\t\t"<<length<<endl;

}

};

void show_memory(vector<int> memory[],int n,vector<file> &files)

{

if(files.size()!=0)

{

cout<<"file name\tindex\tlength\n";

for(int i=0;i<files.size();i++)

{

file fi=files.at(i);

fi.display();

}

}

for(int i=0;i<n;i++)

{

if(i%20==0)

cout<<endl;

cout<<memory[i].at(0)<<" ";

}

cout<<endl;

}

void indexed_file(vector<int> memory[],int n,vector<file> &files)

{

file fi;

memory[fi.index].at(0)=1;

int count=0;

while(count<fi.length)

{

int random=250+rand()%100;

if(memory[random].size()==1 && random!=fi.index)

{

memory[random].at(0)=1;

memory[fi.index].push_back(random);

count++;

}

}

if(count==fi.length)

cout<<"\nthe file allocation was successful\n";

cin.ignore(numeric_limits<streamsize>::max(),'\n');

char ans;

cout<<"Do you want to enter more files?\n";

cout<<"enter 'Y' for yes and 'N' for no: ";

cin>>ans;

if(ans=='Y' || ans=='y')

indexed_file(memory,n,files);

else

return;

}

int main()

{

srand(time(NULL));

vector<file> files;

vector<int> memory[500];

for(int i=0;i<500;i++)

memory[i].push_back(0);

int start=(rand()%100)+(rand()%50)+1;

int end=150+(rand()%50);

for(int i=start;i<end;i++)

{

memory[i].at(0)=1;

}

cout<<"memory before storage allocation.";

show_memory(memory,500,files);

indexed_file(memory,500,files);

cout<<"\nmemory after the storage allocation.";

show_memory(memory,500,files);

return 0;

}
