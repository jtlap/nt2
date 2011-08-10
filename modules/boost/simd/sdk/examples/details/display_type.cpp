#include <vector>
#include <boost/simd/details/type_id.hpp>

int main()
{
  boost::display_type("some litteral string");
  boost::display_type(3.14159f);
  boost::display_type< std::vector<long*> >();
}
