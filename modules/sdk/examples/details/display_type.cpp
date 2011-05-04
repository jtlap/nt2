#include <vector>
#include <nt2/sdk/details/type_id.hpp>

int main()
{
  nt2::display_type("some litteral string");
  nt2::display_type(3.14159f);
  nt2::display_type< std::vector<long*> >();
}
