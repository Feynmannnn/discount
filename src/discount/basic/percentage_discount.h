#pragma once
#include "src/discount/discount_strategy.h"

class PercentageDiscount : public DiscountStrategy {
public:
  explicit PercentageDiscount(double rate) : rate_(rate) {}

  double Calculate(double price, UserContext user_context) const override {
    return price * rate_;
  }

private:
  double rate_;
};
