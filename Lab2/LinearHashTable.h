#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        int originalSize;                           //create a new variable to store the initial capacity
        int mod;
		T *array;
		state *occupied;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << m ){
    array = new T[array_size];
    occupied = new state[array_size];               //initialize two arrays
    count = 0;                                      //initialize count
    power = m;                                      //initialize power
    originalSize = pow(2,m);
    for(int i = 0; i < array_size; i++){            //initialize the occupied array and make all the incdex empty
        occupied[i] = EMPTY;
        array[i] = 0;
    }
}


template<typename T >
LinearHashTable<T >::~LinearHashTable() {
    delete[] array;
    delete[] occupied;                              //delete the memeory allocate for the arrays
}

template<typename T >
int LinearHashTable<T >::size() const {
	return count;                                   //return the current size of the hashtable
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;                              //return the capacity of the hashtable
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
    double alpha = (double)count/array_size;
    return alpha;                                   //calculate the load factor
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    if (count == 0){
        return true;
    }
    return false;                                   //determine if the hashtable is empty
}


template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
    for(int i = 0; i < array_size; i++){
        if (array[i] == obj && occupied[i] == OCCUPIED) {
            return true;
        }
    }
    return false;                                   //determine if the object is in the hashtable
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
    return array[n];                                //return the entry in index n
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
    if(load_factor() <= 0.75){
        int index;
        index = (int)obj % array_size;              //primary hash function
        while(occupied[index] == OCCUPIED){
            index = (index + 1) % array_size;       //if there exist collision, then using linear probing method
        }
        array[index] = obj;                         //store the obj in the hashtable
        occupied[index] = OCCUPIED;                 //change the state to occupied
        count++;                                    //increment the size of the hashtable
    }
    else{
        array_size = array_size * 2;
        T* oldarray = array;
        state* oldoccupied = occupied;
        array = new T[array_size];
        occupied = new state[array_size];           //create two new arrays with capacity multiply by 2
        power++;                                    //increment the power to increase the capacity
        count = 0;                                  //reset the count
        
        for(int i = 0; i < array_size; i++){
            occupied[i] = EMPTY;
            array[i] = 0;                           //make each entry empty
        }
        for(int i = 0; i < array_size / 2; i++){
            if(oldoccupied[i] == OCCUPIED){
                insert(oldarray[i]);                //rehash all the obj into the new arrays
            }
        }
        delete [] oldarray;
        delete [] oldoccupied;                      //delete the memory allocated in the old arrays
        insert(obj);                                //hash the new obj
        }
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
    if(member(obj)){                                //check if the obj is in the hashtable
        if(load_factor() > 0.25 || originalSize == capacity()){
            for(int i = 0; i < array_size; i++){
                if(array[i] == obj){
                    occupied[i] = DELETED;          //delete the obj in the hashtable
                    count--;                        //decrement the count
                    return true;
                }
            }
            return false;
        }
        else{
            array_size = array_size / 2;
            T* oldarray = array;
            state* oldoccupied = occupied;
            array = new T[array_size];
            occupied = new state[array_size];       //create two arrays with capacity divided by 2
            power--;                                //decrement the power to decrease the capacity
            count = 0;                              //reset the count
            
            for(int i = 0; i < array_size; i++){
                occupied[i] = EMPTY;                //make each entry empty
                array[i] = 0;
            }
            for(int i = 0; i < array_size * 2; i++){
                if(oldoccupied[i] == OCCUPIED){
                    insert(oldarray[i]);            //rehash all the obj into the new arrays
                }
            }
            delete [] oldarray;
            delete [] oldoccupied;                  //delet the memory allocated in the old arrays
            remove(obj);                            //remove the obj in the hashtable
            return true;
        }
    }
    return false;
}

template<typename T >
void LinearHashTable<T >::clear() {
    for(int i = 0; i < array_size; i++){
        array[i] = 0;
        occupied[i] = EMPTY;                        //clear all the entry
    }
    count = 0;                                      //reset the count
}

template<typename T >
void LinearHashTable<T >::print() const{
    for(int i = 0; i < array_size; i++)
    {
        std::cout << array[i] << "      " << occupied[i] << std::endl;
    }
    std::cout << array_size << std::endl;
    std::cout << load_factor() << std::endl;        //print out each entries of two arrays, the arraysize and the load factor
}

#endif
