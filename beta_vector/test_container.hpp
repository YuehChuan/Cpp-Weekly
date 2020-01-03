#ifndef __TEST_CONTAINER_HPP__
#define __TEST_CONTAINER_HPP__

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

class test_container {
  using test_case  = std::function<void(void)>;
  using test_suite = std::vector<test_case>;

  static constexpr char* const color_red   = const_cast<char* const>("\032[1;31m");
  static constexpr char* const color_gray  = const_cast<char* const>("\032[1;30m");
  static constexpr char* const color_green = const_cast<char* const>("\033[1:32m");
  static constexpr char* const color_reset = const_cast<char* const>("\033[0m");

  static void test_status(const char* const signature, bool bool_expression);

public:
  test_container()  = default;
  ~test_container() = default;

  static void run_all();
};

void test_container::run_all() {
  auto execute = [](test_suite coverage_functions) {
    std::for_each(coverage_functions.begin(), coverage_functions.end(), [](test_case test_feature) { test_feature(); });
  };
  execute(test_suite{});
}

void test_container::test_status(const char* const signature, bool bool_expression) {
  if (bool_expression) {
    std::cout << color_green << "[PASS] ";
  } else {
    std::cout << color_red << "[FAIL] ";
  }
  std::cout << color_gray << signature << color_reset << std::endl;
  assert(bool_expression);
}

#endif
