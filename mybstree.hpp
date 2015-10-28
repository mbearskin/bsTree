//
//  mybstree.cpp
//  bsTree
//
//  Created by Martha Winger-Bearskin on 11/11/13.
//  Copyright (c) 2013 Martha Winger-Bearskin. All rights reserved.
//



//Clone Function used by the operator equals function
template <typename T>
BSTreeNode<T>* MyBSTree<T>::clone(const BSTreeNode<T>* t) const
{
    if (t == NULL)
        return NULL;
    else{
        return new BSTreeNode<T>(t->m_data, clone(t->m_left),clone(t->m_right));
    }
}


//Overloaded operator equals funtion to perform a deep copy of a tree
template <typename T>
const MyBSTree<T>& MyBSTree<T>::operator=(const MyBSTree<T> & rhs)
{
    if(this != &rhs)
    {
        clear();
        m_root = clone(rhs.m_root);
    }
    return *this;
}

// Purpose: Accessor function for the number of elements in the tree
// Returns: number of elements in the tree
template <typename T>
int MyBSTree<T>::size() const
{
    return m_size;
}

// Purpose: Checks if a tree is empty
// Returns: 'true' if the tree is empty
//     'false' otherwise
template <typename T>
bool MyBSTree<T>:: isEmpty() const
{
    if (m_size == 0)
        return true;
    else
        return false;
}

//Purpose: recursice function to calculate height of tree
//returns height of tree
template <typename T>
int MyBSTree<T>::rec_height(BSTreeNode<T> * t)const
{
    int x;
    int y;
    if(t == NULL)
        return 0;
    x = rec_height(t-> m_right);
    y = rec_height(t-> m_left);
    if (x > y)
        return (1 + x);
    else
        return (1 + y);
}

// Purpose: Returns the height of the tree
// Returns: height the tree
template <typename T>
int MyBSTree<T>::height() const
{
    return rec_height(m_root);
    
}

//Purpose: to insert x into the tree using reccursion.
template <typename T>
bool MyBSTree<T>::rec_insert(BSTreeNode<T>* &t , const T& x)
{
    
    if(t==NULL)
    {
        t = new BSTreeNode<T>( x, NULL, NULL);
        return true;
    }
    else if(x < t-> m_data)
        return rec_insert(t->m_left, x);
    else if(x > t-> m_data)
        return rec_insert(t->m_right, x);
    else
        return false;
}

// Purpose: Inserts an element into a tree
// Parameters: x is value to be added to the tree
// Postconditions: The tree now contains x
//     if the tree already contains x, ignore insertion
template <typename T>
void MyBSTree<T>::insert(const T& x)
{
    
    if (rec_insert(m_root, x) )
        m_size++;
}

//Purpose: prettyPrint function called by print()
template <typename T>
void MyBSTree<T>::prettyPrint (const BSTreeNode<T>* t, int pad) const
{
    string s(pad, ' ');
    if (t == NULL)
        cout << endl;
    else
    {
        prettyPrint(t->m_right, pad+4);
        cout << s << t->m_data << endl;
        prettyPrint(t->m_left, pad+4);
    }  
}

// Purpose: Prints the Tree In-Order with formatting
// each level indented 4 spaces, one element per line
template <typename T>
void MyBSTree<T>::print() const
{
    
    prettyPrint(m_root, 0);
}
//recursive clear
template <typename T>
void MyBSTree<T>::rec_clear(BSTreeNode<T> *&t)
{
    if (t != NULL)
    {
        rec_clear(t->m_left);
        rec_clear(t->m_right);
        delete t;
    }
    t = NULL;
}


// Purpose: Clears the Tree
// Postconditions: an empty Tree
template <typename T>
void MyBSTree<T>::clear()
{
    rec_clear(m_root);
}

//Recursive function to find max valus of tree
template <typename T>
const T& MyBSTree<T>::findMax_rec(BSTreeNode<T> * t) const
{
    string error = "PANIC : Tree is Empty!!";
    if(t== NULL)
        throw error; // throw error message
    if(t->m_right == NULL)
        return t->m_data;
    else
        return findMax_rec(t->m_right);
}

// Purpose: finds the maximum element in the Tree
// Returns: a const reference to the maximum element
template <typename T>
const T& MyBSTree<T>::findMax() const
{
    return findMax_rec(m_root);
}

//Recursive function used to find the minimum value in tree
template <typename T>
const T& MyBSTree<T>::findMin_rec(BSTreeNode<T> * t) const
{
    string error = "PANIC : Tree is Empty!!";
    if(t== NULL)
        throw error;
    if(t->m_left== NULL)
        return t->m_data;
    else
        return findMin_rec(t->m_left);
}

// Purpose: finds the minimum element in the Tree
// Returns: a const reference to the minimum element
template <typename T>
const T& MyBSTree<T>::findMin() const
{
    return findMin_rec(m_root);
}

template <typename T>
int MyBSTree<T>::contains_rec(const BSTreeNode<T> *t, const T& x, int count)const
{
    if(t == NULL)
        return -count;
    if(t->m_data == x)
        return count;
    if(x < t->m_data)
        return contains_rec(t->m_left, x, (count +1));
    else
        return contains_rec(t->m_right, x, (count+1));
}



//*****************************************needs to write!!****
// Purpose: finds an element in the Tree
// Parameters: x is value to be found
// Returns:
//     If The tree contains x then
//         return N, the level of the node containing x
//         (the root is considered level 0)
//     If The tree does not contains x then
//         return -N, where N is the level of the tree reached in the search

template <typename T>
int MyBSTree<T>::contains(const T& x) const
{
    return contains_rec(m_root, x, 0);
}

//Recursive function to remove nodes from tree
template <typename T>
bool MyBSTree<T>::remove_rec(BSTreeNode<T> *&t, const T& x)
{
    BSTreeNode<T> * tmp;
    if (t == NULL)
        return false;
    if(x < t->m_data)
        remove_rec(t->m_left, x);
    else if(x > t->m_data)
        remove_rec(t->m_right, x);
    else if(t->m_right != NULL && t-> m_left != NULL)
    {
        t->m_data = findMax_rec(t->m_right);
        remove_rec(t->m_right,t->m_data);
        
    }
    else
    {
        tmp = t;
        t = (t->m_left != NULL) ? t->m_left : t->m_right;
        delete tmp;
        return true;
    }
   
    return true;
}

// Purpose: Removes an element from the tree
// Parameters: x, the element to remove
// Postconditions: the tree does not contains x
template <typename T>
void MyBSTree<T>::remove(const T& x)
{
    if (remove_rec(m_root, x) )
        m_size--;
}

template <typename T>
void MyBSTree<T>::PreOrder_rec(BSTreeNode<T> *t) const
{
    cout << t->m_data << endl;
    if(t->m_left != NULL) PreOrder_rec(t->m_left);
    if(t->m_right != NULL)PreOrder_rec(t->m_right);

}

// Purpose: Prints the Tree in Pre-Order
template <typename T>
void MyBSTree<T>::printPreOrder() const
{
    PreOrder_rec(m_root);
}

template <typename T>
void MyBSTree<T>::PostOrder_rec(BSTreeNode<T> *t) const
{
    if(t->m_left != NULL) PostOrder_rec(t->m_left);
    if(t->m_right != NULL)PostOrder_rec(t->m_right);
    cout << t->m_data << endl;
}

// Purpose: Prints the Tree in Pre-Order
template <typename T>
void MyBSTree<T>::printPostOrder() const
{
    PostOrder_rec(m_root);
}

