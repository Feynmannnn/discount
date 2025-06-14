#pragma once
#include "src/user/user_context.h"

class DiscountStrategy {
public:
  virtual double Calculate(double price, UserContext user_context) const = 0;
  virtual ~DiscountStrategy() = default;
};
