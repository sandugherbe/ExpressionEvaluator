//
//  treenode.h
//  ExpressionEvaluator
//
//  Created by Sandu Gherbe on 17/06/2019.
//  Copyright © 2019 Sandu Gherbe. All rights reserved.
//

#ifndef treenode_h
#define treenode_h

/**
 * @class TreeNode
 * @brief Interface for a tree node.
 */

template <typename T>
class TreeNode {
public:
  virtual T value() = 0;
};

/**
 * @class NumericNode
 * @brief Type of TreeNode which wraps a number
 */

template <typename T>
class NumericNode: public TreeNode<T> {
private:
  T number;
public:
  NumericNode(T val);
  virtual T value();
};

/**
 * @brief Constructor
 * @param val The number.
 */
template <typename T>
NumericNode<T>::NumericNode(T val) : number(val) {
}

/**
 * @brief Returns the value of the number
 * @return The value of the number wrapped.
 */
template <typename T>
T NumericNode<T>::value() {
  return number;
}


#endif /* treenode_h */
