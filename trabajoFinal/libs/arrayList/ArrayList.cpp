#include "ArrayList.h"

template <typename T>
Node<T>::Node(T value) : data(value), next(nullptr) {}

template <typename T>
ArrayList<T>::ArrayList() : head(nullptr) {}

template <typename T>
void ArrayList<T>::add(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

template <typename T>
void ArrayList<T>::add(int position, T value) {
    Node<T>* newNode = new Node<T>(value);

    if (position < 0) {
        add(value);
        return;
    }

    if (position == 0) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node<T>* current = head;
    for (int i = 0; i < position - 1 && current != nullptr; ++i) {
        current = current->next;
    }

    if (current == nullptr) {
        add(value);
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

template <typename T>
void ArrayList<T>::printList() {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Resto del código...

template <typename T>
ArrayList<T>::~ArrayList() {
    Node<T>* current = head;
    Node<T>* nextNode;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
}
