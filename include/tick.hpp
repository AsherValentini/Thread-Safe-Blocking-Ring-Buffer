#pragma once

struct Tick {
  Tick(std::string symbol, float price) : price_(price), symbol_(symbol) {}

  float price_;
  std::string symbol_;
};