#include <iostream>
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/all.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace std;
using namespace boost;
using namespace boost::mpl;

int main()
{
  cout  << "All bool in vector<bool,bool> :"
        << nt2::meta::all<is_same<_,bool>, vector<bool,bool> >::value
        << "\n";

  cout  << "All bool in {int,bool,float} :"
        << nt2::meta::all<is_same<_,bool>, int,bool,float>::value
        << "\n";
}
