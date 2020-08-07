//
// Swring.cpp
// Created by viraltaco on 20/06/2020.

#include "Stash.hpp"
#include <vector>
#include <iostream>

int main() {
  using namespace vt::literals;
  static constexpr auto nl = '\n';
  
  
  for (const auto u: { "Hello"_sh, "Bitch"_sh, "hello"_sh,
                       "Hello, World!"_sh, "World!Hahdgfeizuf gfeuzgfbfbf sggfiu "_sh }) {
    std::cout << u << nl;
  }
}