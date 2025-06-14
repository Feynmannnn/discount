#pragma once

#include "src/user/user_level.h"
#include <string>

class User {
public:
  explicit User(std::string name, UserLevel user_level)
      : name_(std::move(name)), user_level_(user_level) {}

  std::string name() const { return name_; }
  UserLevel user_level() const { return user_level_; }

  void set_user_level(UserLevel user_level) { user_level_ = user_level; }
  void set_name(const std::string &name) { name_ = name; }
  void set_name(std::string &&name) { name_ = std::move(name); }

private:
  std::string name_;
  UserLevel user_level_;
};
