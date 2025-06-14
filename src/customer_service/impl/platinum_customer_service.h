#pragma once
#include "src/customer_service/customer_service.h"

class PlatinumCustomerService : public CustomerService {
public:
  UserLevel SupportedUserLevel() const override { return UserLevel::Platinum; }

  std::string_view CustomerServiceName() const override {
    return "PlatinumCustomerService";
  }
};
