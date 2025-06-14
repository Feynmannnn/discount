#pragma once

class Order {
public:
  explicit Order(double price) : price_(price) {}

  double price() const { return price_; }

private:
  double price_;
};
