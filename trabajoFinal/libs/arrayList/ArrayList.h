#pragma once

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
    void printList();
    int size();
    void remove(T value);
    void reverse();
    Node<T>* nextNode(Node<T>* current);
    Node<T>* previousNode(Node<T>* current);
    Node<T>* getNodeAtPosition(int position);

    ArrayList<T> findPositions(T value);
};

