#pragma once
#include "src/customer_service/customer_service.h"

class SilverCustomerService : public CustomerService {
public:
  UserLevel SupportedUserLevel() const override { return UserLevel::Silver; }

  std::string_view CustomerServiceName() const override {
    return "SilverCustomerService";
  }
};
