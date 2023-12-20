#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value);
};



template <typename T>
class ArrayList {
private:

    Node<T>* head;

public:
    ArrayList();
    ~ArrayList();

    void add(T value);
    void add(int position, T value);
    //void printList();
    int size();
    //void remove_byValue(T value);
    void remove_byIndex(int index);
    void reverse();
    Node<T>* nextNode(Node<T>* current);
    Node<T>* previousNode(Node<T>* current);
    Node<T>* get(int position);
    //ArrayList<T> findPositions(T value);
    
};

#endif