#include <iostream>
#include <boost/assert.hpp>
#include <nt2/sdk/error/assert.hpp>

int main()
{
  try
  {
    BOOST_ASSERT_MSG(false, "This is a forced trigger !");
  }
  catch( nt2::exception& e )
  {
    std::cout << "Captured:\n" << e.what() << "\n";
  }

  std::cout << "Normal execution resumes here ...\n";
}
