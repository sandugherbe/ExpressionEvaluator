//
//  operationnode.h
//  ExpressionEvaluator
//
//  Created by Sandu Gherbe on 17/06/2019.
//  Copyright © 2019 Sandu Gherbe. All rights reserved.
//

#ifndef operationnode_h
#define operationnode_h

#include "treenode.h"
#include <memory>
#include <iostream>

/**
 * @class OperationNode
 * @brief Type of TreeNode which wraps a mathematical expression
 */
template <typename T>
class OperationNode: public TreeNode<T> {
protected:
  char operator_;
  std::shared_ptr<TreeNode<T>> left;
  std::shared_ptr<TreeNode<T>> right;
  void traverseNodes(T &leftVal, T &rightVal);

public:
  OperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r);
  virtual T value() = 0;
  virtual ~OperationNode() {}
};

template <typename T>
OperationNode<T>::OperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r) : operator_(op), left(l), right(r) {
}

/**
 * @brief Traverses the subtrees of the current node.
 * @param leftVal The value of the left tree.
 * @param rightVal The value of the right tree.
 */
template <typename T>
void OperationNode<T>::traverseNodes(T &leftVal, T &rightVal) {
  std::cout << "op: " << operator_ << std::endl;
  leftVal = left->value();
  std::cout << "num: " << leftVal << std::endl;
  rightVal = right->value();
  std::cout << "num: " << rightVal << std::endl;
}

/**
 * @class PlusOperationNode
 * @brief Wraps an addition expression
 */
template <typename T>
class PlusOperationNode: public OperationNode<T> {
public:
  PlusOperationNode<T>(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r);
  virtual T value();
};

template <typename T>
PlusOperationNode<T>::PlusOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r) : OperationNode<T>(op, l, r) {
}

template <typename T>
T PlusOperationNode<T>::value() {
  T leftVal = 0;
  T rightVal = 0;
  this->traverseNodes(leftVal, rightVal);
  return leftVal + rightVal;
}

/**
 * @class MinusOperationNode
 * @brief Wraps a subtraction expression
 */
template <typename T>
class MinusOperationNode: public OperationNode<T> {
public:
  MinusOperationNode<T>(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r);
  virtual T value();
};

template <typename T>
MinusOperationNode<T>::MinusOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r) : OperationNode<T>(op, l, r) {
}

template <typename T>
T MinusOperationNode<T>::value() {
  T leftVal;
  T rightVal;
  this->traverseNodes(leftVal, rightVal);
  return leftVal - rightVal;
}

/**
 * @class MulOperationNode
 * @brief Wraps a multiplication expression
 */
template <typename T>
class MulOperationNode: public OperationNode<T> {
public:
  MulOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r);
  virtual T value();
};

template <typename T>
MulOperationNode<T>::MulOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r) : OperationNode<T>(op, l, r) {
}

template <typename T>
T MulOperationNode<T>::value() {
  T leftVal = 0;
  T rightVal = 0;
  this->traverseNodes(leftVal, rightVal);
  return leftVal * rightVal;
}

/**
 * @class DivOperationNode
 * @brief Wraps a division expression
 */
template <typename T>
class DivOperationNode: public OperationNode<T> {
public:
  DivOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r);
  
  virtual T value();
};

template <typename T>
DivOperationNode<T>::DivOperationNode(char op, std::shared_ptr<TreeNode<T>> l, std::shared_ptr<TreeNode<T>> r) : OperationNode<T>(op, l, r) {
}

template <typename T>
T DivOperationNode<T>::value() {
  T leftVal = 0;
  T rightVal = 0;
  this->traverseNodes(leftVal, rightVal);
  return leftVal / rightVal;
}

#endif /* operationnode_h */
