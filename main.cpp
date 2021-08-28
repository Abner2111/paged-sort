#include <bits/stdc++.h>

using namespace std;


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
