#define NT2_ASSERTS_AS_EXCEPTIONS
#include <iostream>
#include <nt2/sdk/error/assert.hpp>

using namespace std;

template<class T> void f(T const& v)
{
  NT2_ASSERT( v > 4 );
}

int main( int argc, char** argv)
{
  try
  {
    f(1.23456);
  }
  catch( nt2::assert_exception& e )
  {
    cout << e << endl;
  }
}

