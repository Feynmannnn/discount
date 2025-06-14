#pragma once

#include "src/discount/discount_strategy.h"

#include <memory>

class DiscountContext {
public:
  void
  SetDiscountStrategy(std::shared_ptr<DiscountStrategy> discount_strategy) {
    discount_strategy_ = discount_strategy;
  }

  double Apply(double price, UserContext user_context) const {
    return discount_strategy_
               ? discount_strategy_->Calculate(price, user_context)
               : price;
  }

private:
  std::shared_ptr<DiscountStrategy> discount_strategy_;
};
