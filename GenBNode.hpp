#ifndef _GenBNode_HPP_
#define _GenBNode_HPP_
template <class T>
class GenBNode
{
    public:
GenBNode(T *inputData){
    data = inputData;
    leftPtr = nullptr;
    rightPtr = nullptr;
}
GenBNode(T *inputData, GenBNode<T> *left, GenBNode *right){
    data = inputData;
    leftPtr = left;
    rightPtr = right;
}
~GenBNode() {
    delete leftPtr;
    delete rightPtr;
}
void leftPtrSetter(GenBNode<T> *left) {
 leftPtr = left; 
 }
void rightPtrSetter(GenBNode<T> *right) { 
rightPtr = right; 
}
bool isLeaf() const { 
return (leftPtr == nullptr && rightPtr == nullptr); 
}
GenBNode<T> *getRightPtr() const {
 return rightPtr; 
}
void setData(T *inputData) {
         data = inputData; 
}
    T *getData() const { 
return data; 
}
    GenBNode<T> *getLeftPtr() const { 
return leftPtr; 
}
private:
    T *data;    
    GenBNode<T> *rightPtr;              
    GenBNode<T> *leftPtr;  

};
#endif