/**
 * @author Abner Arroyo
 * @date 8/28/2021
 * @brief program that sorts a large file with integers with just 6 pages of 1KB of memory each
 *
 */
#include <iostream>
#include <fstream>
using namespace std;

class PagedArray{
public:

    int size;
    int virtualArray[256][2];
    ifstream infile;
    ofstream outfile;

    PagedArray(string inputfilename, string outputfilename){
        infile.open(inputfilename);
        outfile.open(outputfilename);
        string line;
        this->size = 0;
        if(infile.is_open() && outfile.is_open()){
            while(!infile.eof()){
                getline(infile, line);
                outfile << line << "\n";
                this->size++;
            }
            cout <<"File has " << size << "entries" << endl;
            cout << "Data copied to new location..."<< endl;

        } else {
            printf("Cannot read file");
        }
        infile.close();

    }

private:
    int calculatefilesize(string filename){

    }
};


/**
 *
 * @param array
 * @param size
 * @return none
 * @brief it sorts a given array of integers using the insertion sort algorithm with pointers
 */

int sort(int array[], int size){
    int i, curr, j;
    for (i = 1; i<size; i++){
        curr = array[i];
        j = i - 1;

        while (j >=0 && array[j] > curr){
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = curr;
    }
}

int main() {

}
