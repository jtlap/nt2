#include <iostream>
#include <boost/preprocessor/stringize.hpp>
#include <boost/dispatch/preprocessor/remove_typename.hpp>

#define FOO(X)                                              \
BOOST_PP_STRINGIZE( BOOST_DISPATCH_PP_REMOVE_TYPENAME(X) )  \
/**/

int main()
{
  std::cout << FOO(add_pointer<float>::type)      << std::endl;
  std::cout << FOO(typename add_pointer<T>::type) << std::endl;
}
