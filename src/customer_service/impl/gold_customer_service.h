#pragma once
#include "src/customer_service/customer_service.h"

class GoldCustomerService : public CustomerService {
public:
  UserLevel SupportedUserLevel() const override { return UserLevel::Gold; }

  std::string_view CustomerServiceName() const override {
    return "GoldCustomerService";
  }
};
