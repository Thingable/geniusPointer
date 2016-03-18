/**
 * @file GeniusPtrArray.h
 *
 * @author  Darrell Henderson
 * @date    3/16/16
 */

#ifndef GENIUSPTRARRAY_H
#define GENIUSPTRARRAY_H

#include <iostream>
    using std::cout;
    using std::endl;

class GeniusPtrArray{
    public:
        ~GeniusPtrArray();
        bool newPtr(int* const address);            // adds new pointer or increments pointers count
        bool deletePtr(int* const address);         // removes pointer or decrements pointers count
        int get_count(int* const address);          // returns number of shared pointers for an array
        int get_shared_count() const;                       // get size of array


    private:
        int** pointer_array = nullptr;      // pointer to the pointer indexes
        int* count_array = nullptr;         // pointer to count of shared
        int  size = 0;                      // internal size of items in the array
};

GeniusPtrArray::~GeniusPtrArray(){
    cout << "Deleting GeniusPtrArray..." << size << endl;
    delete [] pointer_array;
    delete [] count_array;
    pointer_array = nullptr;
    count_array = nullptr;
}

bool GeniusPtrArray::newPtr(int* const address){
    bool resizeFlag = 1;
    if(pointer_array){                                              // If previous shared pointers
        for(int i = 0; i < size; i++){                              // Loop through and check for address match
            if(pointer_array[i] == address){
                count_array[i] = count_array[i] + 1;
                resizeFlag = 0;
            }
        }
        if(resizeFlag){                                            // If no address match
            size++;
            int** temp_pointer_array = new int* [size];
            int* temp_count_array = new int [size];
            for(int i = 0; i < size - 1; i++){                      // Copy to temporary array
                temp_pointer_array[i] = pointer_array[i];
                temp_count_array[i] = count_array[i];
            }
            temp_pointer_array[size-1] = address;                // Add new count address
            temp_count_array[size-1] = 1;
            delete [] pointer_array;
            delete [] count_array;
            pointer_array = temp_pointer_array;
            count_array = temp_count_array;
            temp_pointer_array = nullptr;
            temp_count_array = nullptr;
        }
    }else{                                                          // If previous no shared pointers
        size++;
        pointer_array = new int* [size];
        count_array = new int [size];
        pointer_array[0] = address;
        count_array[0] = 1;
    }
    return resizeFlag;
}


bool GeniusPtrArray::deletePtr(int* const address){
    bool resizeFlag = 0;
    if(pointer_array){                                              // If previous shared pointers
        for(int i = 0; i < size; i++){
            if(pointer_array[i] == address){
                count_array[i] = count_array[i] - 1;
                if(count_array[i] == 0){                            // If shared count == 0
                    size--;
                    resizeFlag = 1;
                    if(size == 0){
                        delete [] pointer_array;
                        delete [] count_array;
                        pointer_array = nullptr;
                        count_array = nullptr; 
                    }else{
                        int** temp_pointer_array = new int* [size];
                        int* temp_count_array = new int [size];
                        for(int j = 0; j < size; j++){
                            bool skipFlag = 0;
                            if(i==j){
                                skipFlag = 1;
                            }
                            if(!skipFlag){
                                temp_pointer_array[j] = pointer_array[j];
                                temp_count_array[j] = count_array[j];
                            }else{
                                temp_pointer_array[j] = pointer_array[j];
                                temp_count_array[j] = count_array[j];
                            }
                        }
                        delete [] pointer_array;
                        delete [] count_array;
                        pointer_array = temp_pointer_array;
                        count_array = temp_count_array;
                        temp_pointer_array = nullptr;
                        temp_count_array = nullptr; 
                    }
                }
            }
        }
        
    }
    
    return resizeFlag;
}

int GeniusPtrArray::get_count(int* const address){
    int count = 0;
    for(int i = 0; i < size; i++){
        if(pointer_array[i] == address){
            count = count_array[i];
        }
    }
    return count;
}

int  GeniusPtrArray::get_shared_count() const{
    return size;
}


#endif
