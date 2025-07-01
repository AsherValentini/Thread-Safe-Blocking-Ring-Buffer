#pragma once

struct Tick {
  Tick(std::string symbol, float price) : price_(price), symbol_(symbol) {}

  float price_;
  std::string symbol_;
};

inline bool operator==(const Tick& lhs, const Tick& rhs) {
  return lhs.symbol_ == rhs.symbol_ && lhs.price_ == rhs.price_;
}
inline std::ostream& operator<<(std::ostream& os, const Tick& tick) {
  return os << "Tick(" << tick.symbol_ << ", " << tick.price_ << ")";
}
