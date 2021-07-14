#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class File {
public:
    string filename;
    size_t size;
    int partition;
};
class Block {
    bool occupied = false;
    File file;

public:
    void set_file(File file)
    {
        this->file = file;
        occupied = true;
    }
    string get_file_name()
    {
        return file.filename;
    }
    int get_file_partition_no()
    {
        return file.partition;
    }
    bool is_empty()
    {
        return !occupied;
    }
    void set_empty()
    {
        occupied = false;
    }
    void set_occupied()
    {
        occupied = true;
    }
};

void showmemory(vector<Block> memory,int Size)
{
	for(int i=0;i<Size;i++)
	{
		if(i%20==0 && i!=0)
			cout<<endl;
		cout<<!memory[i].is_empty()<<" ";
	}
	cout<<endl;
}

int get_empty_count(vector<Block> memory)
{
    int sum = 0;
    vector<Block>::iterator slot;
    for (slot = memory.begin();
         slot != memory.end(); slot++) {
        sum += (*slot).is_empty();
    }

    return sum;
}

bool file_exists(vector<Block> memory,
                 string name)
{
    vector<Block>::iterator slot;

    for (slot = memory.begin();
         slot != memory.end(); slot++) {
        if (!(*slot).is_empty()
            && (*slot).get_file_name() == name) {
            return true;
        }
    }
    return false;
}

void set_contiguous_memory(vector<Block>* memory,
                           vector<int>* index,
                           File file)
{
    bool avail = false;
    int i = 0, count = 0, main_index;
    vector<Block>::iterator slot;

    if (file_exists((*memory),
                    file.filename))
        cout << "File already exists"
             << endl;

    else {

        for (slot = (*memory).begin();
             slot != (*memory).end(); slot++) {
            if ((*slot).is_empty()) {
                count++;
                if (count == 1)
                    main_index = i;
                if (count == file.size) {
                    avail = true;
                    break;
                }
            }
            else {
                count = 0;
            }
            i++;
        }
        if (avail) {

            (*index).push_back(main_index);
            count = 0;
            for (int i = main_index;
                 i < main_index + file.size;
                 i++) {
                file.partition = count;
                (*memory).at(i).set_file(file);
                count++;
            }
            cout << "File " << file.filename
                 << " has been successfully"
                 << " allocated"
                 << endl;
        }
        else {
            cout << "The size of the file is"
                 << " greater than"
                 << endl;
            cout << "the greatest slot available"
                 << " in contiguous memory"
                 << endl;
            cout << "Hence, File "
                 << file.filename
                 << " cannot be allocated"
                 << endl;
        }
    }
}

void delete_contiguous_mem(vector<Block>* memory,
                           vector<int>* index_page,
                           string file)
{
    vector<int>::iterator slot;
    int index, i = 0, main_index;
    if (!file_exists((*memory), file))
        cout << "File does not exist" << endl;
    else {
        for (slot = (*index_page).begin();
             slot != (*index_page).end(); slot++) {
            if ((*memory).at(*slot).get_file_name()
                == file) {
                index = i;
                main_index = (*slot);
                break;
            }
            i++;
        }
        i = main_index;

        while (i < (*memory).size()
               && (*memory).at(i).get_file_name()
                      == file
               && !(*memory).at(i).is_empty()) {
            (*memory).at(i).set_empty();
            i++;
        }

        (*index_page).erase((*index_page).begin() + index);
        cout << "File " << file
             << " has been successfully deleted"
             << endl;
    }
}

void show_contiguous_index(vector<Block> memory,vector<int> index_page)
{
    int max = 9, i, j;
    vector<Block>::iterator slot;
    string fname;

    for (i = 0; i < index_page.size();i++) {

        if (memory.at(index_page.at(i)).get_file_name().length()> max) {
            max = memory.at(index_page.at(i)).get_file_name().length();

            cout << "+" << string(max + 2, '-')
                 << "+---------------+----"
                 << "---------+-----------"
                 << "-------+\n|"
                 << string(max / 2+ max % 2 - 4,' ')
                 << "File Name"
                 << string(max / 2 - 3, ' ')
                 << "| Start Address | "
                 << " End Address | Size"
                 << " of the file |\n+"
                 << string(max + 2, '-')
                 << "+---------------+-------"
                 << "------+------------------+"
                 << endl;
        }
    }

    for (i = 0; i < index_page.size();i++) {
        cout << "|"
             << string(max / 2 + max % 2
                           - memory
                                     .at(index_page
                                             .at(i))
                                     .get_file_name()
                                     .length()
                                 / 2
                           - memory
                                     .at(index_page
                                             .at(i))
                                     .get_file_name()
                                     .length()
                                 % 2
                           + 1,
                       ' ')
             << memory.at(index_page.at(i))
                    .get_file_name()
             << string(max / 2
                           - memory
                                     .at(index_page
                                             .at(i))
                                     .get_file_name()
                                     .length()
                                 / 2
                           + 1,
                       ' ')
             << "|"
             << string(8
                           - to_string(index_page
                                           .at(i))
                                     .length()
                                 / 2
                           - to_string(index_page
                                           .at(i))
                                     .length()
                                 % 2,
                       ' ')
             << index_page.at(i)
             << string(7
                           - to_string(index_page
                                           .at(i))
                                     .length()
                                 / 2,
                       ' ')
             << "|";
        j = index_page
                .at(i);
        fname = memory
                    .at(j)
                    .get_file_name();
        while (j < memory.size()
               && !memory
                       .at(j)
                       .is_empty()
               && memory
                          .at(j)
                          .get_file_name()
                      == fname) {
            j++;
        }
        j -= 1;
        cout << string(7
                           - to_string(j)
                                     .length()
                                 / 2
                           - to_string(j)
                                     .length()
                                 % 2,
                       ' ')
             << j
             << string(6
                           - to_string(j)
                                     .length()
                                 / 2,
                       ' ')
             << "|"
             << string(9
                           - to_string(j
                                       - index_page
                                             .at(i)
                                       + 1)
                                     .length()
                                 / 2
                           - to_string(j
                                       - index_page
                                             .at(i)
                                       + 1)
                                     .length()
                                 % 2,
                       ' ')
             << j - index_page.at(i) + 1
             << string(9
                           - to_string(j
                                       - index_page
                                             .at(i)
                                       + 1)
                                     .length()
                                 / 2,
                       ' ')
             << "|"
             << endl;
    }
    cout << "+" << string(max + 2, '-')
         << "+---------------+------"
         << "-------+------------------+"
         << endl;
}


void show_contiguous_indexes(vector<Block> memory,
                             vector<int> index_page,
                             string filename)
{
    int index, i;

    vector<int>::iterator slot;

    if (file_exists(memory, filename)) {
        cout << "File Name = " << filename
             << "\n+------------------+----"
             << "--------------+";

        cout << "\n| Current Location |"
             << " Partition Number |";

        cout << "\n+------------------+-"
             << " -----------------+\n";

        for (slot = index_page.begin();
             slot != index_page.end(); slot++) {
            if (memory.at(*slot).get_file_name()
                == filename) {
                index = (*slot);
                break;
            }
        }

        while (index < memory.size()
               && memory
                          .at(index)
                          .get_file_name()
                      == filename
               && !memory
                       .at(index)
                       .is_empty()) {
            cout << "|"
                 << string(9
                               - to_string(index)
                                         .length()
                                     / 2
                               - to_string(index)
                                         .length()
                                     % 2,
                           ' ')
                 << index
                 << string(9
                               - to_string(index)
                                         .length()
                                     / 2,
                           ' ')
                 << "|"

                 << string(9- to_string(memory.at(index).get_file_partition_no())
                                         .length()
                                     / 2
                               - to_string(memory.at(index).get_file_partition_no())
                                         .length()
                                     % 2,
                           ' ')

                 << memory
                        .at(index)
                        .get_file_partition_no()

                 << string(9
                               - to_string(memory
                                               .at(index)
                                               .get_file_partition_no())
                                         .length()
                                     / 2,
                           ' ')
                 << "|"
                 << endl;
            index++;
        }
        cout << "+------------------+"
             << "------------------+"
             << endl;
    }
    else
        cout << "File does not exist "
             << "in given memory"
             << endl;
}


int main()
{
    cout<<"Enter the size of memory block: ";
    int Size;
    cin>>Size;
    vector<Block> memory(Size);
    srand(time(NULL));
    int a = (rand()%20)+1;
    int b = (rand()%100)+30;
    for(int i=a;i<=b;i++)
    {
        memory[i].set_occupied();
    }

    // Declare index page
    vector<int> index_page;
    File temp;

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    cout<<"Enter the number of files you want to allocate memory ";
    int N;
    cin>>N;
    File arr[N];
    for(int c=0;c<N;c++)
    {
        cout<<"Enter the name of file: ";
        char str[100001];
        cin>>str;
        temp.filename = str;
        cout<<"Enter the size of file: ";
        int s;
        cin>>s;
       /* while(s>get_empty_count(memory))
        {
            cout<<"Remaining memory is not enough"<<endl<<"Just "<<get_empty_count(memory)<<" memory is remaining"<<endl<<"Re enter the size"<<endl;
            cin>>s;
        }*/
        temp.size = s;
        arr[c] = temp;
        set_contiguous_memory(&memory,
                              &index_page,
                              temp);
        if(get_empty_count(memory)==0){
            cout<<"No memory left\n";
            break;
        }


    }
    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    // Function call to show all the
    // memory allocation
    show_contiguous_index(memory,
                          index_page);

    showmemory(memory, Size);

    cout << "Now we will check each partition of";
    cout << " files before"
         << endl;

    cout << "deleting them to see"
         << " which locations ";

    cout << "are going to be set free"
         << " as our slots"
         << endl;

    // Function call to show all the
    // memory allocation
    for(int c=0;c<N;c++)
    {
        show_contiguous_indexes(memory,
                            index_page,
                            arr[c].filename);
    }
    cout<<"Enter the indices of files you want to delete : "<<endl;
    cout<<"Enter -1 to stop: ";
    int index;
    cin>>index;
    while(index!=-1)
    {
        if(index<0 || index>=N){
            cout<<"Index invalid"<<endl;
        }
        else if(index>=0 && index<N){
            delete_contiguous_mem(&memory,
                          &index_page,
                          arr[index].filename);
        }
        cout<<"\nEnter index: ";
        cin>>index;
    }


    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;
    // Function call to show all the
    // memory allocation
    show_contiguous_index(memory,index_page);
    showmemory(memory, Size);
}
