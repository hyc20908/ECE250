/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y65han @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Spring) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
    clear();                                            //call clear function
}

int Trie::size() const {
	return trie_size;                                   //return the size of the trie tree
}

bool Trie::empty() const {
    if(trie_size == 0){
        return true;                                    //determine if there is word in the tree
    }
    return false;
}

Trie_node *Trie::root() const {
	return root_node;                                   //return the pointer to the root node
}

bool Trie::member( std::string const &str ) const {
    for(int i = 0; i < str.size(); i++){
        if(isalpha(str[i]) == false){
            throw illegal_argument();                   //check if input is alphabet
        }
    }
    
    if(root_node == nullptr){                           //return false if nothing is on root node
        return false;
    }
    
    return root_node->member(str, 0);                   //call the member function start from root node and return the results
}

bool Trie::insert( std::string const &str ) {
    for(int i = 0; i < str.size(); i++){
        if(isalpha(str[i]) == false){
            throw illegal_argument();                   //check if input is alphabet
        }
    }
    
    if (root_node == nullptr){
        root_node = new Trie_node();                    //if root node is empty create a new node
    }
    
    if(member(str) == true){
        return false;                                   //check if input is in the tree if it is then dont insert
    }
    root_node->insert(str, 0);                          //recursively call the insert function and size + 1
    trie_size++;
    return true;
    
}

bool Trie::erase( std::string const &str ) {
    for(int i = 0; i < str.size(); i++){
        if(isalpha(str[i]) == false){
            throw illegal_argument();                   //check if input is alphabet
        }
    }
    
    if(member(str) == false){
        return false;                                   //check if input is in the tree then erase if it is not then dont erase
    }
    
    if(empty() == false){
        root_node->erase(str, 0, root_node);
        trie_size--;                                    //if the tree isn't empty then call erase function
    }
    if(trie_size == 0){
        delete root_node;
        root_node = nullptr;
    }
    return true;
    
}

void Trie::clear() {
    if(!empty()){
        root_node->clear();                             //if the tree isn't empty then call the clear function
    }
    delete root_node;                                   //delete the root node
    root_node = nullptr;                                //set the pointer to null
    trie_size = 0;                                      //reset the size
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
