#pragma once
#include "src/user/user_level.h"

class UserContext {
public:
  explicit UserContext(UserLevel user_level) : user_level_(user_level) {}
  UserLevel user_level() const { return user_level_; }

private:
  UserLevel user_level_;
};
