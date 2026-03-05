#include <iostream>
#include <string>
#include "node.h"
using namespace std;

Node::Node(Node* n_next, Node* n_child1, Node* n_child2, string n_meta, string n_data){
  // constructor, mainly for setting private data
  children[0] = n_next;
  children[1] = n_child1;
  children[2] = n_child2;
  meta = n_meta;
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

Node* Node::get_child(unsigned short child_index){
  // get the child requested in argument
  return children[child_index]; // 0 or 1 or 2
}

string Node::get_child_data(unsigned short child_index){
  // skip a step and go straight to this child's data!
  if (children[child_index] == nullptr){
    return "";
  }
  return children[child_index]->get_data();
}

bool Node::have_grandkids(){
  // whether or not any children have children
  for (Node* child : children){
    // look at all 3 children, check all 3 of their children
    // if they have any children at all, return true
    if (child != nullptr){
      for (int i = 0; i < 3; i++){
	if (child->get_child(i) != nullptr){
	  return true;
	}
      }
    }
  }
  return false;
}

void Node::set_child(unsigned short child_index, Node* n_child){
  // set this child based on arguments
  children[child_index] = n_child;
}

string Node::get_data(){
  // get data from this node
  return data;
}

void Node::set_data(string n_data){
  // set data based on arguments
  data = n_data;
}
