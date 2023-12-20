#include <iostream>
#include "ArrayList.h"

// Definición de la estructura Node
template <typename T>
Node<T>::Node(T value) : data(value), next(nullptr) {}

// Implementación del constructor de la clase ArrayList
template <typename T>
ArrayList<T>::ArrayList() : head(nullptr) {}

// Método para agregar un elemento al final de la lista
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

// Método para agregar un elemento en una posición específica
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

// Método para imprimir la lista
/* template <typename T>
void ArrayList<T>::printList() {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
} */

// Método para obtener el tamaño de la lista
template <typename T>
int ArrayList<T>::size() {
    int count = 0;
    Node<T>* current = head;

    while (current != nullptr) {
        ++count;
        current = current->next;
    }

    return count;
}

// Método para eliminar un elemento de la lista
/* template <typename T>
void ArrayList<T>::remove_byValue(T value) {
    Node<T>* current = head;
    Node<T>* previous = nullptr;

    while (current != nullptr && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous != nullptr) {
            previous->next = current->next;
        } else {
            head = current->next;
        }
        delete current;
    }
}
 */

template <typename T>
void ArrayList<T>::remove_byIndex(int index) {
    if (index < 0 || head == nullptr) {
        return;
    }

    if (index == 0) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<T>* current = head;
    Node<T>* previous = nullptr;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) {
        previous = current;
        current = current->next;
        ++currentIndex;
    }

    if (current != nullptr) {
        previous->next = current->next;
        delete current;
    }
}


// Método para invertir la lista
template <typename T>
void ArrayList<T>::reverse() {
    Node<T>* current = head;
    Node<T>* previous = nullptr;
    Node<T>* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    head = previous;
}

// Método para obtener el siguiente nodo en la lista
template <typename T>
Node<T>* ArrayList<T>::nextNode(Node<T>* current) {
    if (current != nullptr) {
        return current->next;
    }
    return nullptr;
}

// Método para obtener el nodo anterior en la lista
template <typename T>
Node<T>* ArrayList<T>::previousNode(Node<T>* current) {
    if (current != nullptr) {
        Node<T>* temp = head;
        while (temp != nullptr && temp->next != current) {
            temp = temp->next;
        }
        return temp;
    }
    return nullptr;
}

// Método para obtener el nodo en una posición específica
template <typename T>
Node<T>* ArrayList<T>::get(int position) {
    if (position >= 0) {
        Node<T>* current = head;
        int index = 0;

        while (current != nullptr && index < position) {
            current = current->next;
            ++index;
        }

        return current;
    }

    return nullptr;
}

// Método para encontrar todas las posiciones de un valor en la lista
/* template <typename T>
ArrayList<T> ArrayList<T>::findPositions(T value) {
    ArrayList<T> positions;
    Node<T>* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->data == value) {
            positions.add(index);
        }
        current = current->next;
        ++index;
    }

    return positions;
} */

// Destructor de la clase ArrayList
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

// Es importante incluir la definición de las funciones de la plantilla en el archivo .cpp
// Esto garantiza que el compilador genere el código necesario para la plantilla con el tipo int
template class ArrayList<int>;  
template class ArrayList<float>;
template class ArrayList<unsigned int>;
