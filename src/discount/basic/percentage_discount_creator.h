#pragma once
#include "src/discount/basic/percentage_discount.h"
#include "src/discount/discount_strategy.h"

#include <memory>

class DiscountStrategyCreator {
public:
  virtual ~DiscountStrategyCreator() = default;
  virtual std::shared_ptr<DiscountStrategy> Create() = 0;
};

class PercentageDiscountCreator : public DiscountStrategyCreator {
public:
  explicit PercentageDiscountCreator(double percentage)
      : percentage_(percentage) {}

  std::shared_ptr<DiscountStrategy> Create() override {
    return std::make_shared<PercentageDiscount>(percentage_);
  }

private:
  double percentage_;
};
