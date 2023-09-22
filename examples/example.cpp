#include "ntree.hpp"

#include <iostream>
#include <numeric>

int main()
{
    
    //Create root of ntree with value 0
    ntree_node<int> root{0};
    /*
    Add child 1 to root                 0--1
    */
    root.add(1);
    /*                                    /--1 
    Add another child to root           0-
                                          \--2
    */
    root.add(2);
    /*                                    /--1 
    Add child 2 child 2                 0-
                                          \--2--3
    */
    root[1].add(3);
    /*
                                                /--4
                                           /--1-
    Add some more children               0-        /--5
                                           \--2--3- --7
                                                   \--3
    */
    root[0].add(4);
    root[1][0].add(5);
    root[1][0].add(7);
    root[1][0].add(3);
    //Get value of tree or subtree
    std::cout << *root << std::endl;            // out 0
    std::cout << *root[1][0][2] << std::endl;   // out 3
    //Print all tree using range-based for
    for(auto&& it : root)
    {
        std::cout << it << std::endl;
    }
    //Print root[1] subtree using range-based for
    for(auto&& it : root[1])
    {
        std::cout << it << std::endl;
    }
    //calculate sum of all tree elements using std::accumulate
    int sum = std::accumulate(root.begin(), root.end(), 0);
    std::cout << sum << std::endl;         //ntree_node<T>::end() is valid for any ntree_node<T> object, 
                                                                                    //because it is a ntree_node<T>::recursive_iterator{ nullptr }
    //calculate sum of tree[1] subtree elements using std::accumulate
    sum = std::accumulate(root[1].begin(), root[1].end(), 0);
    std::cout << sum << std::endl;   //unstead of root[1].end() you can use root.end(), or any 
                                                                                    //ntree_node<int>::recursive_iterator{ nullptr }

    return 0;
}