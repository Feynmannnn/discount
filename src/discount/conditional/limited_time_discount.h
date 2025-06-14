#pragma once
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "src/discount/discount_strategy.h"

#include <memory>

class LimitedTimeDiscount : public DiscountStrategy {
public:
  explicit LimitedTimeDiscount(
      std::shared_ptr<DiscountStrategy> discount_strategy,
      absl::Time start_time, absl::Time end_time)
      : discount_strategy_(discount_strategy), start_time_(start_time),
        end_time_(end_time) {}

  double Calculate(double price, UserContext user_context) const override {
    auto now = absl::Now();
    if (now < start_time_ || now > end_time_) {
      return price;
    }
    return discount_strategy_->Calculate(price, user_context);
  }

private:
  std::shared_ptr<DiscountStrategy> discount_strategy_;
  absl::Time start_time_;
  absl::Time end_time_;
};
