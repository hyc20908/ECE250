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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
        bool noChildAlive() const;                                      //create a new function check if there is only one child
		bool erase( std::string const &, int, Trie_node *& );           //in the children array
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
    
    char letter = str[depth];
    letter = tolower(letter);
    int index = letter - 97;                                           //take the letter one by one and convert to lower case
                                                                       //initialize an index minus 97 to get the offset with a
    if(depth == str.size()){
        if(is_terminal == true){
            return true;                                                //when reach the end of the tree and it is a terminal then
        }                                                               //the input is in the tree
        else{
            return false;
        }
    }
    
    if(children == nullptr){
        return false;                                                   //if array point to null then it is not a member
    }
    
    if(children[index] == nullptr){
        return false;                                                   //if the index of the array is point to null then it is
    }                                                                   //not a member
    return children[index]->member(str, depth + 1);                     //recursively call the member function
}

bool Trie_node::insert( std::string const &str, int depth ) {
    
    char letter = str[depth];
    letter = tolower(letter);
    int index = letter - 97;
    
    if(depth == str.size()){
        is_terminal = true;                                             //set the terminal to true if the insert is over
        return true;
    }
    if(children == nullptr){
        children = new Trie_node*[26];                                  //create a new pointer array and set all the index to null
        for(int i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
    if(children[index] == nullptr){
        children[index] = new Trie_node();                              //create a new node if the index is null
    }
    children[index]->insert(str, depth + 1);                            //recursively call the function
	return true;
}

bool Trie_node::noChildAlive() const{
    
    if (children == nullptr){
        return 0;
    }
    int count = 0;
    for (int i = 0; i < 26; i++){
        if (children[i] != nullptr){
            count++;
        }
    }
    if(count < 1){
        return true;
    }
    return false;
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
    
    char letter = str[depth];
    letter = tolower(letter);
    int index = letter - 97;
    
    if(depth == str.length()){
        is_terminal = false;
        return true;
    }
    else{
        children[index]->erase(str, depth + 1, children[index]);        //need recursive back so put the instruction under the
    }                                                                   //recursive function
    
    if(children[index]->children == nullptr){
        if(children[index]->is_terminal == false){                      //when recursive back if the node is not a terminal and
            delete children[index];                                     //the children is point to null then we delete this index
            children[index] = nullptr;
        
            if(ptr_to_this->noChildAlive() == true){                    //check if the index is the only child in the array
                delete[] children;                                      //if it is then delete the entire array
                children = nullptr;
            }
            return true;
        }
    }
    return true;
}

void Trie_node::clear() {
    if(children != nullptr){                                            //if the array is not empty loop through the array
        for(int i = 0; i < 26; i++){                                    //and delete whatever it is not null and recursively call
            if (children[i] != nullptr){                                //the clear method
                children[i]->clear();
                delete children[i];
                children[i] = nullptr;
            }
        }
    }
    delete[] children;                                                  //at the end delete the entire array
    children = nullptr;
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
