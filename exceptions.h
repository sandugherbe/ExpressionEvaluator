//
//  exceptions.h
//  ExpressionEvaluator
//
//  Created by Sandu Gherbe on 18/06/2019.
//  Copyright © 2019 Sandu Gherbe. All rights reserved.
//

#ifndef exceptions_h
#define exceptions_h

#include <exception>

/**
 * @class InvalidExpressionException
 * @brief It is thrown when the input is an invalid expression
 */
class InvalidExpressionException: public std::exception {
public:
  const char* what() const noexcept(true) {
    return "The expression is not valid!";
  }
};

/**
 * @class InvalidNumberException
 * @brief It is thrown when the input is an contains an invalid number
 */
class InvalidNumberException: public std::exception {
public:
  const char* what() const noexcept(true) {
    return "The number is not valid!";
  }
};


#endif /* exceptions_h */
