#include <iostream>
//#include <thread>
#include <pthread.h>
#include <stdio.h>
using namespace std;
#ifndef SORTINGARRAY
#define SORTINGARRAY
class sortingArray {       
        public:             
        int unsortedArray[10] = {4,2,5,1,0,7,9,2,1,8};
        int sortedArray[10];
        int arr1[5];
        int arr2[5];
        void sort1();
        void sort2();
        void merge();
        void start();
        sortingArray();

        static void* startSortOne(void* object){
            reinterpret_cast<sortingArray*>(object)->sort1();
            return 0;
        }
        static void* startSortTwo(void* object){
            reinterpret_cast<sortingArray*>(object)->sort2();
            return 0;
        }
        static void* startSortThree(void* object){
            reinterpret_cast<sortingArray*>(object)->merge();
            return 0;
        }
};

    sortingArray::sortingArray(){ //constructor to seperate arrays
        for (int i=0; i<5; i++){
            arr1[i] = unsortedArray[i];
            arr2[i] = unsortedArray[i+5];
        }
    }
    
    void sortingArray::sort1(){ //bubble sort
        int temp;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                if (arr1[j] > arr1[j + 1])
                {
                    temp = arr1[j];
                    arr1[j] = arr1[j + 1];
                    arr1[j + 1] = temp;
                }
            }
        }
    }
    void sortingArray::sort2(){ //bubble sort
        int temp;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                if (arr2[j] > arr2[j + 1])
                {
                    temp = arr2[j];
                    arr2[j] = arr2[j + 1];
                    arr2[j + 1] = temp;
                }
            }
        }
    }

    void sortingArray::merge(){
        int i = 0, j = 0, k = 0;
        while (i<5 && j <5){
        //check if arr1[i]<arr2[j] and if yes add it to the sorted array and increment
        //otherwise do the same to j
            if (arr1[i] < arr2[j]){
                sortedArray[k++] = arr1[i++];
            }
            else{
                sortedArray[k++] = arr2[j++];
            }
        }
 
        //store remaining elements
        while (i < 5){
            sortedArray[k++] = arr1[i++];
        }
   
        while (j < 5){
            sortedArray[k++] = arr2[j++];
        }
    }

    void sortingArray::start(){ //start threads
        pthread_t thread_id;
        pthread_t thread_id1;
        pthread_t thread_id2;
        pthread_create(&thread_id, NULL, &sortingArray::startSortOne, this);
        pthread_create(&thread_id1, NULL, &sortingArray::startSortTwo, this);
        pthread_join(thread_id, NULL);
        pthread_join(thread_id1, NULL);
        pthread_create(&thread_id2, NULL, &sortingArray::startSortThree, this);
        pthread_join(thread_id2, NULL);
        printf("sorted list: ");
        for(int i=0;i<10;i++){
            printf("%i",sortedArray[i]);
            printf(", ");
        }
        printf("\n");
    }



#endif



int main(){
    sortingArray sort;
    sort.start();
    return 0;
}