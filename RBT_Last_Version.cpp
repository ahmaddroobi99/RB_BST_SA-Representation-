#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

//
//  BSTree.h
//  DataAlog
//
//  Created by Sam on 3/31/14.
//  Copyright (c) 2014 Sam. All rights reserved.
//
// ahmad droobi @@ Ataa shaqoor (c) 2021

#ifndef __DataAlog__BSTree__
#define __DataAlog__BSTree__

#include <iostream>
#include <stack>

#define SAT_DATA_SIZE 8

#define black 0
#define red 1
using namespace std;
typedef struct Data
{
    int key;
    int satellite[SAT_DATA_SIZE];

} Data;

class BSTree // virtual base class
{

public:
    // returns whether the tree contains the following value or not
    virtual bool Search(int key) = 0;

    // Adds a single data item to the tree.  If there is already an
    // item in the tree that compares equal to the item being inserted,
    // it is "overwritten" by the new item.

    virtual void Add(int key, int n) = 0;

    // export the content of the tree as an ordered array
    virtual void BSTreeSort(int max) = 0;

    // return the information of the node with the minimum key
    virtual int GetMin() = 0;

    // return the information of the node with the maximum key
    virtual int GetMax() = 0;
};

#endif

int j = 0;
struct Node
{

    int data = -1;
    int parent = -1;
    int left = -1;
    int right = -1;
    bool color = 1;
};
class RBTreeSA : public BSTree
{

public:
    Node *a;
    int s = 0;

    RBTreeSA();
    RBTreeSA(int n)
    {
        a = new Node[n];
        s = n;
    }

    bool flag = true;
    void Add(int n, int D) override
    {
        int node_index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i].data == -1)
            {
                node_index = i;
                a[i].data = D;
                break;
            }
        }
        if (node_index == 0)
        {
            a[node_index].color = black;
            return;
        }
        else
        {
            int here = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[here].left == -1 && a[here].right == -1)
                {
                    if (a[here].data < D)
                    {
                        a[here].right = node_index;
                        a[node_index].parent = here;
                        fix_violation(node_index);
                        return;
                    }
                    else
                    {
                        a[here].left = node_index;
                        a[node_index].parent = here;
                        fix_violation(node_index);
                        return;
                    }
                }
                else if (a[here].left != -1 || a[here].right != -1)
                {
                    if (a[here].left != -1 && a[here].right == -1)
                    {
                        if (a[here].data < D)
                        {
                            a[here].right = node_index;
                            a[node_index].parent = here;
                            fix_violation(node_index);
                            return;
                        }
                        else
                        {
                            here = a[here].left;
                            continue;
                        }
                    }
                    else if (a[here].left == -1 && a[here].right != -1)
                    {
                        if (a[here].data < D)
                        {
                            here = a[here].right;
                            continue;
                        }
                        else
                        {
                            a[here].left = node_index;
                            a[node_index].parent = here;
                            fix_violation(node_index);
                            return;
                        }
                    }
                    else
                    {
                        if (a[here].data < D)
                        {
                            here = a[here].right;
                            continue;
                        }
                        else
                        {
                            here = a[here].left;
                            continue;
                        }
                    }
                }
            }
        }
    }

    int leftRotate(int key)
    {
        Node *y = &a[a[key].right];
        int y_index = a[key].right;

        a[key].right = y->left;

        if (y->left != -1)
        {
            a[y->left].parent = key;
        }
        if (y_index != -1)
        {
            y->parent = a[key].parent;
        }
        if (a[key].parent == -1)
        {
            a[y->left].parent = key;
            a[y->right].parent = key;
            a[a[key].left].parent = y_index;
            a[a[key].right].parent = y_index;
            Node temp;
            temp.data = a[key].data;
            temp.color = a[key].color;
            temp.left = a[key].left;
            temp.right = a[key].right;
            temp.parent = a[key].parent;

            a[key].data = y->data;
            a[key].color = y->color;
            a[key].left = y->left;
            a[key].right = y->right;
            a[key].parent = y->parent;

            y->data = temp.data;
            y->color = temp.color;
            y->left = temp.left;
            y->right = temp.right;
            y->parent = temp.parent;
            key = y_index;
            y = &a[0];
            y_index = 0;
        }
        else if (key == a[a[key].parent].left)
        {
            a[a[key].parent].left = y_index;
        }

        else
        {

            a[a[key].parent].right = y_index;
        }

        y->left = key;
        if (key != -1)
            a[key].parent = y_index;
        return key;
    }

    int rightRotate(int key)
    {
        Node *y = &a[a[key].left];
        int y_index = a[key].left;
        a[key].left = y->right;

        if (y->right != -1)
        {
            a[y->right].parent = key;
        }
        if (y_index != -1)
        {
            y->parent = a[key].parent;
        }
        if (a[key].parent == -1)
        {
            a[y->left].parent = key;
            a[y->right].parent = key;
            a[a[key].left].parent = y_index;
            a[a[key].right].parent = y_index;
            Node temp;
            temp.data = a[key].data;
            temp.color = a[key].color;
            temp.left = a[key].left;
            temp.right = a[key].right;
            temp.parent = a[key].parent;

            a[key].data = y->data;
            a[key].color = y->color;
            a[key].left = y->left;
            a[key].right = y->right;
            a[key].parent = y->parent;

            y->data = temp.data;
            y->color = temp.color;
            y->left = temp.left;
            y->right = temp.right;
            y->parent = temp.parent;
            key = y_index;
            y = &a[0];
            y_index = 0;
        }
        else if (key == a[a[key].parent].right)
        {
            a[a[key].parent].right = y_index;
        }

        else
        {

            a[a[key].parent].left = y_index;
        }

        y->right = key;
        if (key != -1)
            a[key].parent = y_index;
        return key;
    }

    void fix_violation(int key)
    {
        int parent = a[key].parent, grand = a[parent].parent;

        //cout << "key: "<< parent<< "      color: " << a[parent].color << endl;

        while (key != 0 && a[parent].color == red)
        {
            if (parent == a[grand].left)
            {
                int uncle = a[grand].right;

                if (uncle != -1 && a[uncle].color == red)
                {
                    a[parent].color = black;
                    a[uncle].color = black;
                    a[grand].color = red;
                }
                else
                {

                    if (key == a[parent].right)
                    {
                        key = parent;
                        leftRotate(key);
                        parent = a[key].parent;
                        grand = a[parent].parent;
                    }
                    swap(a[parent].color, a[grand].color);
                    rightRotate(grand);
                }
                key = grand;
                parent = a[key].parent;
                grand = a[parent].parent;
            }
            else
            {
                int uncle = a[grand].left;
                if (uncle != -1 && a[uncle].color == red)
                {
                    a[parent].color = black;
                    a[uncle].color = black;
                    a[grand].color = red;
                }
                else
                {
                    if (key == a[parent].left)
                    {
                        key = parent;
                        rightRotate(key);
                        parent = a[key].parent;
                        grand = a[parent].parent;
                    }
                    
                    swap(a[parent].color, a[grand].color);
                    leftRotate(grand);
                }
                
                key = grand;
                parent = a[key].parent;
                grand = a[parent].parent;
            }
        }

        a[0].color = black;
        

    }

    int GetMax() override
    {
        if (a[0].data == -1)
            return -1;
        else
        {
            int here = 0;
            while (a[here].right != -1)
            {
                here = a[here].right;
            }

            return a[here].data;
        }
    }

    int GetMin() override
    {
        if (a[0].data == -1)
            return -1;
        else
        {
            int here = 0;
            while (a[here].left != -1)
            {
                here = a[here].left;
            }

            return a[here].data;
        }
    }

    bool Search(int key) override
    {
        for (int i = 0; i < s; i++)
        {
            if (a[i].data == key)
                return true;
        }
        return false;
    }

    void BSTreeSort(int max) override
    {
        stack<int> sta;
        stack<int> index;

        int curr = 0;
        while (curr != -1 || sta.empty() == false)
        {

            while (curr != -1)
            {

                sta.push(a[curr].data);
                index.push(curr);
                curr = a[curr].left;
            }

            if (sta.top() == max)
            {
                cout << sta.top() << "]";
            }
            else
            {
                cout << sta.top() << ",";
            }
            curr = index.top();
            sta.pop();
            index.pop();

            curr = a[curr].right;
        }
    }
};

int main()
{

    int insert_num = 0, number_of_instructions = 0;

    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            cin >> insert_num;
        }
        else
        {
            cin >> number_of_instructions;
        }
    }

    RBTreeSA s(insert_num);

    string str;
    string order;
    string value;
    int val = 0;
    string domy;
    for (int i = 0; i < number_of_instructions; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 1)
            {
                cin >> order;
                continue;
            }
            else if (j == 3)
            {
                scanf("%d", &val);
                continue;
            }
            cin >> domy;
        }

        if (order == "i")
        {
            s.Add(insert_num, val);
        }
        else if (order == "s")
        {
            int flag = s.Search(val);
            if (flag)
            {
                cout << "[Yes] " << endl;
            }
            else
            {
                cout << "[No] " << endl;
            }
        }
    }
    int max = s.GetMax();
    cout << "[" << max << "] " << endl;
    cout << "[" << s.GetMin() << "] " << endl;
    cout << "[";
    s.BSTreeSort(max);

    return 0;
}
