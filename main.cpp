#include <iostream>
#include <cmath>
#include <string>
#include "node.h"
using namespace std;
// shunting-yard algorithm to perform calculations based on user input
// started 3/03/26
// github.com/TRVRNB/CppShuntYard.git
namespace shunting_yard{
  Node* startptr = nullptr;; // bottom of the stack
  Node* headptr = nullptr; // end of the stack
  Node* prevptr = nullptr; // second to last, just saves some run time
  // need to keep track of these separately, since it's theoretically much faster this way
  string version = "1.1";
}
using namespace shunting_yard;

// stack functions
void push(Node* nextptr){
  // push to top of stack
  if (startptr == nullptr){
    startptr = nextptr;
  } else {
    headptr->set_child(0, nextptr); // set next
  }
  prevptr = headptr;
  headptr = nextptr;
  return;
}

Node* pop(){
  // remove and return last
  // doesn't automatically free memory!
  Node* pop_node = headptr;
  if (startptr == nullptr){ // stack is empty!
    return nullptr;
  } else if (prevptr == nullptr){ // stack is size 1
    headptr = nullptr;
    startptr = nullptr;
    return pop_node;
  }
  prevptr->set_child(0, nullptr); // remove next
  // now, need to update prevptr again...
  // i could technically avoid this O(n) computation by storing the previous pointer in the Node class
  // but after a certain point, may as well bite the bullet and take a negligible hit to performance, it already has 3 pointers and a lot of functions
  // just know i would do this differently if i thought the stack would ever get to at least a few thousand elements
  prevptr = startptr;
  while (prevptr->get_child(0)->get_child(0) != nullptr){ // look for second to last
    prevptr = prevptr->get_child(0); // get next
    // get_child runs 3 times per loop here, but it shouldn't be a big hit
  }
  return headptr;
}
  
int main(){
  cout << "ok!" << endl;
  return 0;
}
