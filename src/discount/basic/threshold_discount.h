#pragma once
#include "src/discount/discount_strategy.h"

class ThresholdDiscount : public DiscountStrategy {
public:
  explicit ThresholdDiscount(double threshold, double reduction)
      : threshold_(threshold), reduction_(reduction) {}

  double Calculate(double price, UserContext user_context) const override {
    return price >= threshold_ ? price - reduction_ : price;
  }

private:
  double threshold_;
  double reduction_;
};
