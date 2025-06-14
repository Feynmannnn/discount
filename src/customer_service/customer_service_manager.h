#pragma once
#include "src/customer_service/customer_service.h"
#include "src/customer_service/impl/default_customer_service.h"
#include "src/customer_service/impl/gold_customer_service.h"
#include "src/customer_service/impl/platinum_customer_service.h"
#include "src/customer_service/impl/silver_customer_service.h"

#include <memory>
#include <optional>
#include <unordered_map>

class CustomerServiceManager {
public:
  std::optional<std::shared_ptr<CustomerService>>
  GetCustomerService(UserLevel user_level) const {
    const auto &service_map = ServiceMap();
    auto it = service_map.find(user_level);
    if (it != service_map.end()) {
      return it->second;
    }
    return std::nullopt;
  }

private:
  static const std::unordered_map<UserLevel, std::shared_ptr<CustomerService>> &
  ServiceMap() {
    static const std::unordered_map<UserLevel, std::shared_ptr<CustomerService>>
        service_map = {
            {UserLevel::Basic, std::make_shared<DefaultCustomerService>()},
            {UserLevel::Silver, std::make_shared<SilverCustomerService>()},
            {UserLevel::Gold, std::make_shared<GoldCustomerService>()},
            {UserLevel::Platinum, std::make_shared<PlatinumCustomerService>()}};
    return service_map;
  }
};
