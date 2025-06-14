#include "src/customer_service/customer_service_manager.h"

#include <gtest/gtest.h>

TEST(CustomerServiceTest, GetCustomerService) {
  CustomerServiceManager manager;
  auto service = manager.GetCustomerService(UserLevel::Basic);
  ASSERT_TRUE(service.has_value());
  EXPECT_EQ(service->get()->CustomerServiceName(), "DefaultCustomerService");

  service = manager.GetCustomerService(UserLevel::Silver);
  ASSERT_TRUE(service.has_value());
  EXPECT_EQ(service->get()->CustomerServiceName(), "SilverCustomerService");

  service = manager.GetCustomerService(UserLevel::Gold);
  ASSERT_TRUE(service.has_value());
  EXPECT_EQ(service->get()->CustomerServiceName(), "GoldCustomerService");

  service = manager.GetCustomerService(UserLevel::Platinum);
  ASSERT_TRUE(service.has_value());
  EXPECT_EQ(service->get()->CustomerServiceName(), "PlatinumCustomerService");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
