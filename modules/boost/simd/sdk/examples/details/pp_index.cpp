#include <iostream>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

int main()
{
  // Prints (0 , 1 , 2)
  std::cout << NT2_PP_DEBUG( BOOST_PP_ENUM(3,NT2_PP_INDEX,~)) << std::endl;
}
