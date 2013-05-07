#include <iostream>
#include <boost/dispatch/preprocessor/strip.hpp>

int main()
{
  std::cout << BOOST_DISPATCH_PP_STRIP("without parentheses") << std::endl;
  std::cout << BOOST_DISPATCH_PP_STRIP(("with parentheses")) << std::endl;
}
