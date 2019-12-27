#include <beta_vector.hpp> // beta_vector
#include <cstring>         // atoi

int test_suite([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  int capacity = 2;
  beta_vector<int> dataset(capacity);
  [[maybe_unused]] auto test_resize = [&]() {
    for (int test_size = 1; test_size <= atoi(argv[1]); ++test_size) {
      dataset.resize(capacity << test_size);
    }
  };
  test_resize();
  return 0;
}
