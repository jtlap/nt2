#include <iostream>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

int main()
{
  // Prints (foo foo foo)
  std::cout << NT2_PP_DEBUG( BOOST_PP_REPEAT(3,NT2_PP_TEXT,foo)) << std::endl;
}
