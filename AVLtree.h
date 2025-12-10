
#ifndef DATAHW1_AVLTREE_H
#define DATAHW1_AVLTREE_H
#include "AVLnode.h"
#include <iostream>


template <class Key , class Data>
class AVLtree {
public:
    AVLnode<Key,Data>* m_root;
    AVLnode<Key,Data>* max;
    AVLnode<Key,Data>* min;
    int m_size;
    AVLtree();
    ~AVLtree();
    void destroyTree(AVLnode<Key,Data>* root);
    void insert(Key newKey, Data newData);
    bool ifExist(Key key);
    void updateHeight(AVLnode<Key,Data>* leaf);
    int findMaxSon(AVLnode<Key,Data>* parent);
    void rotate(AVLnode<Key,Data>* current);
    void insertRotate(AVLnode<Key,Data>* current);
    void eraseRotate(AVLnode<Key,Data>* current);
    void print2D();
    void LLrotation(AVLnode<Key,Data>* unbalanced);
    bool ifRightChild(AVLnode<Key,Data>* myNode);
    bool ifleftChild(AVLnode<Key,Data>* myNode);
    void LRrotation(AVLnode<Key,Data>* unbalanced);
    void RRrotation(AVLnode<Key,Data>* unbalanced);
    void RLrotation(AVLnode<Key,Data>* unbalanced);
    int balanceFactor(AVLnode<Key,Data>* current);
    void erase(AVLnode<Key,Data>* current);
    AVLnode<Key,Data>* findNext(AVLnode<Key,Data>* current);
    AVLnode<Key,Data>* swapToDelete(AVLnode<Key,Data>* current);
    void eraseKey(Key key);
    //void testSwap(Key key );
    //void empty();
    // bool isGood();
    //bool isGoodAux(AVLnode<Key,Data>* current);
    //bool is_tree_valid(AVLnode<Key, Data> *root);
    Data getData(Key key);
    void deleteDatas();
    void deleteDatasAux(AVLnode<Key , Data>* root);
    void updatemin();
    void updatemax();
    void print2Dpointer();
    class Iterator;
    Iterator begin();
    Iterator end();
    AVLnode<Key, Data>* getNextInOrder(AVLnode<Key,Data> *Node);


};



template<class Key, class Data>
class AVLtree<Key, Data>::Iterator {
private:
    AVLtree<Key, Data> *m_tree;
    AVLnode<Key,Data> *m_current;

    friend class AVLtree<Key, Data>;

public:
    Iterator(AVLtree<Key, Data> *tree, AVLnode<Key,Data> *current);

    ~Iterator() = default;

    bool operator==(const Iterator &iterator) const;

    bool operator!=(const Iterator &iterator) const;

    Iterator &operator++();

    AVLnode<Key,Data> *operator*() const;

    Iterator &operator=(const Iterator &) = default;

    Iterator(const Iterator &) = default;

};



template<class Key, class Data>
typename AVLtree<Key, Data>::Iterator AVLtree<Key, Data>::begin() {
    return Iterator(this, this->min);
}

template<class Key, class Data>
typename AVLtree<Key, Data>::Iterator AVLtree<Key, Data>::end() {
    return Iterator(this, nullptr);
}


template<class Key, class Data>
AVLtree<Key, Data>::Iterator::Iterator(AVLtree<Key, Data> *tree, AVLnode<Key,Data> *current) : m_tree(tree), m_current(current) {}

template<class Key, class Data>
AVLnode<Key,Data> *AVLtree<Key, Data>::Iterator::operator*() const {
    return m_current;
}

template<class Key, class Data>
typename AVLtree<Key, Data>::Iterator &AVLtree<Key, Data>::Iterator::operator++() {
    if ((**this) == nullptr) {
        return *this;
    }
    this->m_current = this->m_tree->getNextInOrder(this->m_current);
    return *this;
}


template<class Key, class Data>
bool AVLtree<Key, Data>::Iterator::operator==(const Iterator &iterator) const {
    if ((iterator.m_current == nullptr) || ((**this) == nullptr)) {
        if (((iterator.m_current == nullptr) && (**this == nullptr))) {
            return true;
        } else {
            return false;
        }
    }
    return (iterator.m_current->m_key == this->m_current->m_key);
}

template<class Value, class Condition>
bool AVLtree<Value, Condition>::Iterator::operator!=(const Iterator &iterator) const {
    return !(*this == iterator);
}

template<class Key, class Data>
AVLnode<Key, Data> *AVLtree<Key, Data>::getNextInOrder(AVLnode<Key,Data> *Node) {
    if (Node == nullptr || this->m_root == nullptr) {
        return nullptr;
    }

    if (Node->m_rightSon == nullptr) {
        if (Node->m_parent == nullptr) {
            return nullptr;
        }
        while (Node->m_parent->m_rightSon == Node) {
            Node = Node->m_parent;
            if (Node->m_parent == nullptr) {
                return nullptr;
            }
        }
        return Node->m_parent;
    } else {
        Node = Node->m_rightSon;
        while ((Node->m_leftSon) != nullptr) {
            Node = Node->m_leftSon;
        }
        return Node;
    }

}


template <class Key , class Data>
AVLtree<Key , Data>::AVLtree():m_root(nullptr) , max(nullptr) , min(nullptr), m_size(0){}


template <class Key , class Data>
AVLtree<Key , Data>:: ~AVLtree(){
    this->destroyTree(this->m_root);
}
template <class Key , class Data>
void AVLtree<Key, Data>::destroyTree(AVLnode<Key,Data>* root ) {
    if(root== nullptr){
        return;
    }
    destroyTree(root->m_rightSon);
    destroyTree(root->m_leftSon);
    try {
        delete root;
    }catch(...){
        throw;
    }
}



template <class Key , class Data>
void AVLtree<Key, Data>::insert(Key newKey, Data newData) {
    if(ifExist(newKey)){
        return;
    }
    AVLnode<Key, Data> *newNode= nullptr;
    try {
        newNode = new AVLnode<Key, Data>(newKey, newData);
    }catch(...){
        throw;

    }
    AVLnode<Key, Data>* temp=m_root;
    AVLnode<Key, Data>* tempParent=m_root;
    if(m_root== nullptr){
        m_root=newNode;
        m_size++;
        updatemax();
        updatemin();
        return;
    }
    while(temp!= nullptr) {
        if (newNode->m_key < temp->m_key) {
            tempParent = temp;
            temp = temp->m_leftSon;

        } else {
            tempParent = temp;
            temp = temp->m_rightSon;
        }
    }
    if((newNode->m_key) > (tempParent->m_key)){
        tempParent->m_rightSon=newNode;
        newNode->m_parent=tempParent;
        newNode->m_height=0;
    }
    if(newNode->m_key < tempParent->m_key){
        tempParent->m_leftSon=newNode;
        newNode->m_parent=tempParent;
        newNode->m_height=0;
    }
    updateHeight(newNode);
    insertRotate(newNode);
    if(max== nullptr &&min== nullptr){
        max=newNode;
        min=newNode;
    }else{
        if(newNode->m_key > max->m_key ){
            max=newNode;
        }
        if(newNode->m_key< min->m_key){
            min =newNode;
        }
    }
    m_size++;
}

template <class Key , class Data>
bool AVLtree<Key, Data>::ifExist(Key key) {
    AVLnode<Key, Data>* temp=m_root;
    while(temp!= nullptr){
        if(key==temp->m_key){
            return true;
        }
        if(key<temp->m_key){
            temp=temp->m_leftSon;
        }else{
            temp=temp->m_rightSon;
        }
    }
    return false;
}

template <class Key , class Data>
void AVLtree<Key , Data>::updateHeight(AVLnode<Key, Data> *leaf) {
    AVLnode<Key, Data>* temp=leaf;

    while(temp!=m_root&&temp!= nullptr){
        temp->m_height= findMaxSon(temp)+1;
        temp=temp->m_parent;
    }
    m_root->m_height= findMaxSon(m_root)+1;
}


template <class Key , class Data>
int AVLtree<Key, Data>::findMaxSon(AVLnode<Key, Data> *parent) {
    if(parent->m_leftSon== nullptr&&parent->m_rightSon== nullptr){
        return -1;
    }else {
        if(parent->m_rightSon== nullptr){
            return parent->m_leftSon->m_height;
        }
        if(parent->m_leftSon== nullptr){
            return parent->m_rightSon->m_height;
        }
    }
    if(parent->m_leftSon!= nullptr&&parent->m_rightSon!= nullptr){
        if(parent->m_leftSon->m_height > parent->m_rightSon->m_height){
            return parent->m_leftSon->m_height;
        }else{
            return parent->m_rightSon->m_height;
        }
    }
    return 0;
}

template<class Key, class Data>
void print2DUtil(AVLnode<Key, Data>* root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->m_rightSon, space);

    // Print current node after space

    // count
    std::cout << std::endl;
    for (int i = 10; i < space; i++)
    {
        std::cout << " " ;
    }
    std::cout << "id=" << root->m_key << "  H=" << root->m_height << std::endl;


    print2DUtil(root->m_leftSon, space);
}

// Wrapper over print2DUtil()
template<class Key, class Data>
void AVLtree<Key, Data>::print2D() {
    // Pass initial space count as 0
    print2DUtil(m_root, 0);
    std::cout << "\n\n\n" << std::endl;
}//namespace DS

template<class Key, class Data>
void AVLtree<Key , Data>::rotate(AVLnode<Key,Data>* current) {
    int BF= balanceFactor(current);
    if(BF==2){
        if(balanceFactor(current->m_leftSon)==-1){
            LRrotation(current);
            return;
        }else{
            LLrotation(current);
            return;
        }
    }else{
        if(balanceFactor(current->m_rightSon)==1){
            RLrotation(current);
            return;
        }else{
            RRrotation(current);
            return;
        }
    }
}


template<class Key, class Data>
void AVLtree<Key , Data>::LLrotation(AVLnode<Key, Data> *unbalanced) {
    if(unbalanced==m_root){
        AVLnode<Key, Data>* AR=unbalanced->m_leftSon->m_rightSon;
        AVLnode<Key, Data>* A=unbalanced->m_leftSon;
        m_root=A;
        A->m_rightSon=unbalanced;
        A->m_parent= nullptr;
        unbalanced->m_parent=A;
        unbalanced->m_leftSon=AR;
        if(AR){
            AR->m_parent=unbalanced;
        }
        unbalanced->m_height= findMaxSon(unbalanced)+1;
        m_root->m_height= findMaxSon(m_root)+1;
        updateHeight(A);
        return;
    }
    AVLnode<Key, Data>* AR=unbalanced->m_leftSon->m_rightSon;
    AVLnode<Key, Data>* A=unbalanced->m_leftSon;
    AVLnode<Key, Data>* parent=unbalanced->m_parent;
    if(ifRightChild(unbalanced)) {
        parent->m_rightSon = A;

    }
    if(ifleftChild(unbalanced)){
        parent->m_leftSon=A;

    }
    A->m_rightSon=unbalanced;
    A->m_parent= parent;
    unbalanced->m_parent=A;
    unbalanced->m_leftSon=AR;
    if(AR){
        AR->m_parent=unbalanced;
    }
    unbalanced->m_height= findMaxSon(unbalanced)+1;
    A->m_height= findMaxSon(A)+1;
    updateHeight(A);
    return;

}


template<class Key, class Data>
bool AVLtree<Key , Data>::ifRightChild(AVLnode<Key, Data> *myNode) {
    if(m_root==myNode){
        return false;
    }
    if(myNode==myNode->m_parent->m_rightSon){
        return true;
    }
    return false;
}

template<class Key, class Data>
bool AVLtree<Key , Data>::ifleftChild(AVLnode<Key, Data> *myNode) {
    if(m_root==myNode){
        return false;
    }
    if(myNode==myNode->m_parent->m_leftSon){
        return true;
    }
    return false;
}
template<class Key, class Data>
void AVLtree<Key , Data>::LRrotation(AVLnode<Key, Data> *unbalanced){
    AVLnode<Key, Data>* B =unbalanced->m_leftSon->m_rightSon;
    AVLnode<Key, Data>* A =unbalanced->m_leftSon;
    AVLnode<Key, Data>* parent=unbalanced->m_parent;
    unbalanced->m_leftSon=B->m_rightSon;
    A->m_rightSon=B->m_leftSon;
    if(B->m_rightSon!= nullptr) {
        B->m_rightSon->m_parent = unbalanced;
    }
    if(B->m_leftSon!= nullptr) {
        B->m_leftSon->m_parent = A;
    }
    A->m_parent=B;
    B->m_parent=parent;
    if(unbalanced==m_root) {
        m_root = B;
    }else {
        if (ifleftChild(unbalanced)) {
            parent->m_leftSon = B;
        }
        if (ifRightChild(unbalanced)) {
            parent->m_rightSon = B;
        }
    }
    B->m_leftSon=A;
    B->m_rightSon=unbalanced;
    unbalanced->m_parent=B;
    updateHeight(unbalanced);
    updateHeight(A);
}



template<class Key, class Data>
void AVLtree<Key , Data>::RRrotation(AVLnode<Key, Data> *unbalanced){
    AVLnode<Key, Data>* B =unbalanced->m_rightSon;
    AVLnode<Key, Data>* parent =unbalanced->m_parent;
    if(B->m_leftSon!= nullptr) {
        B->m_leftSon->m_parent = unbalanced;
    }
    unbalanced->m_rightSon=B->m_leftSon;
    B->m_leftSon=unbalanced;
    B->m_parent=parent;
    if(unbalanced==m_root){
        m_root=B;
    }else{
        if(ifRightChild(unbalanced)){
            parent->m_rightSon=B;
        }
        if(ifleftChild(unbalanced)){
            parent->m_leftSon=B;
        }
    }
    unbalanced->m_parent=B;
    unbalanced->m_height= findMaxSon(unbalanced)+1;
    updateHeight(unbalanced);
}

template<class Key, class Data>
void AVLtree<Key , Data>::RLrotation(AVLnode<Key, Data> *unbalanced){
    AVLnode<Key, Data>* B =unbalanced->m_rightSon;
    AVLnode<Key, Data>* parent =unbalanced->m_parent;
    AVLnode<Key, Data>* C =unbalanced->m_rightSon->m_leftSon;
    if(C->m_rightSon){
        C->m_rightSon->m_parent=B;
    }
    if(C->m_leftSon){
        C->m_leftSon->m_parent=unbalanced;
    }
    if(unbalanced==m_root){
        m_root=C;
    }else{
        if(ifRightChild(unbalanced)){
            parent->m_rightSon=C;
        }
        if(ifleftChild(unbalanced)){
            parent->m_leftSon=C;
        }
    }
    unbalanced->m_rightSon=C->m_leftSon;
    B->m_leftSon=C->m_rightSon;
    unbalanced->m_parent=C;
    C->m_leftSon=unbalanced;
    B->m_parent=C;
    C->m_rightSon=B;
    C->m_parent=parent;
    updateHeight(unbalanced);
    updateHeight(B);
    updateHeight(C);

}
template<class Key, class Data>
int AVLtree<Key , Data>::balanceFactor(AVLnode<Key, Data> *current) {
    int leftHeight=0 , rigthHeight=0;
    if(current->m_leftSon== nullptr){
        leftHeight=-1;
    }else{
        leftHeight=current->m_leftSon->m_height;
    }
    if(current->m_rightSon== nullptr){
        rigthHeight=-1;
    }else{
        rigthHeight=current->m_rightSon->m_height;
    }
    return leftHeight-rigthHeight;
}

template<class Key, class Data>
void AVLtree<Key , Data>::insertRotate(AVLnode<Key, Data> *current) {
    AVLnode<Key , Data>* temp=current;
    while(temp!= nullptr){
        if(balanceFactor(temp)==2|| balanceFactor(temp)==-2){
            rotate(temp);
            return;
        }
        temp=temp->m_parent;
    }
}
template<class Key, class Data>
void AVLtree<Key , Data>::erase(AVLnode<Key, Data> *current) {
    if(current== nullptr)
        return;

    if(current->m_leftSon== nullptr && current->m_rightSon== nullptr){
        if(m_root==current){//only one node
            m_root= nullptr;
            try{
                delete current;
            }catch(...){
                throw;
            }
            max= nullptr;
            min= nullptr;
            m_size--;
            return;
        }
        if(ifRightChild(current)){
            current->m_parent->m_rightSon= nullptr;
            updateHeight(current->m_parent);
            eraseRotate(current->m_parent);
            try{
                delete current;
            }catch(...){
                throw;
            }
            updatemax();
            updatemin();
            m_size--;
            return;
        }else{
            current->m_parent->m_leftSon= nullptr;
            updateHeight(current->m_parent);
            eraseRotate(current->m_parent);
            try{
                delete current;
            }catch(...){
                throw;
            }
            updatemax();
            updatemin();
            m_size--;
            return;
        }
    }

    if(current->m_leftSon== nullptr || current->m_rightSon== nullptr){
        if(m_root->m_key==current->m_key){
            if(current->m_leftSon){
                m_root=current->m_leftSon;
                m_root->m_parent= nullptr;
            }else{
                m_root=current->m_rightSon;
                m_root->m_parent= nullptr;
            }
            try{
                delete current;
            }catch(...){
                throw;
            }
            updatemax();
            updatemin();
            m_size--;
            return;
        }
        if(ifRightChild(current)){
            if(current->m_rightSon== nullptr){
                current->m_parent->m_rightSon=current->m_leftSon;
                current->m_leftSon->m_parent=current->m_parent;
            }else{
                current->m_parent->m_rightSon=current->m_rightSon;
                current->m_rightSon->m_parent=current->m_parent;
            }
            updateHeight(current->m_parent);
            eraseRotate(current->m_parent);
            try{
                delete current;
            }catch(...){
                throw;
            }
            updatemax();
            updatemin();
            m_size--;
            return;
        }else{
            if(current->m_rightSon== nullptr){
                current->m_parent->m_leftSon=current->m_leftSon;
                current->m_leftSon->m_parent=current->m_parent;
            }else{
                current->m_parent->m_leftSon=current->m_rightSon;
                current->m_rightSon->m_parent=current->m_parent;
            }
            updateHeight(current->m_parent);
            eraseRotate(current->m_parent);
            try{
                delete current;
            }catch(...){
                throw;
            }
            updatemax();
            updatemin();
            m_size--;
            return;
        }
    }
    if(current->m_leftSon!= nullptr && current->m_rightSon!= nullptr){
        AVLnode<Key, Data>* toDelete=swapToDelete(current);
        erase(toDelete);
        return;
    }

}

template<class Key, class Data>
AVLnode<Key, Data>* AVLtree<Key ,Data>::swapToDelete(AVLnode<Key, Data> *current) {
    AVLnode<Key, Data>* next= findNext(current);
    int heightTemp=0;
    if(current->m_rightSon->m_key==next->m_key){
        if(current->m_key==m_root->m_key){
            AVLnode<Key, Data>* nextRightChild=next->m_rightSon;
            m_root=next;
            if(current->m_leftSon){
                current->m_leftSon->m_parent=next;
            }
            next->m_rightSon=current;
            next->m_leftSon=current->m_leftSon;
            current->m_parent=next;
            current->m_rightSon=nextRightChild;
            if(nextRightChild!= nullptr) {
                nextRightChild->m_parent = current;
            }
            next->m_parent= nullptr;
            heightTemp=current->m_height;
            current->m_height=next->m_height;
            next->m_height=heightTemp;
            current->m_leftSon= nullptr;

            return current ;
        }else{
            AVLnode<Key, Data>* parentCurrent=current->m_parent;
            AVLnode<Key, Data>* nextRightChild=next->m_rightSon;
            AVLnode<Key, Data>* leftcurrent=current->m_leftSon;
            next->m_parent=parentCurrent;
            next->m_rightSon=current;
            if(ifRightChild(current)) {
                parentCurrent->m_rightSon = next;
            }else{
                parentCurrent->m_leftSon=next;
            }
            current->m_parent=next;
            current->m_rightSon=nextRightChild;
            current->m_leftSon= nullptr;
            next->m_leftSon=leftcurrent;
            if(leftcurrent!= nullptr){
                leftcurrent->m_parent=next;
            }
            if(nextRightChild != nullptr) {
                nextRightChild->m_parent = current;
            }
            heightTemp=current->m_height;
            current->m_height=next->m_height;
            next->m_height=heightTemp;
            current->m_leftSon= nullptr;
            return current;
        }
    }
    AVLnode<Key, Data>* parentNext= next->m_parent;
    AVLnode<Key, Data>* nextRightChild= next->m_rightSon;
    if(current->m_key==m_root->m_key){
        if(ifRightChild(next)){
            parentNext->m_rightSon=current;
        }else{
            parentNext->m_leftSon =current;
        }
        next->m_rightSon=current->m_rightSon;
        next->m_leftSon=current->m_leftSon;
        next->m_leftSon->m_parent=next;
        next->m_rightSon->m_parent=next;
        m_root=next;
        next->m_parent= nullptr; // 3laa added this
        heightTemp=current->m_height;
        current->m_height=next->m_height;
        next->m_height=heightTemp;
        current->m_parent=parentNext;
        current->m_leftSon= nullptr;
        current->m_rightSon=nextRightChild;
        if(nextRightChild!=nullptr){
            nextRightChild->m_parent=current;
        }

        return current;

    }else{
        next->m_rightSon=current->m_rightSon;
        next->m_leftSon=current->m_leftSon;
        next->m_leftSon->m_parent=next;
        next->m_rightSon->m_parent=next;
        if(ifRightChild(next)){
            parentNext->m_rightSon=current;
        }else{
            parentNext->m_leftSon=current;
        }
        next->m_parent=current->m_parent;
        if(ifRightChild(current)){
            current->m_parent->m_rightSon=next;
        }else{
            current->m_parent->m_leftSon=next;
        }
        heightTemp=current->m_height;
        current->m_height=next->m_height;
        next->m_height=heightTemp;
        current->m_parent=parentNext;
        current->m_rightSon= nextRightChild;
        current->m_leftSon= nullptr;
        if(nextRightChild!= nullptr){
            nextRightChild->m_parent=current;
        }

        return current;
    }

}

template<class Key, class Data>
AVLnode<Key, Data>* AVLtree<Key ,Data>::findNext(AVLnode<Key, Data> *current) {
    AVLnode<Key, Data> * temp=current->m_rightSon;
    AVLnode<Key, Data> * last=current;
    while(temp!= nullptr){
        last=temp;
        temp=temp->m_leftSon;
    }
    return last;
}

template<class Key, class Data>
void AVLtree<Key , Data>::eraseRotate(AVLnode<Key, Data> *current) {
    AVLnode<Key , Data>* temp=current;
    while(temp!= nullptr){
        if(balanceFactor(temp)==2|| balanceFactor(temp)==-2){
            rotate(temp);
        }
        temp=temp->m_parent;
    }
}
template<class Key, class Data>
void AVLtree<Key , Data>::eraseKey(Key key) {
    if(!ifExist(key)){
        return;
    }
    AVLnode<Key, Data>* temp=m_root;
    while(temp!= nullptr){
        if(key==temp->m_key){
            erase(temp);
            return;
        }
        if(key<temp->m_key){
            temp=temp->m_leftSon;
        }else{
            temp=temp->m_rightSon;
        }
    }
}
/*
template<class Key, class Data>
void AVLtree<Key , Data>::testSwap(Key key) {
    AVLnode<Key, Data>* temp=m_root;
    while(temp!= nullptr){
        if(key==temp->m_key){
            break;
        }
        if(key<temp->m_key){
            temp=temp->m_leftSon;
        }else{
            temp=temp->m_rightSon;
        }
    }
    swapToDelete(temp);
}
 */
/*
template<class Key, class Data>
void AVLtree<Key , Data>::empty() {
    while(m_root!= nullptr){
        eraseKey(m_root->m_key);
        print2D();
    }

}

 */
/*
template<class Key, class Data>
bool AVLtree<Key , Data>::isGood() {
    return is_tree_valid(m_root);
}

template<class Key, class Data>
bool AVLtree<Key , Data>::isGoodAux(AVLnode<Key, Data> *current) {
    if(current== nullptr){
        return true;
    }
    if(current->m_rightSon){
        if(current->m_key!=current->m_rightSon->m_parent->m_key){
            return false;
        }
    }
    if(current->m_leftSon){
        if(current->m_key!=current->m_leftSon->m_parent->m_key){
            return false;
        }
    }

    return isGoodAux(current->m_leftSon)&& isGoodAux(current->m_rightSon);
}*/
/*
template<class Key, class Data>
bool AVLtree<Key , Data>::is_tree_valid(AVLnode<Key, Data> *root) {
    if (!root) {
        return true;
    }
    // Checks the height of every node is valid

    if (!root->m_leftSon && !root->m_rightSon && root->m_height != 0) {
        std::cout << "Leaf Height is not valid" << std::endl;
        return false;
    }
    //checks the Tree is a Binary Search Tree
    if (root->m_leftSon && root->m_leftSon->m_key >= root->m_key) {
        std::cout << "Left son is not smaller than root" << std::endl;
        return false;
    }
    if (root->m_rightSon && root->m_rightSon->m_key <= root->m_key) {
        std::cout << "Right son is not bigger than root" << std::endl;
        return false;
    }

    //checks that the Balance Factor of every node is valid
    if (std::abs(balanceFactor(root)) > 1) {
        std::cout << "Balance Factor is not valid" << std::endl;
        return false;
    }
    //checks that the parent pointer is valid
    if (root->m_parent) {
        if (root->m_parent->m_leftSon != root && root->m_parent->m_rightSon != root) {
            std::cout << "Parent pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->m_leftSon) {
        if (root->m_leftSon->m_parent != root) {
            std::cout << "Parent's Left Son pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->m_rightSon) {
        if (root->m_rightSon->m_parent != root) {
            std::cout << "Parent's Right Son pointer is not valid" << std::endl;
            return false;
        }
    }
    return is_tree_valid(root->m_leftSon) && is_tree_valid(root->m_rightSon);
}
*/
template<class Key, class Data>
Data AVLtree<Key , Data>::getData(Key key) {
    AVLnode<Key, Data>* temp=m_root;
    while(temp!= nullptr){
        if(key==temp->m_key){
            return (temp->m_data);
        }
        if(key<temp->m_key){
            temp=temp->m_leftSon;
        }else{
            temp=temp->m_rightSon;
        }
    }
    return nullptr;
}
template<class Key, class Data>
void AVLtree<Key , Data>::deleteDatas() {
    deleteDatasAux(m_root);
}

template<class Key, class Data>
void AVLtree<Key , Data>::deleteDatasAux(AVLnode<Key, Data> *root) {
    if(root== nullptr){
        return;
    }
    try{
        delete root->m_data;
    }catch(...){
        throw;
    }
    root->m_data= nullptr;
    deleteDatasAux(root->m_leftSon);
    deleteDatasAux(root->m_rightSon);
}
template<class Key, class Data>
void AVLtree<Key , Data>::updatemax() {
    AVLnode<Key , Data>* temp=m_root;
    if(m_root == nullptr){
        max=nullptr;
        return;
    }
    while(temp->m_rightSon!=nullptr){
        temp=temp->m_rightSon;
    }
    max= temp;
}

template<class Key, class Data>
void AVLtree<Key , Data>::updatemin() {
    AVLnode<Key , Data>* temp=m_root;
    if(m_root == nullptr){
        min=nullptr;
        return;
    }
    while(temp->m_leftSon!=nullptr){
        temp=temp->m_leftSon;
    }
    min =temp;
}

///////////////////////////////////////////////////////////////////////////
template<class Key, class Data>
void print2DUtilpointer(AVLnode<Key, Data>* root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtilpointer(root->m_rightSon, space);

    // Print current node after space

    // count
    std::cout << std::endl;
    for (int i = 10; i < space; i++)
    {
        std::cout << " " ;
    }
    std::cout << "id=" << *root->m_key << "  H=" << root->m_height << std::endl;


    print2DUtilpointer(root->m_leftSon, space);
}

// Wrapper over print2DUtil()
template<class Key, class Data>
void AVLtree<Key, Data>::print2Dpointer() {
    // Pass initial space count as 0
    print2DUtilpointer(m_root, 0);
    std::cout << "\n\n\n" << std::endl;
}//namespace DS

#endif //DATAHW1_AVLTREE_H
