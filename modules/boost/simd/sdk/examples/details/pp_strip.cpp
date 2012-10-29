#include <iostream>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/preprocessor/stringize.hpp>

int main()
{
  std::cout << BOOST_PP_STRINGIZE( BOOST_DISPATCH_PP_STRIP(no parens) ) << std::endl;
  std::cout << BOOST_PP_STRINGIZE( BOOST_DISPATCH_PP_STRIP((with parens)) ) << std::endl;
}
