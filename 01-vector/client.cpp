#include <inc/test_vector.hpp>

int test_suite(void) {
  beta::test_vector test_client;
  test_client.run_all();
  return 0;
}
