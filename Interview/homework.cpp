/*************************************************************************
	> File Name: homework.cpp
	> Author:yangkun 
	> Mail:yangkungetit@163.com 
	> Created Time: Mon 05 Feb 2018 08:20:06 PM CST
 ************************************************************************/
#pragma once
#include <vector>
#include <queue>
#include <stack>

//template<class T>
//struct TreeNode
//{
//  T _data;
//  vector<TreeNode<T>*> _subs;
//};

template<class T>
struct BinaryTreeNode
{
    T _data;
    BinaryTreeNode<T>* _left;
    BinaryTreeNode<T>* _right;

    BinaryTreeNode(const T& x)
        :_data(x)
        ,_left(NULL)
        ,_right(NULL)
    {}
};

template<class T>
class BinaryTree
{
    typedef BinaryTreeNode<T> Node;
public:
    BinaryTree(T* a, size_t n, const T& invalid)
    {
        size_t index = 0;
        _root = _CreareTree(a, n, invalid, index);
    }

    Node* CopyTree(Node* root)
    {
        if (root == NULL)
        {
            return NULL;
        }

        Node* newRoot = new Node(root->_data);
        newRoot->_left = CopyTree(root->_left);
        newRoot->_right = CopyTree(root->_right);

        return newRoot;
    }

    BinaryTree(const BinaryTree<T>& t)
    {
        _root = CopyTree(t._root);
    }

    //BinaryTree<T>& operator=(const  BinaryTree<T>& t)
    //{
    //  if (this != &t)
    //  {
    //      Destory(_root);
    //      _root = CopyTree(t._root);
    //  }

    //  return *this;
    //}

    // t2(t1)
    BinaryTree<T>& operator=(BinaryTree<T> t)
    {
        swap(_root, t._root);
        return *this;
    }

    ~BinaryTree()
    {
        Destory(_root);
        _root = NULL;
    }

    void Destory(Node* root)
    {
        if (root == NULL)
            return;

        Destory(root->_left);
        Destory(root->_right);

        delete root;
    }

    // ǰ��
    Node* _CreareTree(T* a, size_t n, const T& invalid, size_t& index)
    {
        // ��+������+������
        Node* root = NULL;
        if(a[index] != invalid)
        {
            root = new Node(a[index]);
            root->_left = _CreareTree(a, n, invalid, ++index);
            root->_right = _CreareTree(a, n, invalid, ++index);
        }

        return root;
    }

    void PrevOrder()
    {
        _PrevOrder(_root);
        cout<<endl;
    }

    void _PrevOrder(Node* root)
    {
        if(root == NULL)
            return;

        cout<<root->_data<<"  ";
        _PrevOrder(root->_left);
        _PrevOrder(root->_right);
    }

    void InOrder()
    {
        _InOrder(_root);
        cout<<endl;
    }

    void _InOrder(Node* root)
    {
        if(root == NULL)
            return;

        _InOrder(root->_left);
        cout<<root->_data<<"  ";
        _InOrder(root->_right);
    }

    void PostOrder();

    // ������
    /*int Size()
    {
        return _Size(_root);
    }

    size_t _Size(Node* root)
    {
        if(root == NULL)
            return 0;

        return _Size(root->_left) + _Size(root->_right) + 1;
    }*/

    // ����
    int Size()
    {
        size_t size = 0;
        _Size(_root, size);
        return size;
    }

    void _Size(Node* root, size_t& size)
    {
        if(root == NULL) return;

        _Size(root->_left, size);
        ++size;
        _Size(root->_right, size);
    }

    /*size_t LeafSize()
    {
        size_t size = 0;
        _LeafSize(_root, size);
        return size;
    }

    void _LeafSize(Node* root, size_t& size)
    {
        if (root == NULL)
            return;

        if (root->_left == NULL && root->_right == NULL)
            ++size;

        _LeafSize(root->_left, size);
        _LeafSize(root->_right, size);
    }*/

    size_t LeafSize()
    {
        return _LeafSize(_root);
    }

    size_t _LeafSize(Node* root)
    {
        if (root == NULL)
            return 0;

        if (root->_left == NULL
            && root->_right == NULL)
        {
            return 1;
        }

        return _LeafSize(root->_left) + _LeafSize(root->_right);
    }

    size_t Height()
    {
        return _Height(_root);
    }

    size_t _Height(Node* root)
    {
        if (root == NULL)
            return 0;

        size_t leftHeight = _Height(root->_left);
        size_t rightHeight = _Height(root->_right);

        return  leftHeight > rightHeight
            ? leftHeight+1 : rightHeight+1;
    }

    size_t GetKLevel(size_t k)
    {
        return _GetKLevel(_root, k);
    }

    size_t _GetKLevel(Node* root, size_t k)
    {
        if (root == NULL)
            return 0;

        if (k == 1)
            return 1;

        return _GetKLevel(root->_left, k-1) + _GetKLevel(root->_right, k-1);
    }

    void LevelOrder()
    {
        queue<Node*> q;
        if(_root)
            q.push(_root);

        while (!q.empty())
        {
            Node* front = q.front();
            cout<<front->_data<<" ";
            q.pop();

            if (front->_left)
                q.push(front->_left);

            if (front->_right)
                q.push(front->_right);
        }

        cout<<endl;
    }

    /*bool IsCompleteTree()
    {
        queue<Node*> q;
        if (_root)
            q.push(_root);

        while (!q.empty())
        {
            Node* front = q.front();
            q.pop();
            if (front)
            {
                q.push(front->_left);
                q.push(front->_right);
            }
            else
            {
                break;
            }
        }
        
        while (!q.empty())
        {
            Node* front = q.front();
            q.pop();
            if (front)
                return false;
        }

        return true;
    }*/

    bool IsCompleteTree()
    {
        queue<Node*> q;
        if (_root)
            q.push(_root);

        bool flag = true;

        while (!q.empty())
        {
            Node* front = q.front();
            q.pop();
            if (front->_left)
            {
                if (flag == false)
                    return false;

                q.push(front->_left);
            }
            else
            {
                flag = false;
            }

            if (front->_right)
            {
                if (flag == false)
                    return false;

                q.push(front->_right);
            }
            else
            {
                flag = false;
            }
        }

        return true;
    }

    Node* Find(const T& x)
    {
        return _Find(_root, x);
    }

    Node* _Find(Node* root, const T& x)
    {
        if (root == NULL)
            return NULL;

        if (root->_data == x)
            return root;

        Node* ret1 = _Find(root->_left, x);
        if (ret1)
            return ret1;

        Node* ret2 = _Find(root->_right, x);
        if (ret2)
            return ret2;

        return NULL;
    }

    void PrevOrderNonR()
    {
        Node* cur = _root;
        stack<Node*> s;
        
        while (cur || !s.empty())
        {
            while (cur)
            {
                cout<<cur->_data<<"  ";
                s.push(cur);
                cur = cur->_left;
            }

            Node* top = s.top();
            s.pop();

            // ������
            cur = top->_right;
        }
        cout<<endl;
    }

    void InOrderNonR()
    {
        Node* cur = _root;
        stack<Node*> s;
        while (cur || !s.empty())
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->_left;
            }

            Node* top = s.top();
            cout<<top->_data<<"  ";
            s.pop();

            cur = top->_right;
        }
        cout<<endl;
    }

    void PostOrderNonR()
    {
        Node* cur = _root;
        Node* prev = NULL;
        stack<Node*> s;

        while (cur || !s.empty())
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->_left;
            }

            Node* top = s.top();
            if (top->_right == NULL || top->_right == prev)
            {
                cout<<top->_data<<"  ";
                s.pop();
                prev = top;
            }
            else
            {
                cur = top->_right;
            }
        }

        cout<<endl;
    }

protected:
    Node* _root;
};

void TestBinaryTree()
{
    //int array[] = {1, 2, 3, '#', '#', 4, '#','#', 5, 6,'#' ,'#' ,'#' };
    int array[] = {1, 2, 3, '#', '#', 4, 40, '#' , '#' , '#', 5, 6,'#' ,'#' ,'#' };
    BinaryTree<int> t(array, sizeof(array)/sizeof(int), '#');
    t.PrevOrder();
    t.PrevOrderNonR();
    t.InOrder();
    t.InOrderNonR();
    t.PostOrderNonR();
    t.LevelOrder();
    cout<<"Size?"<<t.Size()<<endl;
    cout<<"Leaf Size?"<<t.LeafSize()<<endl;
    cout<<"Height?"<<t.Height()<<endl;
    cout<<"IsCompleteTree?"<<t.IsCompleteTree()<<endl;
    cout<<"K Level Size?"<<t.GetKLevel(4)<<endl;

    BinaryTree<int> t1(t);
    t1.PrevOrderNonR();
}
