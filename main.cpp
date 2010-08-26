#include <iostream>
#include <boost/array.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/memory/linear_block.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>
#include <nt2/sdk/options/options.hpp>

using namespace std;

NT2_REGISTER_PARAMETERS(size);
NT2_REGISTER_PARAMETERS(base);
NT2_REGISTER_PARAMETERS(padding);

int main()
{
  {
    typedef nt2::memory::linear_block<1, float
                                       , boost::array<int,1>
                                       , boost::array<int,1>
                                       , nt2::memory::global_padding
                                       , nt2::memory::allocator<float>
                                       > t;
    boost::array<int,1> s = {{5}};
    boost::array<int,1> b = {{-2}};
    t u(b,s);
    cout << u.data_.size() << endl;
    cout << u.data_.lower() << endl;
    cout << u.data_.upper() << endl;
    cout << u.data_.capacity() << endl;
    cout << "\n";
    cout << u.size<1>() << endl;
    cout << u.lower<1>() << endl;
    cout << u.upper<1>() << endl;
  }
}
