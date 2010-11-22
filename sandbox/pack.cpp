#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/na.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
//#include <nt2/sdk/simd/pack.hpp>
//#include <nt2/include/functions/madd.hpp>

using namespace std;

namespace nt2 { namespace meta
{
  template<class Map> struct link { template<class Key> struct with; };

  template<class Map, class Key, class Enable=void >
  struct has_key : boost::mpl::false_ {};

  template< class Map, class Key>
  struct has_key< Map
                , Key
                , typename enable_if_type < typename  link<Map>
                                                      ::template with<Key>::type
                                          >::type
                >
        : boost::mpl::true_
  {};

  template<class Map, class Key, class Enable=typename has_key<Map,Key>::type >
  struct at_key
  {
    typedef nt2::meta::na_ type;
  };

  template< class Map, class Key>
  struct at_key < Map, Key, boost::mpl::true_ >
  {
    typedef typename link<Map>::template with<Key>::type type;
  };

} }

namespace nt2 { namespace meta
{
  template<> template<>
  struct link<int>::with<float> { typedef char*** type; };
} }

int main()
{
  cout << nt2::type_id<nt2::meta::has_key<int,float>::type>() << endl;
  cout << nt2::type_id<nt2::meta::at_key<int,float>::type>() << endl;

//  nt2::simd::pack<float> x(1);
//  nt2::simd::pack<float> y(2);
//  nt2::simd::pack<float> z(3);

// cout << x+y*z << "\n";
// cout << y*z+x << "\n";
// cout << (y*z+x)*(y*z+x)+(y*z+x) << "\n";
}
