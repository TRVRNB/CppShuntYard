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
  // need to keep track of these separately, since it's theoretically much faster this way
  string version = "1.0";
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
  headptr = nextptr;
  return;
}

Node* pop(){
  // remove and return last
  if (startptr == nullptr){
    return nullptr;
}
int main(){
  return 0;
}
