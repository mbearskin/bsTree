//Martha Winger-Bearskin
//mybstree.h
//homework 7

#ifndef MYBSTREE_H
#define MYBSTREE_H
#include <string>
#include <iostream>

using namespace std;

#include "abstractbstree.h"


// ------------------------------------------------------------
template < typename T >
class BSTreeNode
{
public:
    T m_data;
    BSTreeNode<T>* m_left;
    BSTreeNode<T>* m_right;
    
    BSTreeNode(const T & data, BSTreeNode<T> *lt, BSTreeNode<T> *rt)
    : m_data(data), m_left( lt ), m_right( rt )
    { }
    
};


// ------------------------------------------------------------
template < typename T >
class MyBSTree: public AbstractBSTree<T>
{
    private:
        BSTreeNode<T>* m_root;
        int m_size;
    
        //*******All recursive functions are private*******//

        BSTreeNode<T> * clone(const BSTreeNode<T>* t) const;
        int rec_height(BSTreeNode<T> * t)const;
        const T& findMax_rec(BSTreeNode<T> * t) const;
        const T& findMin_rec(BSTreeNode<T> * t) const;
        void rec_clear(BSTreeNode<T> *&t);
        bool rec_insert(BSTreeNode<T>* &t , const T& x);
        bool remove_rec(BSTreeNode<T> * &t, const T& x);
        void prettyPrint (const BSTreeNode<T>* t, int pad)const;
        void PreOrder_rec(BSTreeNode<T> *t) const;
        void PostOrder_rec(BSTreeNode<T> *t) const;
        int contains_rec(const BSTreeNode<T> *t, const T& x,  int count) const;

    
    public:
        //constructor
        MyBSTree(): m_root(NULL), m_size(0)
        {}
        //copy constructor
        MyBSTree(const MyBSTree<T> & rhs): m_root(NULL)
        {
            *this = rhs;
        }
        //destructor
        ~MyBSTree()
        {
            clear();
        }
        //operator =
        const MyBSTree & operator=(const MyBSTree<T> & rhs);
    
    
        //*********Non-recurstive function******//
        virtual int size() const;
        virtual bool isEmpty() const;
        virtual int height() const;
        virtual const T& findMax() const;
        virtual const T& findMin() const;
        virtual int contains(const T& x) const;
        virtual void clear();
        virtual void insert(const T& x);
        virtual void remove(const T& x);
        virtual void printPreOrder() const;
        virtual void printPostOrder() const;
        virtual void print() const;
    
    
    
    
};



#include "mybstree.hpp"
#endif