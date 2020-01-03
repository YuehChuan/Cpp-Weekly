#ifndef __TEST_CONTAINER_HPP__
#define __TEST_CONTAINER_HPP__

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <random>
#include <vector>

#include <inc/beta.hpp>
#include <inc/noncopyable.hpp>
#include <inc/vector.hpp>

class beta::test_vector : public beta::noncopyable {
  using test_case  = std::function<void(void)>;
  using test_suite = std::vector<test_case>;

  static constexpr char* const color_red   = const_cast<char* const>("\033[1;31m");
  static constexpr char* const color_gray  = const_cast<char* const>("\033[1;30m");
  static constexpr char* const color_green = const_cast<char* const>("\033[1;32m");
  static constexpr char* const color_reset = const_cast<char* const>("\033[0m");

  static void test_status(const char* const signature, bool bool_expression);

public:
  test_vector()  = default;
  ~test_vector() = default;

  static void run_all();
  static void test_resize();
  static void test_emplace_back();
};

void beta::test_vector::run_all() {
  auto execute = [](test_suite coverage_functions) {
    std::for_each(coverage_functions.begin(), coverage_functions.end(), [](test_case test_feature) { test_feature(); });
  };
  execute(test_suite{test_resize, test_emplace_back});
}

void beta::test_vector::test_resize() {
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(1, std::numeric_limits<short>::max() << 1);
  int init_capacity     = distribution(generator);
  int required_capacity = init_capacity << 1;
  beta::vector<int> dataset1st(init_capacity);
  std::vector<int> dataset2nd(init_capacity);
  dataset1st.resize(required_capacity);
  dataset2nd.resize(required_capacity);
  test_status(__PRETTY_FUNCTION__, (dataset1st.capacity() == dataset2nd.capacity()));
}

void beta::test_vector::test_emplace_back() {
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(1, std::numeric_limits<short>::max());
  int init_capacity = distribution(generator);
  int rnd_num       = distribution(generator);
  beta::vector<int> dataset1st(init_capacity);
  std::vector<int> dataset2nd(init_capacity);
  dataset1st.emplace_back(rnd_num >> 1);
  dataset1st.emplace_back(rnd_num >> 2);
  dataset1st.emplace_back(rnd_num >> 3);
  dataset2nd.emplace_back(rnd_num >> 1);
  dataset2nd.emplace_back(rnd_num >> 2);
  dataset2nd.emplace_back(rnd_num >> 3);
  test_status(__PRETTY_FUNCTION__, dataset1st.back() == dataset2nd.back());
}

void beta::test_vector::test_status(const char* const signature, bool bool_expression) {
  if (bool_expression) {
    std::cout << color_green << "[PASS] ";
  } else {
    std::cout << color_red << "[FAIL] ";
  }
  std::cout << color_gray << signature << color_reset << std::endl;
  assert(bool_expression);
}

#endif
