#ifndef SHUNT_NODE
#define SHUNT_NODE
#include <iostream>
#include <string>
using namespace std;

// node class, both linear and binary tree
class Node{
  // this node is (very slightly) wasteful, since it has a left child, right child, and next ptr
  // it will be used for either a linked list or binary tree
  // so the functions for the other class will be unused
  // why not make 2 classes then? it would hurt performance more than it would help memory
  // and it would be more inconvenient to make :)
 public:
  // constructor / destructor
  Node(string n_data);
  ~Node();
  // main functions!
  string data;
  void set_child(int child, Node* new_node);
  Node* get_child(int child);

 private:
  Node* children[3] = {nullptr}; // create 3 empty pointers to nodes (filled in later)
};


#endif
