//
//  expressionevaluator.h
//  ExpressionEvaluator
//
//  Created by Sandu Gherbe on 17/06/2019.
//  Copyright © 2019 Sandu Gherbe. All rights reserved.
//

#ifndef expressionbuilder_h
#define expressionbuilder_h

#include "operationnode.h"
#include "treenode.h"
#include <stack>
#include <sstream>
#include "exceptions.h"

enum class Precedence: std::uint8_t {
  Parantheses, AdditionMinus, MultiplicationDivision
};

/**
 * @class expressionevaluator
 * @brief Parses input and builds the expression tree
 */
template <typename T>
class ExpressionEvaluator {
private:
  std::stack<char> operatorStack;
  std::stack<std::shared_ptr<TreeNode<T> >> operandStack;
  void processOperator(char op);
  void processRightParenthesis();
  void build();
  Precedence precedence(char op);
public:
  std::shared_ptr<OperationNode<T>> parse(const std::string& istr) noexcept(false);
  
};

/**
 * @brief Returns the precedence of an operator
 * @param op The operator being considered.
 * @return The precedence of the operator.
 */
template <typename T>
Precedence ExpressionEvaluator<T>::precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return Precedence::AdditionMinus;
    case '/':
    case '*':
      return Precedence::MultiplicationDivision;
    default:
      return Precedence::Parantheses;
  }
}

/**
 * @brief Parses a mathematical expression
 * @param input The string to parse
 * @return A node in the tree.
 */
template <typename T>
std::shared_ptr<OperationNode<T>> ExpressionEvaluator<T>::parse(const std::string& input) noexcept(false) {
  std::stringstream strngstr(input);
  char item;
  while (strngstr >> item) {
    switch (item) {
      case '+':
      case '-':
      case '*':
      case '/':
        processOperator(item);
        break;
      case ')':
        processRightParenthesis();
        break;
      case '(':
        operatorStack.push(item);
        break;
      default:
        if (isdigit(item)) {
          strngstr.putback(item);
          int number;
          strngstr >> number;
          std::shared_ptr<NumericNode<T>> newNode = std::make_shared<NumericNode<T>>(number);
          operandStack.push(newNode);
          continue;
        } else {
          throw InvalidNumberException();
        }
        
    }
  }

  while (!operatorStack.empty()) {
    build();
    operatorStack.pop();
  }
  
  if (operandStack.size() != 1) {
    throw InvalidExpressionException();
  }
  std::shared_ptr<TreeNode<T>> p = operandStack.top();
  return std::static_pointer_cast<OperationNode<T>> (p);
}

/**
 * @brief Processes a given operator
 * @param op The operator to process
 */

template <typename T>
void ExpressionEvaluator<T>::processOperator(char op) {
  Precedence opPrecedence = precedence(op);
  while ((!operatorStack.empty()) && (opPrecedence <= precedence(operatorStack.top())))  {
    build();
    operatorStack.pop();
  }
  operatorStack.push(op);
}

/**
 * @brief Processes the right paranthesis operator
 */
template <typename T>
void ExpressionEvaluator<T>::processRightParenthesis() {
  while (!operatorStack.empty() && operatorStack.top() != '(') {
    build();
    operatorStack.pop();
  }
  operatorStack.pop();
}

/**
 * @brief Builds a new node
 */
template <typename T>
void ExpressionEvaluator<T>::build() {
  if (operandStack.size() >=2 ) {
    std::shared_ptr<TreeNode<T>> right = operandStack.top();
    operandStack.pop();
    std::shared_ptr<TreeNode<T>> left = operandStack.top();
    operandStack.pop();
    std::shared_ptr<OperationNode<T>> p = nullptr;
    switch (operatorStack.top()) {
        case '+':
          p =  std::make_shared<PlusOperationNode<T>>(operatorStack.top(), left, right);
          break;
        case '-':
          p = std::make_shared<MinusOperationNode<T>>(operatorStack.top(), left, right);
          break;
        case '*':
          p = std::make_shared<MulOperationNode<T>>(operatorStack.top(), left, right);
          break;
        case '/':
          p = std::make_shared<DivOperationNode<T>>(operatorStack.top(), left, right);
          break;
      }
    
    operandStack.push(p);
  } else {
    throw InvalidExpressionException();
  }
}

#endif /* expressionevaluator */
