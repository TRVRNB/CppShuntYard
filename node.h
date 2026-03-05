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
  Node(Node* n_next, Node* n_child1, Node* n_child2, string n_meta, string n_data);
  ~Node();
  // main functions!
  // children[0] is next, children[0] and children[1] are left/right child
  Node* get_child(unsigned short child_index); // 1 = child1, 2 = child2, this way i can use variables
  string get_child_data(unsigned short child_index); // same as above; this might save some lines
  void set_child(unsigned short child_index, Node* n_child);
  string get_data();
  void set_data(string n_data);
  bool have_grandkids();
  string meta; // metadata, aka comments, for debugging purposes
 private:
  Node* children[2] = {nullptr}; // create 2 empty pointers to nodes (filled in later)
  string data;
};


#endif
