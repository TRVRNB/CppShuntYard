#include <iostream>
#include <cmath>
#include <string>
#include <vector>
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
  Node* queue_front = nullptr;
  // OTHER VARIABLES
  string mode = "postfix";
  string version = "1.9";
}
using namespace shunting_yard;

namespace terminal_colors{
  // i made this, after wasting quite a bit of time looking into the documentation, but it is mine!
  // these MIGHT be system-dependent, but it's just ASCII color codes
  // they also might have bad contrast with light mode terminals... but, like, come on
  const string red = "\033[1;31m";
  const string green = "\033[1;32m";
  const string yellow = "\033[1;33m";
  const string blue = "\033[1;34m";
  const string white = "\033[1;37m";
  const string reset1  = "\033[0m";
  const string endl1  = "\033[0m\n";
}
using namespace terminal_colors;

// stack functions
// the stack is a linked list, but a very simple one, where the only efficient point to access is the very last node added
void push(Node* nextptr){
  nextptr->set_child(0, nullptr); // this should start without a next pointer
  // push to top of stack
  if (startptr == nullptr){
    startptr = nextptr;
    headptr = nextptr;
    prevptr = nullptr;
  } else {
    headptr->set_child(0, nextptr); // set next
    prevptr = headptr;
    headptr = nextptr;
  }
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
    prevptr = nullptr;
    pop_node->set_child(0, nullptr);
    return pop_node;
  }
  prevptr->set_child(0, nullptr); // remove next
  // now, need to update prevptr again...
  // i could technically avoid this O(n) computation by storing the previous pointer in the Node class
  // but after a certain point, may as well bite the bullet and take a negligible hit to performance, it already has 3 pointers and a lot of functions
  // just know i would do this differently if i thought the stack would ever get to at least a few thousand elements
  headptr = prevptr;
  Node* current_node = startptr;
  Node* lastprev = nullptr;
  while ((current_node != nullptr) && (current_node->get_child(0) != headptr)){
    lastprev = current_node;
    current_node = current_node->get_child(0); // get next
  }
  prevptr = lastprev;
  pop_node->set_child(0, nullptr);
  return pop_node;
}

// queue functions
// the queue is almost the opposite, where the front and back are saved, and it has FI/FO
// my implementation is very simple, has the same optimization problems (time < memory) as the stack
void enqueue(Node* to_queue){
  // add to the back of the queue
  to_queue->set_child(0, nullptr);
  if (queue_back == nullptr){
    queue_front = to_queue;
    queue_back = to_queue;
    return;
  }
  // assume the queue isn't empty now
  queue_back->set_child(0, to_queue);
  queue_back = to_queue;
}

Node* dequeue(){
  // remove and return the front of the queue
  if (queue_front == nullptr){ // empty queue
    return nullptr;
  }
  Node* pop_node = queue_front;
  queue_front = queue_front->get_child(0);
  if (queue_front == nullptr){
    queue_back = nullptr;
  }
  pop_node->set_child(0, nullptr);
  return pop_node;
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
  cout << yellow << "operation " << operation << " not found" << endl1 << flush;
  return 0.0;
}

bool is_operator(string term){
  // returns whether or not this term is an operator
  return ((term == "+") || (term == "-") || (term == "*") || (term == "/") || (term == "^"));
}
  
int o3(string term){
  // o3: order of operations, the name is confusing but less confusing than ooo()
  // basically just returns higher values for preferred operations
  if (term == "^"){
    return 3;
  } else if ((term == "/") || (term == "*")){
    return 2;
  } else {
    return 1;
  }
}

void print_tree(Node* current_node, unsigned short recursion = 0){
  // print the expression and its children
  // recursion determines tab length
  if (current_node == nullptr){
    return;
  }
  for (int i = 0; i < recursion; i++){
    cout << ' ';
  }
  cout << reset1 << current_node->data << endl;
  print_tree(current_node->get_child(1), recursion+1);
  print_tree(current_node->get_child(2), recursion+1);
  return;
}

int main(){
  cout << red << "TRVRNB's Shunting Yard Calculator - Version " << version << endl1;
  cout << yellow << "Type 'HELP' for a list of commands." << endl1;
  cout << yellow << "Current mode: " << mode << endl1;
  string input = "";
  while (input != "QUIT"){ // QUIT
    input = "";
    cout << green << "$ " << reset1 << flush;
    cin >> input;
    if (input == "HELP"){ // HELP
      cout << "HELP: return a list of commands (obviously!)" << endl1;
      cout << "QUIT: end the program" << endl1;
      cout << "INFIX: switch to infix mode (a / b)" << endl1;
      cout << "PREFIX: switch to prefix mode (/ a b)" << endl1;
      cout << "POSTFIX: switch to postfix mode (b a /)" << endl1;
      cout << white << "RUN: input and calculate an expression" << endl1;
      cout << flush;
    } else if (input == "INFIX"){ // INFIX
      mode = "infix";
      cout << yellow << "Switched to infix mode." << endl1 << flush;
    } else if (input == "PREFIX"){ // PREFIX
      mode = "prefix";
      cout << yellow << "Switched to prefix mode." << endl1 << flush;
    } else if (input == "POSTFIX"){ // POSTFIX
      mode = "postfix";
      cout << yellow << "Switched to postfix mode." << endl1 << flush;
    } else if (input == "RUN"){ // RUN
      char input1[201] = "";
      cout << endl1;
      cout << yellow << "Enter an expression. Add a space between terms, including parentheses." << endl1 << green << "\t$ " << reset1 << flush;
      cin.ignore();
      cin.getline(input1, 200, '\n');
      string expression(input1); // apparently i can iterate over this like a C-style string
      if (expression == "eeeeeeeeeeeeeeeeeee"){
	cout << blue << "eeeeeeeeeeeeeeeeeee" << endl1 << flush;
	return 0;
      }
      // now, parse the expression
      // (just test it for now)
      vector<string> terms; // this would honestly be better as a queue. but i can only make so many
      string current_term = "";
      for (char c : expression){ // look at every char
        if (c == ' '){ // reset this term
          if (current_term != ""){
            terms.push_back(current_term); // add to vector
          }
          current_term = "";
        } else {
          current_term += c;
        }
      }
      if (current_term != ""){
        terms.push_back(current_term); // need to push back the last one, too!
      }
      // build the expression tree now
      Node* root = nullptr; // root of expression tree, just declare it for now so it can be used in evaluating
      // infix will be infinitely more complicated; for prefix and postfix, the operations essentially become their own functions, so i don't need to keep order of operations or parentheses in mind
      // but for infix, it's awkward, since you have to make the program infer the order instead
      // i misunderstood earlier, the only input mode is actually infix, so i need to make order of operations
      // operator stack reset
      startptr = nullptr;
      headptr = nullptr;
      prevptr = nullptr;
      // output queue reset
      queue_back = nullptr;
      queue_front = nullptr;
      // this loop makes me regret barely using whitespace (for C++, if anything i overuse it in python), i'll make these giant functions more legible in the future
      // also, keep in mind that i roughly copied this from the shunting yard algorithm wikipedia page, which was in pseudocode, i only half understand this
      while (terms.size() > 0){ // while not empty
        string term = terms.front();
        terms.erase(terms.begin()); // pop front, this is basically a vector used as a queue
        if (!is_operator(term) && term != "(" && term != ")"){ // would be easier if there was an 'isNumber' functino
          Node* new_node = new Node(term);
          enqueue(new_node); // push this to output queue
        } else if (is_operator(term)){ // check for regular operator
          while (headptr != nullptr){ // stack isn't empty
            string top_term = headptr->data; // top of stack, must be an operator
            if (top_term == "("){ // this is a different... factor? i don't know what the part inside the parentheses is called in normal expressions honestly
              break; // i remember not being allowed to break, but that was sem. 1, and it looks like it's on the table now, like strings
            }
            if ((o3(term) < o3(top_term)) || ((o3(term) == o3(top_term)) && (term != "^"))){ // top of stack has right order of operations
              Node* top_node = pop(); // remove from stack
              enqueue(top_node); // but add to queue
              // the queue will be used to build the main expression tree anyway
              // the numbers go first because it's postfix
            } else {
              break; // some stacks aren't meant to be emptied
            }
          }
          Node* new_node = new Node(term);
          push(new_node);
        } else if (term == "("){ // opening parentheses, for now just do the same thing as numbers
          Node* new_node = new Node(term);
          push(new_node);
        } else if (term == ")"){ // right parentheses
          // look for matching parentheses OR empty stack
          while ((headptr != nullptr) && (headptr->data != "(")){ // apparently && will always not run the second check if the first one fails. so i can actually use this by checking for nullptr first, then doing the function second, the other order crashes
            Node* top_node = pop(); // remove this from stack
            enqueue(top_node); // and add to queue
          } // this should look for the left end
          if ((headptr != nullptr) && (headptr->data == "(")){ // left end was found
            Node* top_node = pop(); // this left parentheses is garbage data now
            delete top_node; // don't want to be wasteful here!
          }
        }
      }
      // now, add remaining terms to the queue
      while (headptr != nullptr){
        Node* top_node = pop();
        enqueue(top_node);
      }
      // print the postfix before building rtee
      Node* to_print = queue_front;
      cout << reset1 << "Postfix (before finishing tree):";
      while (to_print != nullptr){
        cout << ' ' << to_print->data;
        to_print = to_print->get_child(0);
      }
      cout << endl;
      // build the expression tree from the queue
      startptr = nullptr;
      headptr = nullptr;
      prevptr = nullptr;
      // the stack will now be used to organize these elements, but it should be empty by the end
      Node* current_node = dequeue();
      while (current_node != nullptr){ // while the queue has remaining terms
        if (is_operator(current_node->data)){ // if this is an operator
          Node* child1 = pop();
          Node* child2 = pop();
          if (child1 == nullptr || child2 == nullptr){
            cout << red << "Not enough operands for operator " << current_node->data << endl1 << flush;
            return 0;
          }
          current_node->set_child(1, child2);
          current_node->set_child(2, child1);
          push(current_node);
        } else { // number
          push(current_node);
        }
        current_node = dequeue(); // remove the first element from the queue
      }
      root = pop(); // final expression should be root one
      print_tree(root);
    }
  }
    cout << yellow << "Goodbye!" << endl1 << flush;
  return 0;
}
