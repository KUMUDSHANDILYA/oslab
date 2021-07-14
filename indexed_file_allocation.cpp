
// C++ implementation of the Indexed
// File Allocation Method
#include <iostream>
#include <vector>
using namespace std;

// File Class
class File {
public:
    // Name of File
    string filename;

    // Size of file
    size_t size;

    // Partition no. is which part of
    // file is present at a particular
    // block of memory
    int partition;
};

// Block class
class Block {
    // If Block is occupied
    // by a file or not
    bool occupied = false;

    // File of the block
    File file;

public:
    // This function will set file
    // into current block
    // and set occupied flag
    void set_file(File file)
    {
        this->file = file;
        occupied = true;
    }

    // This function will return
    // filename of given block
    string get_file_name()
    {
        return file.filename;
    }

    // This function will return
    // partition number of file
    int get_file_partition_no()
    {
        return file.partition;
    }

    // This function will return
    // if the block is empty or not
    bool is_empty()
    {
        return !occupied;
    }

    // This function will set the
    // occupied flag as false
    // meaning that it will free
    // the given block
    void set_empty()
    {
        occupied = false;
    }
};

// Function to return the number of
// empty Blocks from given memory
int get_empty_count(vector<Block> memory)
{
    int sum = 0;
    vector<Block>::iterator slot;

    // count no. of empty blocks in
    // given memory
    for (slot = memory.begin();
         slot != memory.end(); slot++)
        sum += (*slot).is_empty();
    return sum;
}

// This function will generate random indexes
// from empty memory slots to test indexing
int generate_index(vector<Block> memory)
{
    int index = -1;

    // Check if memory is full
    if (!get_empty_count(memory) == 0) {

        // Here it will generate index until
        // the memory block at generated
        // index is found to be empty
        do {
            index = rand() % memory.size();
            index = abs(index);

        } while (!memory.at(index).is_empty());
    }
    return index;
}

// This function will return if the file
// exists in a given memory
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

// This function will set file in
// memory and push index for each partition
// and then push the file index to main
// index vector
void set_indexed_memory(vector<Block>* memory,
                        vector<vector<int> >* index_page,
                        File file)
{
    int index;

    // Declaration newpage to set the
    // index page for given file
    vector<int> newpage;

    // Check if file exists
    if (file_exists((*memory), file.filename))
        cout << "File already exists" << endl;
    else {
        // Check if available memory is greater than
        // size of given file
        if (get_empty_count(*memory) >= file.size) {

            // Iterate till file size
            for (int i = 0; i < file.size; i++) {

                // Generate random empty index
                index = generate_index(*memory);

                // Set file partition
                file.partition = i;

                // Push the file to memory
                (*memory).at(index).set_file(file);

                // Push the index to newpage
                newpage.push_back(index);
            }

            // Push new index page into main
            // index page
            (*index_page).push_back(newpage);
            cout << "File " << file.filename
                 << " has been successfully allocated"
                 << endl;
        }
        else {
            cout << "Not enough available space"
                 << endl;
        }
    }
}

// Function to delete a file from given
// indexed memory
void delete_from_indexed_memory(vector<Block>* memory,
                                vector<vector<int> >* index_page,
                                string file)
{
    vector<int>::iterator slot;
    vector<vector<int> >::iterator it;
    int index, i = 0;

    // Check if file exists
    if (file_exists((*memory), file)) {
        // Iterate main index
        for (it = (*index_page).begin();
             it != (*index_page).end(); it++) {
            // Check for sub-index at
            // start location
            slot = (*it).begin();

            // Check if it equals filename
            if ((*memory)
                    .at(*slot)
                    .get_file_name()
                == file) {
                // Set for index and break
                index = i;
                break;
            }
            i++;
        }

        // Set the memory flag as empty
        for (slot = (*index_page).at(index).begin();
             slot != (*index_page).at(index).end();
             slot++)
            (*memory).at(*slot).set_empty();

        // Erase file index from main index page
        (*index_page)
            .erase((*index_page).begin() + index);
        cout << "File " << file
             << " has been successfully deleted"
             << endl;
    }
    else {
        cout << "File does not exist"
             << endl;
    }
}

// Function to display the main index
void show_indexed_index(vector<Block> memory,
                        vector<vector<int> > index_page)
{
    int max = 9;
    vector<Block>::iterator slot;
    vector<vector<int> >::iterator it;

    // Iterate over index pages
    for (it = index_page.begin();
         it != index_page.end(); it++) {
        if (memory
                .at((*it)
                        .at(0))
                .get_file_name()
                .length()
            > max) {
            max = memory
                      .at((*it)
                              .at(0))
                      .get_file_name()
                      .length();
            cout << "+" << string(max + 2, '-')
                 << "+---------------+----------"
                 << "---+------------------+\n|"
                 << string(max / 2 + max % 2 - 4, ' ')
                 << "File Name"
                 << string(max / 2 - 3, ' ')
                 << "| Start Address | End Address"
                 << " | Size of the file |\n+"
                 << string(max + 2, '-')
                 << "+---------------+------"
                 << "-------+------------------+"
                 << endl;
        }
    }

    // Iterate through all the index pages
    for (it = index_page.begin();
         it != index_page.end(); it++) {
        cout << "|"
             << string(max / 2
                           + max % 2
                           - memory
                                     .at((*it)
                                             .at(0))
                                     .get_file_name()
                                     .length()
                                 / 2
                           - memory
                                     .at((*it)
                                             .at(0))
                                     .get_file_name()
                                     .length()
                                 % 2
                           + 1,
                       ' ')
             << memory
                    .at((*it)
                            .at(0))
                    .get_file_name()
             << string(max / 2
                           - memory
                                     .at((*it)
                                             .at(0))
                                     .get_file_name()
                                     .length()
                                 / 2
                           + 1,
                       ' ')
             << "|"
             << string(8
                           - to_string((*it)
                                           .at(0))
                                     .length()
                                 / 2
                           - to_string((*it)
                                           .at(0))
                                     .length()
                                 % 2,
                       ' ')
             << ((*it).at(0))
             << string(7
                           - to_string((*it)
                                           .at(0))
                                     .length()
                                 / 2,
                       ' ')
             << "|"
             << string(7
                           - to_string((*it)
                                           .at((*it)
                                                   .size()
                                               - 1))
                                     .length()
                                 / 2
                           - to_string((*it)
                                           .at((*it)
                                                   .size()
                                               - 1))
                                     .length()
                                 % 2,
                       ' ')
             << (*it)
                    .at((*it).size() - 1)
             << string(6
                           - to_string((*it)
                                           .at((*it)
                                                   .size()
                                               - 1))
                                     .length()
                                 / 2,
                       ' ')
             << "|"
             << string(9
                           - to_string((*it)
                                           .size())
                                     .length()
                                 / 2
                           - to_string((*it)
                                           .size())
                                     .length()
                                 % 2,
                       ' ')
             << (*it).size()
             << string(9
                           - to_string((*it)
                                           .size())
                                     .length()
                                 / 2,
                       ' ')
             << "|" << endl;
        cout << "+" << string(max + 2, '-')
             << "+---------------+----------"
             << "---+------------------+"
             << endl;
    }
}

// Function to show each partition details
// w.r.t filename
void show_indexed_indexes(vector<Block> memory,
                          vector<vector<int> > index_page,
                          string filename)
{
    int index, i = 0, main_index;
    vector<vector<int> >::iterator slot;

    // Check if file exists
    if (file_exists(memory, filename)) {
        for (slot = index_page.begin();
             slot != index_page.end(); slot++) {
            if (memory.at((*slot).at(0)).get_file_name()
                == filename) {
                main_index = i;
                break;
            }
            i++;
        }

        // Display File Details
        cout << "File Name = " << filename << endl;
        cout << "File page index at main index :- "
             << main_index
             << "\n+------------------+------------------+\n";
        cout << "| Current Location | Partition Number |\n";
        cout << "+------------------+------------------+\n";
        for (i = 0;
             i < index_page.at(main_index).size();
             i++) {
            index = index_page
                        .at(main_index)
                        .at(i);
            cout << "|" << string(9
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
                 << "|" << string(9
                                      - to_string(memory
                                                      .at(index)
                                                      .get_file_partition_no())
                                                .length()
                                            / 2
                                      - to_string(memory
                                                      .at(index)
                                                      .get_file_partition_no())
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
                 << "|" << endl;
        }

        cout << "+------------------+----"
             << "--------------+" << endl;
    }
    else {
        cout << "File does not exist"
             << endl;
    }
}

// Driver Code
int main()
{
    // Declare memory of size 16 Blocks
    vector<Block> memory(16);

    // Declare index page
    vector<vector<int> > index_page;

    File temp;
    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    // Set the data
    temp.filename = "home.txt";
    temp.size = 5;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "Report.docx";
    temp.size = 6;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "new_img.png";
    temp.size = 3;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    temp.filename = "test.cpp";
    temp.size = 2;
    set_indexed_memory(&memory,
                       &index_page,
                       temp);

    // Print the Remaining memory
    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    // Print all the index memory
    show_indexed_index(memory, index_page);
    cout << "Now we will check each partition"
         << " for Report.docx and test.cpp"
         << " before deleting them" << endl;

    // Print all the index memory
    show_indexed_indexes(memory, index_page,
                         "Report.docx");

    // Print all the index memory
    show_indexed_indexes(memory, index_page,
                         "test.cpp");

    // Now delete Report.docx and test.cpp
    delete_from_indexed_memory(&memory,
                               &index_page,
                               "Report.docx");

    delete_from_indexed_memory(&memory,
                               &index_page,
                               "test.cpp");

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    // Print all the index memory
    show_indexed_index(memory, index_page);

    // Creating hello.jpeg file now
    // and setting it to memory
    temp.filename = "hello.jpeg";
    temp.size = 8;

    set_indexed_memory(&memory,
                       &index_page,
                       temp);
    cout << "Check index page :- "
         << endl;

    // Print all the index memory
    show_indexed_index(memory, index_page);

    // Now we will see index for each partition of
    // hello.jpeg
    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;
    cout << "We will check each partition"
         << " for hello.jpeg to see ";
    cout << "if the locations of deleted files"
         << " are utilized or not" << endl;

    // Print all the index memory
    show_indexed_indexes(memory, index_page,
                         "hello.jpeg");
    memory.clear();
    memory.shrink_to_fit();
    index_page.clear();
    index_page.shrink_to_fit();
    return 0;
}
