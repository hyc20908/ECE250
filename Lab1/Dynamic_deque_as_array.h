#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"


class Dynamic_deque_as_array
{

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();


		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
    
    int* array;
    int arrayhead;
    int arraytail;
    int count;
    int arraysize;                                      //initialize each variable
    
};


Dynamic_deque_as_array::Dynamic_deque_as_array( int n) {
    if (n < 1){
        arraysize = 1;
    }
    else{
        arraysize = n;
    }                                                   //check the capacity and create a new array
    array = new int[arraysize];
    this->arrayhead = 0;
    this->arraytail = 0;                                //initialize the head and tail index
    count = 0;                                          //initialize the count

}




Dynamic_deque_as_array::~Dynamic_deque_as_array() {
    delete [] array;                                    //delete the memeory allocate for the array
}





int Dynamic_deque_as_array::size() const {
    return count;                                       //return the current size of the array
}


int Dynamic_deque_as_array::capacity() const {
    return arraysize;                                   //return the capacity of the array
}


bool Dynamic_deque_as_array::empty() const {
    bool flag = false;
        if(count == 0){
            flag = true;
        }
        else{
            flag = false;
        }
    return flag;                                        //check if the array is empty
}


int Dynamic_deque_as_array::head() const {
    if (!empty()){
        return array[arrayhead];                        //return the content at head index
    }
    else{
        throw underflow();                              //throw exception if array is empty
        }
}


int Dynamic_deque_as_array::tail() const {
    if (!empty()){
        return array[arraytail];                        //return the content at tail index
    }
    else{
        throw underflow();                              //throw exception if array is empty
    }
}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
    if (count != arraysize){                            //check if array is full
        if(!empty()){                                   //check if array is empty
            arrayhead = ((arrayhead - 1) + arraysize) % arraysize;//redirect the head index
        }
        else{                                           //set head and tail for the empty array
                arrayhead = 0;
                arraytail = 0;
        }
        array[arrayhead] = obj;                         //enqueue the value at head
        count++;
    }
    else{
        arraysize = arraysize * 2;
        int* newarray = new int[arraysize];             //creat a new array with size 2n if the old one is full
        if(arrayhead <= arraytail){
            for (int i = 0; i < arraysize/2; i++){
                newarray[i] = array[i];
            }
        }
        else{
            int tmp = 0;
            for(int i = arrayhead; i < arraysize/2; i++){
                newarray[tmp] = array[i];
                tmp++;
            }
            for(int j = 0; j <= arraytail; j++){
                newarray[tmp] = array[j];
                tmp++;                                  //copy all the elements from old array to new array at the
                                                        //begining of the new array
            }
        }
        arrayhead = 0;
        arraytail = count - 1;                          //move the head and tail index
        delete [] array;                                //clear the memory of the old array
        array = newarray;                               //reference the new array back to old array
        enqueue_head(obj);                              //call the enqueue_head function again to add an element at head
    }
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
    if (count != arraysize){                            //check if array is full
        if(!empty()){                                   //check if array is empty
            arraytail = ((arraytail + 1) + arraysize) % arraysize;//re-direct tail index
        }
        else{                                           //set head and tail for the empty array
            arrayhead = 0;
            arraytail = 0;
        }
        array[arraytail] = obj;                         //enqueue the value at tail
        count++;
    }
    else{
        arraysize = arraysize * 2;
        int* newarray = new int[arraysize];             //creat a new array with size 2n if the old one is full
        if(arrayhead <= arraytail){
            for (int i = 0; i < arraysize/2; i++){
                newarray[i] = array[i];
            }
        }
        else{
            int tmp = 0;
            for(int i = arrayhead; i < arraysize/2; i++){
                newarray[tmp] = array[i];
                tmp++;
            }
            for(int j = 0; j <= arraytail; j++){
                newarray[tmp] = array[j];
                tmp++;                                  //copy all the elements from old array to new array at the
                                                        //begining of the new array
            }
        }
        arrayhead = 0;
        arraytail = count - 1;                          //move the head and tail index
        delete [] array;                                //clear the memory of the old array
        array = newarray;                               //reference the new array back to old array
        enqueue_tail(obj);                              //call the enqueue_head function again to add an element at tail
    }

}


int Dynamic_deque_as_array::dequeue_head() {
    int oldhead = 0;
    if(!empty()){
        oldhead = array[arrayhead];                     //record the content
        array[arrayhead] = 0;                           //clear the content at the head index that need to be deleted
        arrayhead = ((arrayhead + 1) + arraysize) % arraysize;//re-direct the head index
        count--;
        
    }
    else{
        throw underflow();
    }
	return oldhead;                                     //return the content of the deleted index

}

int Dynamic_deque_as_array::dequeue_tail() {
    int oldtail = 0;
    if(!empty()){
        oldtail = array[arraytail];                     //record the content
        array[arraytail] = 0;                           //clear the content at the tail index the need to be deleted
        arraytail = ((arraytail - 1) + arraysize) % arraysize;//re-direct the tail index
        count--;
    }
    else{
        throw underflow();
    }
	return oldtail;                                     //return the content of the deleted index
}


void Dynamic_deque_as_array::clear() {
    count = 0;                                          //reset the size of the array
    arrayhead = 0;
    arraytail = 0;                                      //reset the head and the tail index
}

#endif
