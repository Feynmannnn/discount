#pragma once
#include "src/discount/discount_strategy.h"

#include <unordered_map>

class UserLevelDiscount : public DiscountStrategy {
public:
  explicit UserLevelDiscount(
      std::unordered_map<UserLevel, double> user_level_discount_map)
      : user_level_discount_map_(user_level_discount_map) {}

  double Calculate(double price, UserContext user_context) const override {
    return price * user_level_discount_map_.at(user_context.user_level());
  }

private:
  std::unordered_map<UserLevel, double> user_level_discount_map_;
};
