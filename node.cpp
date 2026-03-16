#include <iostream>
#include <string>
#include "node.h"
using namespace std;

Node::Node(string n_data){
  // constructor, mainly for setting private data
  data = n_data;
}

Node::~Node(){
  // main question i usually have to ask here: what data is it allowed to access?
  // i think the node owns its child data, but not next
  // CHANGE THIS LATER IF THE LINKED LIST NEEDS RECURSIVE DELETION
  // OR THE BINARY TREE NEEDS IT REMOVED
  delete children[1];
  delete children[2];
}

void Node::set_child(int child, Node* new_node){
  children[child] = new_node;
}

Node* Node::get_child(int child){
  return children[child];
}


