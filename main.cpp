//
//  main.cpp
//  ExpressionEvaluator
//
//  Created by Sandu Gherbe on 17/06/2019.
//  Copyright © 2019 Sandu Gherbe. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include <string>
#include "operationnode.h"
#include "expressionevaluator.h"
#include "exceptions.h"
#include <memory>


int main(int argc, char** argv) {
  try {
    std::string expression;
    std::cout << "Please, enter the expression to evaluate. Supported operators are '+', '-', '/', '*': ";
    std::getline (std::cin,expression);
    ExpressionEvaluator<int> b;
    std::shared_ptr<OperationNode<int>> root = b.parse(expression);
    auto result = root->value();
    std::cout << " result = " << result << std::endl;
  } catch (InvalidExpressionException e) {
      std::cout << e.what() << std::endl;
  } catch (InvalidNumberException e) {
      std::cout << e.what() << std::endl;
  } catch (std::exception e) {
      std::cout << e.what() << std::endl;
  }
  std::cout << "Exiting..." << std::endl;
return 0;
  
}

