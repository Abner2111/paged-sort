/**
 * @author Abner Arroyo
 * @date 8/28/2021
 * @brief program that sorts a large file with integers with just 6 pages of 1KB of memory each
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>
using namespace std;

class PagedArray{
public:
    int size;
    ifstream infile;
    ofstream outfile;
    string copyfilename;
    string outputfilename;

    PagedArray(string inputfilename, string outputfilename){
        this->outputfilename = outputfilename;
        this->outfile.open(outputfilename);
        this->infile.open(inputfilename);
        this->copyfilename = "newoutput.txt";
        string line;
        this->size = 0;
        if(this->infile.is_open() && this->outfile.is_open()){
            while(!this->infile.eof()){
                getline(this->infile, line);
                this->outfile << line << endl;
                this->size++;
            }
            cout << "Data copied to new location..."<< endl;
            cout << "The file has " << this->size << " entries" << endl;

        } else {
            printf("Cannot read file");
        }
        this->infile.close();
        this->outfile.close();


    }
    /***
     *
     * @param i
     * @return the value of the element in the requestedd index from the paged array
     * @brief it overloads the subscripting operator
     */
    int& operator[](int i){
        int pi = 0;
        for (pi;pi<this->size;pi++){
            if(this->virtualArray[pi][0]==i){
                return this->virtualArray[pi][1];
            } else {
                cout << "page fault" << endl;
                //pageFault
                return this->replace(i);
            }
        }
    }

private:
    int virtualArray[256*3][2];
    int nextflush = 0;

    /***
     *
     * @param i
     * @return the int& from the array, tranlated from the virtual memory after being inserted in it
     */
    int& replace(int i){
        int pos = 0;
        infile.open(this->outputfilename);
        outfile.open(copyfilename);
        string line;
        int curr;

        if(this->infile.is_open() && this->outfile.is_open()){
            while(!this->infile.eof()){
                getline(this->infile, line);
                if(pos == this->nextflush){
                    this->outfile << this->virtualArray[this->nextflush][1];
                    getline(this->infile, line);
                    pos++;
                } else if(pos==i){
                    this->virtualArray[this->nextflush][0]=i;
                    this->virtualArray[this->nextflush][1]=stoi(line);
                }
                this->outfile << line << "\n";
            }
            curr = this->nextflush;
            if (this->nextflush < this->size-1){
                this->nextflush++;
            } else {
                this->nextflush = 0;
            }
            remove(this->outputfilename.c_str());
            rename(this->copyfilename.c_str(), this->outputfilename.c_str());
            return (int &) virtualArray[curr][1];
        }
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
    PagedArray array("randomnumbers.txt", "newfile.txt");
    sort(&array[0], array.size);
}
