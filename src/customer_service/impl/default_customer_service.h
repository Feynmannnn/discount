#pragma once
#include "src/customer_service/customer_service.h"

class DefaultCustomerService : public CustomerService {
public:
  UserLevel SupportedUserLevel() const override { return UserLevel::Basic; }

  std::string_view CustomerServiceName() const override {
    return "DefaultCustomerService";
  }
};
