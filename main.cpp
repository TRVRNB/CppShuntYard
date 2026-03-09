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
  string mode = "postfix";
  string version = "1.2";
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

float operation(string s1, string s2, string operation){
  // take 2 numbers and an operator, perform the operation, automatically casts
  // ORDER MATTERS!
  // also, these are OPERATIONS, not FUNCTIONS, so they need 2 constants instead of 1
  float f1 = stof(s1); // input is integer numbers, but i think computations can be floats
  float f2 = stof(s2);
  if (operation == "+"){ // ADD
    return f1 + f2;
  } else if (operation == "-"){ // SUBTRACT
    return f1 - f2;
  } else if (operation == "*"){ // MULTIPLY
    return f1 * f2;
  } else if (operation == "/"){ // DIVIDE
    return f1 / f2;
  } else if (operation == "^"){ // POWER
    return pow(f1, f2);
  }
  cout << "operation " << operation << " not found" << endl;
  return 0.0;
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
  cout << "Shunting Yard Calculator - Version " << version << endl;
  cout << "Type 'HELP' for a list of commands." << endl;
  string input = "";
  while (input != "QUIT"){
    input = "";
    cout << "$ " << flush;
    cin >> input;
    if (input == "HELP"){
      cout << "HELP: return a list of commands (obviously!)\n";
      cout << "QUIT: end the program\n";
      cout << "INFIX: switch to infix mode (a / b)\n";
      cout << "PREFIX: switch to prefix mode (/ a b)\n";
      cout << "POSTFIX: switch to postfix mode (b a /)\n";
      cout << flush;
    } else if (input == "INFIX"){
      mode = "infix";
      cout << "switched to INFIX mode.";
    } else if (input == "PREFIX"){
      mode = "prefix";
      cout << "switched to PREFIX mode.";
    } else if (input == "POSTFIX"){
      mode = "postfix";
      cout << "switched to POSTFIX mode.";
    }

  }


  
  cout << "Goodbye!" << endl;
  return 0;
}
