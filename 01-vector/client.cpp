#include <inc/test_vector.hpp>

auto test_suite() -> int {
  beta::test_vector test_client;
  test_client.run_all();
  return 0;
}
