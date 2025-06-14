#pragma once
#include "src/discount/basic/no_discount.h"
#include "src/discount/basic/percentage_discount.h"
#include "src/discount/basic/threshold_discount.h"
#include "src/discount/composite/composite_strategy.h"
#include "src/discount/conditional/limited_time_discount.h"
#include "src/discount/conditional/user_level_discount.h"
#include "src/discount/discount_strategy.h"

#include <memory>
#include <vector>

class DiscountStrategyFactory {
public:
  static std::shared_ptr<DiscountStrategy> CreateNoDiscount() {
    return std::make_shared<NoDiscount>();
  }

  static std::shared_ptr<DiscountStrategy>
  CreatePercentageDiscount(double percentage) {
    return std::make_shared<PercentageDiscount>(percentage);
  }

  static std::shared_ptr<DiscountStrategy>
  CreateThresholdDiscount(double threshold, double discount) {
    return std::make_shared<ThresholdDiscount>(threshold, discount);
  }

  static std::shared_ptr<DiscountStrategy> CreateUserLevelDiscount(
      std::unordered_map<UserLevel, double> user_level_discount_map) {
    return std::make_shared<UserLevelDiscount>(user_level_discount_map);
  }

  static std::shared_ptr<DiscountStrategy>
  CreateLimitedTimeDiscount(std::shared_ptr<DiscountStrategy> discount_strategy,
                            absl::Time start_time, absl::Time end_time) {
    return std::make_shared<LimitedTimeDiscount>(discount_strategy, start_time,
                                                 end_time);
  }

  static std::shared_ptr<DiscountStrategy> CreateCompositeStrategy(
      std::vector<std::shared_ptr<DiscountStrategy>> strategies) {
    return std::make_shared<CompositeDiscount>(std::move(strategies));
  }
};
