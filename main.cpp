#include <iostream>
#include <boost/array.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/memory/linear_block.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

using namespace std;

int main()
{
  {
    typedef nt2::memory::linear_block<1, float
                                       , boost::array<int,1>
                                       , boost::mpl::vector4_c<int,2,3,4,5>
                                       , nt2::memory::global_padding
                                       , nt2::memory::allocator<float>
                                       > t;

    t u;
    cout << nt2::type_id<t>() << endl;
    cout << nt2::type_id<t::sizes_type>() << endl;
  }
  {
    typedef nt2::memory::linear_block<1, float
                                       , boost::array<int,1>
                                       , boost::mpl::vector4_c<int,2,3,4,5>
                                       , nt2::memory::no_padding
                                       , nt2::memory::allocator<float>
                                       > t;

    t u;
    cout << nt2::type_id<t>() << endl;
    cout << nt2::type_id<t::sizes_type>() << endl;
  }
}
