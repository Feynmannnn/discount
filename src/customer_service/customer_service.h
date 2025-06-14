#pragma once
#include "src/user/user_level.h"
#include <string_view>

class CustomerService {
public:
  virtual UserLevel SupportedUserLevel() const = 0;
  virtual std::string_view CustomerServiceName() const = 0;
  virtual ~CustomerService() = default;
};
