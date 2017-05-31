#include "dispatch/map.hpp"
#include "dispatch/string_literal.hpp"

#include <iostream>
#include <vector>

using namespace dispatch::literals;

int main() {
  auto example_map = dispatch::make_map(
    std::make_tuple(
      "abc"_s,
      "foo"_s,
      "bar"_s,
      "qwerty"_s,
      "asdf"_s
    ),
    std::make_tuple(
      0.1,
      1,
      std::string("bar"),
      std::vector<int>{1, 2, 3},
      std::make_tuple("hello", "world")
    )
  );

  std::cout << "abc: " << *example_map.at<double>("abc") << "\n";
  std::cout << "foo: " << *example_map.at<int>("foo") << "\n";
  std::cout << "bar: " << *example_map.at<std::string>("bar") << "\n";
  example_map.insert("abc", 0.2);
  std::cout << "abc: " << *example_map.at<double>("abc") << "\n";
  return 0;
}
