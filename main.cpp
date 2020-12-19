/*
 * Joseph Kelley
 * 11/07/2020
 * main.cpp
 */
#include "sortFinal.h"



int main() {
    {
        cout << "Array before Sorting" << endl;
        display();
        cout << "-----------------------------------" << endl;
        quickSort(0,9);
        //heapSort();

        cout << "-----------------------------------" << endl;
        cout << "Array After Sorting" << endl;
        display();

        return 0;
    }
}