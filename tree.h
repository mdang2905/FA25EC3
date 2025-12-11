//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.
   Students must manage storage, pointers, and dynamic allocation.

   Requirements:
   1. Templated Tree class.
   2. Nodes stored dynamically.
   3. Each node has:
      - id
      - data
      - vector of children pointers
   4. Students must prevent memory leaks.
   5. Students must create createRoot, addNode, findNode, print functions, etc.

   DO NOT IMPLEMENT ANYTHING HERE.
   Only placeholders and TODO comments.
*/


template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // TODO: Write constructor
    Node(const string &nodeID, const U &value) {
        id = nodeID;
        data = value;

    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;

public:
    Tree()
    // TODO: Initialize root pointer to nullptr
    {
        root = NULL;
    }


    void createRoot(const string &id, const T &value)
    // TODO: Allocate memory, assign id, assign data, set as root
    {
        root = new Node<T>(id, value);
    }


    void addNode(const string &parentID, const string &childID, const T &value)
    // TODO: Find parent, create child, link parent to child
    // TODO: Support repeated children under multiple parents
    {
        // first check if the new node exists already to avoid creating duplicates
        Node<T>* newNode = findNode(parentID);
        // if node has already been made but has no value, add value
        if (newNode->data == "") {
            newNode->data = value;
        }
        // if newNode does not exist, yes, create it
        if (newNode == nullptr) {
            newNode = new Node<T>(parentID, value);
        }

        // check to see if ID is valid
        if (childID != "") {
            Node<T>* child = findNode(childID);
            // look to see if child already exists
            if (child == nullptr) {
            child = new Node<T>(childID, "");
        }
        newNode->children.push_back(child);
        }



    }

    Node<T>* findNode(const string &id)
    // TODO: Use DFS or BFS to search tree
    // Using Depth First Search
    {
        if (root == nullptr) {
            return nullptr;
        }

        // stack for dfs
        std::stack<Node<T>*> s;
        s.push(root);

        Node<T>* node;
        while (!s.empty()) {
            node = s.top();
            s.pop();

            if (node->id == id) {
                return node;
            }

            if (node->children.size() > 0) {
                for (Node<T>* child : node->children) {
                    s.push(child);
                }
            }
        }

        return nullptr;

    }

    void printAll()
    // TODO: Print entire structure in readable form
    {
        if (root != nullptr) {
            std::queue<Node<T>*> q;
            q.push(root);
            while (!q.empty()) {
                Node<T>* node = q.front();
                q.pop();
                cout << node->id << endl;
                for (Node<T>* child : node->children) {
                    q.push(child);
                }
            }
        }
    }

    // 1. Start at the root node.
    // 2. Display the current node's text.
    // 3. Display numbered options for each child.
    // 4. Ask the user which path to take.
    // 5. Move to the selected child and continue until a node has no children.
    // 6. Print an ending message.
    void playGame() {
        Node<T>* node = root;
        while (node != nullptr) {
            cout << node->data <<  endl;
            if (node->children.empty()) {
                break;
            }
            cout << "Choose your next action:" << endl;
            Node<T>* child;
            for (int i = 0; i < node->children.size(); i++) {
                child = node->children[i];
                cout << child->id  << ". " << child->data << endl;
            }

            string inputID;
            cin >> inputID;
            node = findNode(inputID);
        }
        cout << "There are no further paths. \n"
                << "Your journey ends here. \n"
                << "===== Adventure Complete ====="
        << endl;
    }

    ~Tree()
    // TODO: Free all allocated memory
    {
        if (root != nullptr) {
            std::stack<Node<T>*> s;
            s.push(root);
            while (!s.empty()) {
                Node<T>* node = s.top();
                s.pop();
                cout << node->id << endl;
                if (node->children.size() > 0) {
                    for (Node<T>* child : node->children) {
                        s.push(child);
                    }
                }
                delete node;
            }
            root = nullptr;
        }
    }
};

#endif //FA25EC3_TREE_H
