#ifndef _GenBST_HPP_
#define _GenBST_HPP_
#include "GenBNode.hpp"
#include "GenStructures.hpp"
#include <typeinfo>
#include <time.h>

template <class T>
class GenBST
{
protected:
    GenBNode<T> *rootPtr;
    int count;              
    DoublyLinkList<T> insertedNodes;
    ofstream outFile;
public:
GenBST(){
    rootPtr = nullptr;
    count = 0;
}
~GenBST() { 
    delete rootPtr; 
}
    //functions defined in general BST went over in class
    void clear() {destroyTree(rootPtr);}
    bool remove(T *anEntry);
    bool isEmpty() const { return count == 0; }
    int getsize() const { return count; }
    void printTree(void visit(T *)) const;
    void writeTree(string fileName) const;
    void insert(T *newEntry);
     void printAsTree(void visit(T *)) {

  _printAsTree(visit, 1, rootPtr);
}
    
   
    
    T *find(T *val);
    bool search(T *val);
    T getRandomNode();
   

private:
    void _inOrder(void visit(T *), GenBNode<T> *node) const;
    void _printAsTree(void visit(T *), int level, GenBNode<T> *nodePtr) const;
    void destroyTree(GenBNode<T>* nodePtr);
    void _writeInOrder(string fileName, GenBNode<T> *node) const;
    GenBNode<T> *_insert(GenBNode<T> *nodePtr, GenBNode<T> *newNodePtr);
    
    GenBNode<T> *_remove(GenBNode<T> *nodePtr, T *target, bool &success);
    GenBNode<T> *deleteNode(GenBNode<T> *targetNodePtr);
    GenBNode<T> *removeLeftmostNode(GenBNode<T> *nodePtr, T *successor);

};
template <class T>
void GenBST<T>::printTree(void visit(T *)) const{
    _inOrder(visit, rootPtr);
}

template <class T>
void GenBST<T>::writeTree(string fileName) const{
    _writeInOrder(fileName, rootPtr);
}

template <class T>
void GenBST<T>::insert(T *newEntry){
    GenBNode<T> *newNode = new GenBNode<T>(newEntry);
    rootPtr = _insert(rootPtr, newNode);
    insertedNodes.insertBack(*newEntry);
    count++;
}

template <class T>
bool GenBST<T>::remove(T *target){
     bool isSuccessful = false;

    rootPtr = _remove(rootPtr, target, isSuccessful);
    count= count -1;

    return isSuccessful;
}

template <class T>
T *GenBST<T>::find(T *val){
    if (isEmpty()) {
        cout << "Cannot search empty tree" << endl;
    } else {
        GenBNode<T>* curr = rootPtr;
        while (*curr->getData() != *val) {
            if (*val < *curr->getData())
                curr = curr->getLeftPtr();
            else
                curr = curr->getRightPtr();
            if (curr == nullptr) {
                cout << "The ID you searched for cannot be found" << endl;
            }
        }
        return curr->getData();
    }
    return NULL;
}

template <class T>
bool GenBST<T>::search(T *val){
    if (isEmpty()) {
        return false;
    } else {
        GenBNode<T>* curr = rootPtr;
        while (*curr->getData() != *val) {
            if (*val < *curr->getData()) {
                curr = curr->getLeftPtr();
            } else {
                curr = curr->getRightPtr();
            }
                return false;
            if (curr == nullptr) {
            }
        }
        return true;
    }
}

template <class T>
T GenBST<T>::getRandomNode() {
    srand (time(NULL));
    int randomNumber = rand() % count;
    return insertedNodes.getPosition(randomNumber);
}

template <class T>
void GenBST<T>::_inOrder(void visit(T *), GenBNode<T> *node) const{
    if (node != 0){
        _inOrder(visit, node->getLeftPtr());
        T *item = node->getData();
        visit(item);
        _inOrder(visit, node->getRightPtr());
    }
}

template <class T>
void GenBST<T>::_writeInOrder(string fileName, GenBNode<T> *node) const{
    if (node != 0){
        _writeInOrder(fileName, node->getLeftPtr());
        T *item = node->getData();
        item->writeToFile(fileName);
        _writeInOrder(fileName, node->getRightPtr());
    }
}

template <class T>
GenBNode<T> *GenBST<T>::_insert(GenBNode<T> *nodePtr, GenBNode<T> *newNodePtr){
if (nodePtr == nullptr){
    nodePtr = newNodePtr;
}
else{
    T *newNodeItem = newNodePtr->getData();
    T *nodeItem = nodePtr->getData();
    if (*newNodeItem < *nodeItem){
        if (nodePtr->getLeftPtr() == nullptr)
            nodePtr->leftPtrSetter(newNodePtr);
        else
            _insert(nodePtr->getLeftPtr(), newNodePtr);
    }
    else{

        if (nodePtr->getRightPtr() == nullptr){
            nodePtr->rightPtrSetter(newNodePtr);
        }
        else
            _insert(nodePtr->getRightPtr(), newNodePtr);
    }
}
    return nodePtr;
}

template <class T>
GenBNode<T> *GenBST<T>::_remove(GenBNode<T> *nodePtr, T *target, bool &success){
if (nodePtr == nullptr){
    success = false;
    return 0;
}
T *nodePtrItem = nodePtr->getData();
T *targetItem = target;
if (*nodePtrItem > *target) 
    nodePtr->leftPtrSetter(_remove(nodePtr->getLeftPtr(), target, success));
else if (nodePtrItem < targetItem) 
    nodePtr->rightPtrSetter(_remove(nodePtr->getRightPtr(), target, success));
else{ 
    target = nodePtr->getData();
    nodePtr = deleteNode(nodePtr);
    success = true;
}
 return nodePtr;
}

template <class T>
GenBNode<T> *GenBST<T>::deleteNode(GenBNode<T> *nodePtr){
if (nodePtr->isLeaf()){
    delete nodePtr;
    nodePtr = 0;
    return nodePtr;
}
else if (nodePtr->getLeftPtr() == 0){
    GenBNode<T> *nodeToConnectPtr = nodePtr->getRightPtr();
    delete nodePtr;
    nodePtr = 0;
    return nodeToConnectPtr;
}
else if (nodePtr->getRightPtr() == 0){
    GenBNode<T> *nodeToConnectPtr = nodePtr->getLeftPtr();
    delete nodePtr;
    nodePtr = 0;
    return nodeToConnectPtr;
}
else{
    T *newNodeval = nullptr;
    nodePtr->rightPtrSetter(removeLeftmostNode(nodePtr->getRightPtr(), newNodeval));
    nodePtr->setData(newNodeval);
    return nodePtr;
}
}
template <class T>
GenBNode<T> *GenBST<T>::removeLeftmostNode(GenBNode<T> *nodePtr, T *successor){
if (nodePtr->getLeftPtr() == 0)
{
    successor = nodePtr->getData();
    return deleteNode(nodePtr);
}
else
{
    nodePtr->leftPtrSetter(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
    return nodePtr;
}
}
template<class T>
void GenBST<T>::_printAsTree(void visit(T *), int level, GenBNode<T> *nodePtr) const{
    string indent = " ";
    for (int i = 0; i < level - 1; i++)
    {
        cout << indent;
    }
    cout << "Level" << level << ". ";
    T *item = nodePtr->getData();
    visit(item);
    cout << endl;

if (nodePtr->getRightPtr() != 0)
    _printAsTree(visit, level + 1, nodePtr->getRightPtr());
if (nodePtr->getLeftPtr() != 0)
    _printAsTree(visit, level + 1, nodePtr->getLeftPtr());
}
template<class T>
void GenBST<T>::destroyTree(GenBNode<T>* nodePtr){
    if (nodePtr)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}
#endif