#include <iostream>
#include <vector>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>

using namespace std;

namespace nt2 { namespace meta
{
  struct unknown_ {};
  template<class T> struct fundamental_ {};
  template<class T> struct arithmetic_  : fundamental_<T> { typedef fundamental_<T> parent; };
  template<class T> struct integer_     : arithmetic_<T>  { typedef arithmetic_<T> parent; };
  template<class T> struct real_        : arithmetic_<T>  { typedef arithmetic_<T> parent; };

  template<class T> struct signed_
        : boost::mpl::if_ < boost::is_integral<T>
                                  , integer_<T>
                                  , real_<T>
                                  >::type
  {};

  template<class T> struct unsigned_    : integer_<T>   { typedef integer_<T>   parent; };
  template<class T> struct int_         : signed_<T>    { typedef signed_<T>    parent; };
  template<class T> struct uint_        : unsigned_<T>  { typedef unsigned_<T>  parent; };

  template<class T>
  struct  type8_
        : boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type parent;
  };

  template<class T>
  struct  type16_
        : boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type parent;
  };

  template<class T>
  struct  type32_
        : boost::mpl::if_ < boost::is_floating_point<T>
                          , signed_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type
  {
    typedef typename boost::mpl::if_ < boost::is_floating_point<T>
                          , signed_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type parent;
  };

  template<class T>
  struct  type64_
        : boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type
  {
    typedef typename boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type parent;
  };

  template<class T> struct ints8_        : type8_<T>  { typedef type64_<T> parent; };
  template<class T> struct ints16_       : type16_<T> { typedef type64_<T> parent; };
  template<class T> struct ints32_       : type32_<T> { typedef type64_<T> parent; };
  template<class T> struct ints64_       : type64_<T> { typedef type64_<T> parent; };

  template<class T> struct int8_        : ints8_<T>  { typedef ints8_<T> parent; };
  template<class T> struct int16_       : ints16_<T> { typedef ints16_<T> parent; };
  template<class T> struct int32_       : ints32_<T> { typedef ints32_<T> parent; };
  template<class T> struct int64_       : ints64_<T> { typedef ints64_<T> parent; };
  template<class T> struct uint8_       : ints8_<T>  { typedef ints8_<T> parent; };
  template<class T> struct uint16_      : ints16_<T> { typedef ints16_<T> parent; };
  template<class T> struct uint32_      : ints32_<T> { typedef ints32_<T> parent; };
  template<class T> struct uint64_      : ints64_<T> { typedef ints64_<T> parent; };
  template<class T> struct double_      : type64_<T> { typedef type64_<T> parent; };
  template<class T> struct float_       : type32_<T> { typedef type32_<T> parent; };
  template<class T> struct bool_        : fundamental_<T> { typedef fundamental_<T> parent; };
} }

template<class T> char  dispatch(nt2::meta::signed_<T> const&);
template<class T> short dispatch(nt2::meta::unsigned_<T> const&);
template<class T> int   dispatch(nt2::meta::real_<T> const&);

template<class T,class V> char   dispatch(nt2::meta::real_<T> const&,nt2::meta::signed_<V> const&);
template<class T, class V> float  dispatch(nt2::meta::real_<T> const&,nt2::meta::unsigned_<V> const&);

namespace nt2 { namespace meta
{
  template<class T> struct base_hierarchy { typedef unknown_ type; };

  template<> struct base_hierarchy<char> { typedef int8_<char> type; };
  template<> struct base_hierarchy<short> { typedef int16_<short> type; };
  template<> struct base_hierarchy<int> { typedef int32_<int> type; };
  template<> struct base_hierarchy<long long int> { typedef int64_<long long int> type; };
  template<> struct base_hierarchy<unsigned char> { typedef int8_<unsigned char> type; };
  template<> struct base_hierarchy<unsigned short> { typedef int16_<unsigned short> type; };
  template<> struct base_hierarchy<unsigned int> { typedef int32_<unsigned int> type; };
  template<> struct base_hierarchy<unsigned long long int> { typedef int64_<unsigned long long int> type; };
  template<> struct base_hierarchy<float> { typedef float_<float> type; };
  template<> struct base_hierarchy<double> { typedef double_<double> type; };
  template<> struct base_hierarchy<bool> { typedef bool_<double> type; };
} }

#define NT2_REGISTER_HIERARCHY(Name)                            \
template<class T> struct Name : Name< typename T::parent > {};  \
template<class T> struct Name< nt2::meta::fundamental_<T> > {}  \
/**/

namespace nt2 { namespace meta
{
  NT2_REGISTER_HIERARCHY(vector_);

  template<class T, class A>
  struct base_hierarchy< std::vector<T,A> >
  {
    typedef vector_<typename base_hierarchy<T>::type > type;
  };
} }

struct foo { double t[10]; };

template<class T> foo  dispatch( nt2::meta::vector_< nt2::meta::double_<T> > const&);
template<class T> double  dispatch( nt2::meta::vector_< nt2::meta::signed_<T> > const&);

namespace nt2 { namespace meta
{

} }

int main()
{
//  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<double*>::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<std::vector<char> >::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<std::vector<float> >::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<std::vector<double> >::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<char>::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<unsigned char>::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<float>::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<double>::type() ) ) << "\n";
  cout << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<double>::type(), nt2::meta::base_hierarchy<char>::type() ) ) << "\n";
  cout << sizeof( dispatch(  nt2::meta::base_hierarchy<float>::type(), nt2::meta::base_hierarchy<unsigned char>::type()) ) << "\n";
}

//namespace nt2 { namespace meta
//{
//  template<class Sig> struct dispatch2;
//
//  template<class Functor,class A0>
//  struct dispatch2<Functor(A0)>
//  {
//    // Clean up A0
//    typedef typename strip<A0>::type                                arg0_t;
//    typedef typename raw_type<arg0_t>::type                         raw0_t;
//
//    // Insert into hierarchy
//    typedef typename
//    boost::mpl::push_front< typename get_hierarchy<raw0_t>::type
//                          , typename canonize<arg0_t,raw0_t>::type
//                          >::type                                   list0_t;
//
//    // Find proper hierarchy to start digging in
//    typedef typename boost::mpl::find_if< typename get_hierarchy<raw0_t>::type
//                                        , can_dispatch< make_call<Functor, canonize<arg0_t,boost::mpl::_1> > >
//                                        >::type iter0_t;
//
//    // Select the proper specialization with respect to everything
//    typedef typename boost::mpl::eval_if< can_dispatch<Functor(typename canonize<arg0_t,raw0_t>::type)>
//                                        , canonize<arg0_t,raw0_t>
//                                        , canonize<arg0_t,typename boost::mpl::deref<iter0_t>::type>
//                                        >::type target_t;
//
//    typedef functors::call2<Functor(target_t)>                      type;
//  };
//
//  template<class Functor,class A0,class A1>
//  struct dispatch2<Functor(A0,A1)>
//  {
//    // Clean up A0,A1
//    typedef typename strip<A0>::type        arg0_t;
//    typedef typename strip<A1>::type        arg1_t;
//    typedef typename raw_type<arg0_t>::type raw0_t;
//    typedef typename raw_type<arg1_t>::type raw1_t;
//
//    // Insert into hierarchy
//    typedef typename
//    boost::mpl::push_front< typename get_hierarchy<raw0_t>::type
//                          , typename canonize<arg0_t,raw0_t>::type
//                          >::type               list0_t;
//
//    typedef typename
//    boost::mpl::push_front< typename get_hierarchy<raw1_t>::type
//                          , typename canonize<arg1_t,raw1_t>::type
//                          >::type               list1_t;
//
//
//    template<class V, class State>
//    struct inner
//    {
//      typedef typename
//      boost::mpl::fold< typename get_hierarchy<raw1_t>::type//list1_t
//                      , State
//                      , boost::mpl::
//                        push_back< boost::mpl::_1
//                                  , make_call < Functor
//                                              , typename canonize<arg0_t
//                                                                ,typename boost::mpl::protect<V>::type>::type
//                                              , canonize<arg1_t,boost::mpl::_2>
//                                              >
//                                  >
//                     >::type type;
//    };
//
//    // Generate the cartesian_product
//    typedef typename boost::mpl::fold < typename get_hierarchy<raw0_t>::type//list0_t
//                                      , boost::mpl::vector<>
//                                      , inner<boost::mpl::_2, boost::mpl::_1>
//                                      >::type list_t;
//
//    // Find proper hierarchy to start digging in
//    typedef typename boost::mpl::
//    find_if< list_t, can_dispatch<boost::mpl::_1> >::type  iter_t;
//
//    typedef typename boost::mpl::deref<iter_t>::type typee;
//    typedef typename boost::mpl::at_c<list_t,3>::type typee2;
//
//
//    typedef typename canonize < arg0_t
//                              , typename boost::mpl::deref<iter0_t>::type
//                              >::type           target_t;
//
//    typedef functors::call2<Functor(target_t)>  type;
//  };
//} }
//*/
//
//int main()
//{
//  /*
//  meta::dispatch2<functors::complement_(int)>::type::Test();
//  meta::dispatch2<functors::complement_(float)>::type::Test();
//  meta::dispatch2<functors::complement_(bool)>::type::Test();
//  meta::dispatch2<functors::complement_(vector<int>)>::type::Test();
//  meta::dispatch2<functors::complement_(vector<float>)>::type::Test();
//  meta::dispatch2<functors::complement_(vector<bool>)>::type::Test();
//  */
//}
