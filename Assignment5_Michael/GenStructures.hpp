#ifndef _GEN_STRUCTURES_HPP
#define _GEN_STRUCTURES_HPP

#include <iostream>
using namespace std;
template <class T>
class ListNode {
    //exactly like the one went over in class and the one I used for assignment #4
    public:
        ListNode();
        ListNode(T value);
        ~ListNode();
        T data;
        ListNode *next;
        ListNode *prev;
};

template <class T>
ListNode<T>::ListNode() {
    data = NULL;
    next = nullptr;
    prev = nullptr;
}

template <class T>
ListNode<T>::ListNode(T value) {
    data = value;
    next = nullptr;
    prev = nullptr;
}

template <class T>
ListNode<T>::~ListNode() {
    delete next;
    delete prev;
}

template <class T>
class DoublyLinkList {
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        int size;

    public:
        DoublyLinkList();
        ~DoublyLinkList(); 
    bool isEmpty(); 
        int getSize(); 
        void printList();
        T removeFront(); 
        void insertBack(T data); 
        void insertFront(T data); 
        T getFront(); 
        T getPosition(int pos);

       
};     

template <class T>
DoublyLinkList<T>::DoublyLinkList() {
    size = 0;
    front = nullptr;
    back = nullptr;
}

template <class T>
DoublyLinkList<T>::~DoublyLinkList() {
    ListNode<T> *current = front;

    while (current != nullptr) {
        ListNode<T> *node = current;
        current = current -> next;
        current->prev = nullptr;
        delete node;
    }
    size = 0;
    current = NULL;
    delete front;
    delete back;
}

template <class T>
T DoublyLinkList<T>::removeFront() {
    ListNode<T> *node = front;
    T temp = node->data;

    if (size > 1){
        front = front->next;
        front->prev = nullptr;
    } else {
        front = nullptr;
    }
    node->prev = nullptr;       
    node->next = nullptr;
    delete node;
    size--;
    return temp;
}

template <class T>
void DoublyLinkList<T>::insertBack(T d) {
    ListNode<T> *node = new ListNode<T>(d);
    if(size == 0) {
        front = node;
    } else {
        node->prev = back;
        back->next = node;
    }
    back = node;
    ++size;
}

template <class T>
void DoublyLinkList<T>::insertFront(T d) {
    ListNode<T> *node = new ListNode<T>(d);


    if(size == 0) {
        back = node;
    } else {
        node->next = front;
        front->prev = node;
    }
    front = node;
    ++size;
}

template <class T>
T DoublyLinkList<T>::getFront() {
    return front->data;
}

template <class T>
bool DoublyLinkList<T>::isEmpty() {
    return size == 0;
}

template <class T>
int DoublyLinkList<T>::getSize() {
    return size;
}

template <class T>
T DoublyLinkList<T>::getPosition(int pos) {
    ListNode<T> *current = front;
    for (int j = 0; j < pos; ++j) {
        current = current->next;
    }
    return current->data;
}

template <class T>
void DoublyLinkList<T>::printList() {
    ListNode<T> *current = front;
    for (int j = 0; j < size; j++) {
        cout << j << ":" << current->data << endl;
        current = current->next;
    }
    cout << endl;
}

template <class T>
class GenQueue
{
    public:
        GenQueue();
        GenQueue(int size);
        ~GenQueue();

        void enqueue(T item);
        T dequeue();
        T peek();

        bool isEmpty();  
        int  getSize(); 
        void printQueue(); 

        int queueSize;
        DoublyLinkList<T> myQueue;
};
template <class T>
void GenQueue<T>::enqueue(T item) {
    myQueue.insertBack(item);
}

template <class T>
T GenQueue<T>::dequeue() {
    return myQueue.removeFront();
}

template <class T>
T GenQueue<T>::peek() {
    return myQueue.getFront();
}

template <class T>
bool GenQueue<T>::isEmpty(){
    return myQueue.isEmpty();
}

template <class T>
int GenQueue<T>::getSize() {
    return myQueue.getSize();
}

template <class T>
void GenQueue<T>::printQueue() {
    myQueue.printList();
}
template <class T>
GenQueue<T>::GenQueue() {
    queueSize = 0;
    DoublyLinkList<T> myQueue = DoublyLinkList<T>();
}

template <class T>
GenQueue<T>::GenQueue(int size) {
    queueSize = size;
    DoublyLinkList<T> myQueue = DoublyLinkList<T>();
}

template <class T>
GenQueue<T>::~GenQueue() {
}




template <class T>
class GenStack {
    public:
        GenStack();
        GenStack(int size);
        ~GenStack();

        void push(T item);
        T pop();
        T peek();

        bool isEmpty();  
        int  getSize(); 
        void printStack(); 
        void clear();

        int stackSize;
        DoublyLinkList<T> myStack;
};
template <class T>
bool GenStack<T>::isEmpty(){
    return myStack.isEmpty();
}

template <class T>
int GenStack<T>::getSize() {
    return myStack.getSize();
}

template <class T>
void GenStack<T>::printStack() {
    myStack.printList();
}

template <class T>
void GenStack<T>::clear() {
    while(!myStack.isEmpty()) {
        myStack.removeFront();
    }
}
template <class T>
GenStack<T>::~GenStack() {
   
}
template <class T>
GenStack<T>::GenStack() {
    stackSize = 0;
    DoublyLinkList<T> myStack = DoublyLinkList<T>();
}

template <class T>
GenStack<T>::GenStack(int size) {
    stackSize = size;
    DoublyLinkList<T> myStack = DoublyLinkList<T>();
}

template <class T>
void GenStack<T>::push(T item) {
    myStack.insertFront(item);
}

template <class T>
T GenStack<T>::pop() {
    return myStack.removeFront();
}

template <class T>
T GenStack<T>::peek() {
    return myStack.getFront();
}


#endif 

