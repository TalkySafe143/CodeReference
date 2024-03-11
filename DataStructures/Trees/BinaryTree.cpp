#ifndef ARBBIN_ARBBIN_H
#define ARBBIN_ARBBIN_H
#include <bits/stdc++.h>

template <class T>
class BinaryNode
{
private:
    T info;
    BinaryNode<T> *left;
    BinaryNode<T> *right;
public:
    BinaryNode()
    {
        this->left = nullptr;
        this->right = nullptr;
    }

    BinaryNode(T m_info )
    {
        this->info = m_info;
        this->left = nullptr;
        this->right = nullptr;
    }

    BinaryNode(T m_info, BinaryNode<T> m_left  , BinaryNode<T> m_right  )
    {
        this->info = m_info;
        this->left = m_left;
        this->right = m_right;
    }

    T getInfo()
    {
        return this->info;
    }

    BinaryNode<T> * getLeft()
    {
        return this->left;
    }

    BinaryNode<T> * getRight()
    {
        return this->right;
    }


    // Get member by reference
    void getLeft(BinaryNode<T> *&i)
    {
        i = this->left;
    }

    void getRight(BinaryNode<T> *&d)
    {
        d = this->right;
    }

    void setInfo(T val)
    {
        BinaryNode<T>::info = val;
    }

    void setLeft(BinaryNode<T> *val)
    {
        this->left  = val;
    }

    void setRight(BinaryNode<T> *val)
    {
        this->right = val;
    }
    void CopyTree(BinaryNode<T> *TreePtr, BinaryNode<T>*&NewTreePtr)
    {
        if (TreePtr != 0)
        {
            NewTreePtr = new NodoB<T>(TreePtr->info);
            CopyTree(TreePtr->left,NewTreePtr->left);
            CopyTree(TreePtr->right,NewTreePtr->right);
        }
        else
            NewTreePtr = 0;
    }
};


template <class T>
class BinaryTree
{
    private:
        BinaryNode<T> *root;
    public:
        ArbBin() {
            root = nullptr;
        }
        ArbBin(BinaryNode<T>* NodePtr) {
            root = NodePtr;
        }
        explicit ArbBin(T info){
            root = new BinaryNode<T>(info);
        }
        ArbBin(const T &info, const ArbBin<T> &left, const ArbBin<T> &right)
        {
            root = new BinaryNode<T>(info, left.root, right.root);
        }

        bool operator <(ArbBin<T>& a) {
            return this->GetInfo() < a.GetInfo();
        }

        bool isEmpty() const
        {
            return root == nullptr;
        }

        T getInfo() const
        {
            if (root != nullptr) {
                return root->getInfo();
            } else {
                throw std::runtime_error("El arbol está vacio");
            }
        }

        BinaryTree<T> *getLeftArbBin()
        {
            if (root != nullptr) {
                return new BinaryTree<T>(root->getLeft());
            } else {
                throw std::runtime_error("El arbol esta vacio");
            }
        }

        BinaryTree<T> *getRightArbBin()
        {
            if (root != nullptr) {
                return new BinaryTree<T>(root->getRight());
            } else {
                throw std::runtime_error("El arbol esta vacio");
            }
        }

        void setInfo(const T info)
        {
            root->Setinfo(info);
        }


        void addRightTree(const T info, bool &ok)
        {
            if (root != nullptr) {
                BinaryNode<T> *nuevo = new BinaryNode<T>(info);
                root->setLeft(nuevo);
                ok = true;
            } else {
                ok = false;
            }
        }

        void addLeftTree(const T info, bool &ok)
        {
            if (root != nullptr) {
                BinaryNode<T> *nuevo = new BinaryNode<T>(info);
                root->setLeft(nuevo);
                ok = true;
            } else {
                ok = false;
            }
        }


        void deleteLeftTree(ArbBin<T>& subarbol, bool &ok)
        {
            if (root != nullptr) {
                subarbol.root = root->getLeft();
                root->setLeft(nullptr);
                ok = true;
            } else {
                ok = false;
            }
        }

        void deleteRightTree(ArbBin<T>& subarbol, bool &ok)
        {
            if (root != nullptr) {
                subarbol.root = root->getRight();
                root->setRight(nullptr);
                ok = true;
            } else {
                ok = false;
            }
        }

        void allocateLeftTree(BinaryTree<T>& subarbol, bool &ok)
        {
            if (root != nullptr && subarbol.root != nullptr) {
                root->setLeft(subarbol.root);
                subarbol.root = nullptr;
                ok = true;
            } else {
                ok = false;
            }
        }

        void allocateRightTree(BinaryTree<T>& subarbol, bool &ok)
        {
            if (root != nullptr && subarbol.root != nullptr) {
                root->setRight(subarbol.root);
                subarbol.root = nullptr;
                ok = true;
            } else {
                ok = false;
            }
        }

    protected:

        void CopyTree(BinaryNode<T> *TreePtr, BinaryNode<T> *& NewTreePtr) const
        {
            if (TreePtr != nullptr) {
                NewTreePtr = new BinaryNode<T>(TreePtr->getInfo());
                CopyTree(TreePtr->getLeft(), NewTreePtr->getLeft());
                CopyTree(TreePtr->getRight(), NewTreePtr->getRight());
            } else {
                NewTreePtr = nullptr;
            }
        }

        void preorderTraversal(BinaryNode<T>* TreePtr, void (*Visit)(T))
        {
            if (TreePtr != nullptr){
                Visit(TreePtr->getInfo());
                preorderTraversal(TreePtr->getLeft(), Visit);
                preorderTraversal(TreePtr->getRight(), Visit);
            }
        }
        void inorderTraversal(BinaryNode<T>* TreePtr, void (*Visit)(T))
        {
            if (TreePtr != nullptr){
                inorderTraversal(TreePtr->getLeft());
                Visit(TreePtr->getInfo());
                inorderTraversal(TreePtr->getRight());
            }
        }

        void posorderTraversal(BinaryNode<T>* TreePtr, void (*Visit)(T))
        {
            if (TreePtr != nullptr) {
                posorderTraversal(TreePtr->getLeft());
                posorderTraversal(TreePtr->getRight());
                Visit(TreePtr->getInfo());
            }
        }
};

#endif
