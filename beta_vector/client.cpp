#include <beta_vector.hpp>
#include <test_container.hpp>

int test_suite(void) {
  test_container test_client;
  test_client.run_all();
  return 0;
}
