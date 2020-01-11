#ifndef __TEST_STRING_HPP__
#define __TEST_STRING_HPP__

#include <algorithm>
#include <functional>
#include <vector>

#include <inc/beta.hpp>
#include <inc/noncopyable.hpp>
#include <inc/string.hpp>

class beta::test_string : public beta::noncopyable {
  using test_case  = std::function<void(void)>;
  using test_suite = std::vector<test_case>;

  static constexpr char* const color_red   = const_cast<char* const>("\033[1;31m");
  static constexpr char* const color_gray  = const_cast<char* const>("\033[1;30m");
  static constexpr char* const color_green = const_cast<char* const>("\033[1;32m");
  static constexpr char* const color_reset = const_cast<char* const>("\033[0m");

  static void test_status(const char* const signature, bool bool_expression);

public:
  test_string() = default;

  ~test_string() = default;

  static void run_all();
};

void beta::test_string::run_all() {
  auto execute = [](test_suite coverage_functions) {
    std::for_each(coverage_functions.begin(), coverage_functions.end(), [](test_case test_feature) { test_feature(); });
  };
  execute(test_suite{});
}

#endif
