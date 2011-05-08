#include <iostream>
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <boost/type_traits/is_same.hpp>

using namespace std;
using namespace boost;
using namespace boost::mpl;

int main()
{
  cout  << "Any bool in vector<int,bool,float> :"
        << nt2::meta::any<is_same<_,bool>, vector<int,bool,float> >::value
        << "\n";

  cout  << "Any bool in {int,char,float} :"
        << nt2::meta::any<is_same<_,bool>, int,char,float>::value
        << "\n";
}
