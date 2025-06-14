#pragma once
#include "src/discount/discount_strategy.h"

#include <memory>
#include <vector>

class CompositeDiscount : public DiscountStrategy {
public:
  explicit CompositeDiscount(
      std::vector<std::shared_ptr<DiscountStrategy>> strategies)
      : strategies_(std::move(strategies)) {}

  double Calculate(double price, UserContext user_context) const override {
    double final_price = price;
    for (const auto &strategy : strategies_) {
      final_price = strategy->Calculate(final_price, user_context);
    }
    return final_price;
  }

private:
  std::vector<std::shared_ptr<DiscountStrategy>> strategies_;
};
