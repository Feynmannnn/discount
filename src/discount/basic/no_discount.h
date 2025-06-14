#pragma once
#include "src/discount/discount_strategy.h"

class NoDiscount : public DiscountStrategy {
public:
  double Calculate(double price, UserContext user_context) const override {
    return price;
  }
};
