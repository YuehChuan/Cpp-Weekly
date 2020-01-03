#include <inc/test_container.hpp>

int test_suite(void) {
  beta::test_container test_client;
  test_client.run_all();
  return 0;
}
