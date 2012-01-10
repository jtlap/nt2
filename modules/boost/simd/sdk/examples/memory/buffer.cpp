#include <iostream>
#include <algorithm>

#include <nt2/sdk/error/assert.hpp>

int main()
{
  nt2::memory::buffer<int> b1(0,5);
  nt2::memory::buffer<int> b2(-3,5);

  //Update first element
  b1[0]  = 1;
  b2[-3] = 2;
  
  //update last element 
  b1[4]  = *(b1.begin()) + 1;
  b2[-3] = *(b2.begin()) + 1;

  NT2_ASSERT( *(b1.begin()) == b1[0]  );
  NT2_ASSERT( *(b2.begin()) == b2[-3] );

  std::cout << "Buffer 1 size  = " << b1.size()  << std::endl;
  std::cout << "Buffer 2 size  = " << b1.size()  << std::endl;
  
  return 0;
}
