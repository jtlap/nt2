#include <iostream>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL(small_test, (double)(float)(int))
{
  std::cout << "This is a test" << std::endl;
}
