#include <iostream>
#include <cmath>
#include <string>
#include "node.h"
using namespace std;
// shunting-yard algorithm to perform calculations based on user input
// started 3/03/26
// github.com/TRVRNB/CppShuntYard.git
namespace shunting_yard{
  // STACK VARIABLES
  Node* startptr = nullptr;; // bottom of the stack
  Node* headptr = nullptr; // end of the stack
  Node* prevptr = nullptr; // second to last, just saves some run time
  // need to keep track of these separately, since it's theoretically much faster this way
  // QUEUE VARIABLES
  Node* queue_back = nullptr;
  // OTHER VARIABLES
  string mode = "postfix";
  string version = "1.4"; 
}
using namespace shunting_yard;

namespace terminal_colors{
  // i made this, after wasting quite a bit of time looking into the documentation, but it is mine!
  // these MIGHT be system-dependent. it's just ASCII, but some terminals might have weird formats, i don't know very much about this
  // they also might have bad contrast with light mode terminals... but, like, come on
  const string red = "\033[1;31m";
  const string green = "\033[1;32m";
  const string yellow = "\033[1;33m";
  const string blue = "\033[1;34m";
  const string white = "\033[1;37m";
  const string resetl = "\033[0,37m";
  const string endl2 = "\033[0,37m\n";
}
using namespace terminal_colors;

// stack functions
// the stack is a linked list, but a very simple one, where the only efficient point to access is the very last node added
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
  // this references the idea i mentioned earlier, about whether or not a data structure 'owns' the objects it points to; i don't know the official terminology for this, but the stack needs to return data whenever popped, so it definitely doesn't own this data
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
  while (!prevptr->have_grandkids()){ // look for second to last
    prevptr = prevptr->get_child(0); // get next
    // get_child runs 3 times per loop here, but it shouldn't be a big hit
  }
  return headptr;
}

// queue functions
// the queue is almost the opposite, where the front and back are saved, and it has FI/FO
// my implementation is very simple, has the same optimization problems (time < memory) as the stack
void enqueue(Node* to_queue){
  // add to the back of the queue
  if (queue_back == nullptr){ // first, check if the queue even has anything yet
    queue_back = to_queue;
    return;
  }
  to_queue->set_child(0, queue_back); // set next to back of the queue
  queue_back = to_queue;
  return;
}

Node* dequeue(){
  // remove and return the front of the queue
  Node* to_return;
  Node* current_ptr = queue_back;
  if (current_ptr == nullptr){ // check for empty queue
    return nullptr;
  } else if (current_ptr->get_child(0) == nullptr){ // check for only 1
    to_return = current_ptr->get_child(0);
    current_ptr->set_child(0, nullptr);
    return to_return;
  }
  while (!current_ptr->have_grandkids()){
    // go until you find one with only next (no next->next, if that makes sense) 
    current_ptr = current_ptr->get_child(0);
  }
  to_return = current_ptr->get_child(0);
  current_ptr->set_child(0, nullptr);
  return to_return;
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
  
int main(){
  cout << red << "TRVRNB's Shunting Yard Calculator - Version " << version << endl2;
  cout << yellow << "Type 'HELP' for a list of commands." << endl2;
  string input = "";
  while (input != "QUIT"){ // QUIT
    input = "";
    cout << green << "$ " << flush;
    cin >> input;
    if (input == "HELP"){ // HELP
      cout << white << "HELP: return a list of commands (obviously!)" << endl2;
      cout << "QUIT: end the program" << endl2;
      cout << "INFIX: switch to infix mode (a / b)" << endl2;
      cout << "PREFIX: switch to prefix mode (/ a b)" << endl2;
      cout << "POSTFIX: switch to postfix mode (b a /)" << endl2;
      cout << "RUN: input and calculate an expression" << endl2;
      cout << flush;
    } else if (input == "INFIX"){ // INFIX
      mode = "infix";
      cout << yellow << "Switched to INFIX mode." << endl2 << flush;
    } else if (input == "PREFIX"){ // PREFIX
      mode = "prefix";
      cout << yellow << "Switched to PREFIX mode." << endl2 << flush;
    } else if (input == "POSTFIX"){ // POSTFIX
      mode = "postfix";
      cout << yellow << "Switched to POSTFIX mode." << endl2 << flush;
    } else if (input == "RUN"){ // RUN
      string expression;
      cout << endl2;
      cout << yellow << "Enter an expression." << endl2; 
      cout << green << "\t$ " << flush;
      cin >> expression;
      if (expression == "eeeeeeeeeeeeeeeeeee"){
	cout << blue << "eeeeeeeeeeeeeeeeee" << endl2 << flush;
	return 0;
      }
    }

  }


  
  cout << "Goodbye!" << endl;
  return 0;
}
