#include "src/discount/discount_context.h"
#include "src/discount/discount_strategy_factory.h"

#include <gtest/gtest.h>

class DiscountContextTest : public ::testing::Test {
protected:
  double price = 120.0;
  UserContext user_context = UserContext(UserLevel::Basic);
};

TEST_F(DiscountContextTest, NoDiscount) {
  auto no_discount = DiscountStrategyFactory::CreateNoDiscount();
  DiscountContext context;
  context.SetDiscountStrategy(no_discount);
  EXPECT_EQ(context.Apply(price, user_context), price);
}

TEST_F(DiscountContextTest, ThresholdDiscount) {
  auto threshold_discount =
      DiscountStrategyFactory::CreateThresholdDiscount(100, 20);
  DiscountContext context;
  context.SetDiscountStrategy(threshold_discount);
  EXPECT_EQ(context.Apply(price, user_context), price - 20);
}

TEST_F(DiscountContextTest, PercentageDiscount) {
  auto percentage_discount =
      DiscountStrategyFactory::CreatePercentageDiscount(0.9);
  DiscountContext context;
  context.SetDiscountStrategy(percentage_discount);
  EXPECT_EQ(context.Apply(price, user_context), price * 0.9);
}

TEST_F(DiscountContextTest, CompositeDiscount) {
  auto percentage_discount =
      DiscountStrategyFactory::CreatePercentageDiscount(0.9);
  auto threshold_discount =
      DiscountStrategyFactory::CreateThresholdDiscount(100, 20);
  auto composite_discount = DiscountStrategyFactory::CreateCompositeStrategy(
      std::vector<std::shared_ptr<DiscountStrategy>>{percentage_discount,
                                                     threshold_discount});
  DiscountContext context;
  context.SetDiscountStrategy(composite_discount);
  EXPECT_EQ(context.Apply(price, user_context), price * 0.9 - 20);
}

TEST_F(DiscountContextTest, LimitedTimeDiscount) {
  auto percentage_discount =
      DiscountStrategyFactory::CreatePercentageDiscount(0.9);
  auto valid_limited_time_discount =
      DiscountStrategyFactory::CreateLimitedTimeDiscount(
          percentage_discount, absl::Now() - absl::Hours(1),
          absl::Now() + absl::Hours(1));
  DiscountContext context;
  context.SetDiscountStrategy(valid_limited_time_discount);
  EXPECT_EQ(context.Apply(price, user_context), price * 0.9);
  auto expired_limited_time_discount = std::make_shared<LimitedTimeDiscount>(
      percentage_discount, absl::Now() - absl::Hours(1),
      absl::Now() - absl::Hours(1));
  context.SetDiscountStrategy(expired_limited_time_discount);
  EXPECT_EQ(context.Apply(price, user_context), price);
  auto not_started_limited_time_discount =
      std::make_shared<LimitedTimeDiscount>(percentage_discount,
                                            absl::Now() + absl::Hours(1),
                                            absl::Now() + absl::Hours(2));
  context.SetDiscountStrategy(not_started_limited_time_discount);
  EXPECT_EQ(context.Apply(price, user_context), price);
}

TEST_F(DiscountContextTest, UserLevelDiscount) {
  auto user_level_discount = DiscountStrategyFactory::CreateUserLevelDiscount(
      std::unordered_map<UserLevel, double>{{UserLevel::Basic, 0.9},
                                            {UserLevel::Silver, 0.8},
                                            {UserLevel::Gold, 0.7},
                                            {UserLevel::Platinum, 0.6}});
  DiscountContext context;
  context.SetDiscountStrategy(user_level_discount);
  EXPECT_EQ(context.Apply(price, UserContext(UserLevel::Basic)), price * 0.9);
  EXPECT_EQ(context.Apply(price, UserContext(UserLevel::Silver)), price * 0.8);
  EXPECT_EQ(context.Apply(price, UserContext(UserLevel::Gold)), price * 0.7);
  EXPECT_EQ(context.Apply(price, UserContext(UserLevel::Platinum)),
            price * 0.6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
