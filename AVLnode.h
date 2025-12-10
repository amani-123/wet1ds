//
// Created by alaah on 11/02/2024.
//

#ifndef DATAHW1_AVLNODE_H
#define DATAHW1_AVLNODE_H
template <class Key , class Data>
class AVLnode {
public:
    Key m_key;
    Data m_data;
    AVLnode* m_leftSon;
    AVLnode* m_rightSon;
    AVLnode* m_parent;
    int m_height;
    AVLnode()=default;
    AVLnode(Key key ,Data data);
    ~AVLnode()=default;
    AVLnode(const AVLnode&)=default; /////check if we need
    bool operator<(AVLnode<Key,Data> &otherNode);
    bool operator>(AVLnode<Key,Data> &otherNode);
    bool operator==(AVLnode<Key,Data> &otherNode);
    bool operator<(Key &other) const;
    bool operator>(Key &other) const;
    bool operator==(Key &other) const;
};
template <class Key , class Data>
AVLnode<Key, Data>::AVLnode(Key key ,Data data) : m_key(key) , m_data(data) , m_leftSon(nullptr) , m_rightSon(nullptr)
         , m_parent(nullptr) ,m_height(0) {}


template<class Key,class Data>
bool AVLnode<Key,Data> ::operator<(AVLnode<Key, Data> &otherNode) {
    return this->m_key<otherNode.m_key;
}

template<class Key,class Data>
bool AVLnode<Key,Data> ::operator>(AVLnode<Key, Data> &otherNode) {
    return this->m_key>otherNode.m_key;
}

template<class Key,class Data>
bool AVLnode<Key,Data> ::operator==(AVLnode<Key, Data> &otherNode) {
    return this->m_key==otherNode.m_key;
}
template<class Key, class DataType>
bool AVLnode<Key, DataType>::operator<( Key &other) const{
    return m_key < other;
}

template<class Key, class DataType>
bool AVLnode<Key, DataType>::operator>( Key &other) const{
    return m_key > other;
}

template<class Key, class DataType>
bool AVLnode<Key, DataType>::operator==( Key &other) const{
    return m_key == other;
}


#endif //DATAHW1_AVLNODE_H
