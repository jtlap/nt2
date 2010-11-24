#include <iostream>
#include <vector>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/details/type_id.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/transform.hpp>

using namespace std;
using namespace nt2;

namespace nt2 { namespace meta
{
  template<class T>         struct raw_type { typedef T type; };
  template<class T,class H> struct canonize { typedef H type; };
} }

namespace nt2 { namespace tag
{
  struct std_vector_ {};
}}

namespace nt2 { namespace meta
{
  template<class T,class A>
  struct raw_type< std::vector<T,A> >
  {
    typedef T type;
  };

  template<class T,class A, class H>
  struct canonize< std::vector<T,A>, H >
  {
    typedef tag::std_vector_ type(H);
  };
} }

namespace nt2 { namespace functors
{
  template<class Sig, class Dummy = void> struct call2 {};

  template<class Dummy>
  struct call2<complement_(fundamental_),Dummy> : callable
  {
    static void Test() { cout << "complement_(fundamental_)\n"; }
  };

  template<class Dummy>
  struct call2<complement_(int),Dummy> : callable
  {
    static void Test() { cout << "complement_(int)\n"; }
  };

  template<class Dummy>
  struct call2<complement_(tag::std_vector_(bool_)),Dummy> : callable
  {
    static void Test() { cout << "complement_(tag::std_vector_(bool_))\n"; }
  };

  template<class Dummy>
  struct call2<complement_(tag::std_vector_(arithmetic_)),Dummy> : callable
  {
    static void Test() { cout << "complement_(tag::std_vector_(arithmetic_))\n"; }
  };

  template<class Dummy>
  struct call2<plus_(fundamental_,fundamental_),Dummy> : callable
  {
    static void Test() { cout << "plus_(fundamental_,fundamental_)\n"; }
  };

  template<class Dummy>
  struct call2<plus_(fundamental_,tag::std_vector_(fundamental_)),Dummy> : callable
  {
    static void Test() { cout << "plus_(fundamental_,tag::std_vector_(fundamental_))\n"; }
  };

  template<class Dummy>
  struct call2<plus_(tag::std_vector_(fundamental_),fundamental_),Dummy> : callable
  {
    static void Test() { cout << "plus_(tag::std_vector_(fundamental_),fundamental_)\n"; }
  };

  template<class Dummy>
  struct call2<plus_(tag::std_vector_(fundamental_),tag::std_vector_(fundamental_)),Dummy> : callable
  {
    static void Test() { cout << "plus_(tag::std_vector_(fundamental_),tag::std_vector_(fundamental_))\n"; }
  };
} }

namespace nt2 { namespace meta
{
  template<class Signature, class Enable = void>
  struct can_dispatch : boost::mpl::false_ {};

  template<class Signature>
  struct  can_dispatch < Signature
                          , typename functors::call2<Signature>::callable_type
                          >
        : boost::mpl::true_ {};
} }

namespace nt2 { namespace functors
{
  typedef boost::mpl::vector3 < bool_
                              , arithmetic_
                              , fundamental_
                              > boolean_hierarchies;

  typedef boost::mpl::vector6 < types32_
                              , types64_
                              , real_
                              , signed_
                              , arithmetic_
                              , fundamental_
                              > real_hierarchies;

  typedef boost::mpl::vector12< int8_
                              , int16_
                              , int32_
                              , int64_
                              , types32_
                              , types64_
                              , uint_
                              , int_
                              , signed_
                              , integer_
                              , arithmetic_
                              , fundamental_
                              > integral_hierarchies;
} }

namespace nt2 { namespace meta
{
  template< class T
          , bool isBool = boost::is_same<bool,T>::value
          , bool isReal = boost::is_floating_point<T>::value
          , bool isInt  = boost::is_integral<T>::value
          >
  struct get_hierarchy
  {
    typedef boost::mpl::vector1<functors::empty_> type;
  };

  template<class T> struct get_hierarchy<T,true,false,true>
  {
    typedef functors::boolean_hierarchies type;
  };

  template< class T> struct get_hierarchy<T,false,true,false>
  {
    typedef functors::real_hierarchies type;
  };

  template< class T> struct get_hierarchy<T,false,false,true>
  {
    typedef functors::integral_hierarchies type;
  };
} }

namespace nt2 { namespace meta
{
  template<class Functor, class A0> struct make_call
  {
    typedef Functor type(A0);
  };

  template<class Sig> struct dispatch2;

  template<class Functor,class A0>
  struct dispatch2<Functor(A0)>
  {
    // Clean up A0
    typedef typename strip<A0>::type        arg0_t;
    typedef typename raw_type<arg0_t>::type raw0_t;

    // Find proper hierarchy to start digging in
    typedef typename boost::mpl::find_if< typename get_hierarchy<raw0_t>::type
                                        , can_dispatch< make_call<Functor, canonize<arg0_t,boost::mpl::_1> > >
                                        >::type iter0_t;

    typedef typename boost::mpl::eval_if< can_dispatch<Functor(typename canonize<arg0_t,raw0_t>::type)>
                                        , canonize<arg0_t,raw0_t>
                                        , canonize<arg0_t,typename boost::mpl::deref<iter0_t>::type>
                                        >::type target_t;

    typedef functors::call2<Functor(target_t)> type;
  };
} }

int main()
{
  meta::dispatch2<functors::complement_(int)>::type::Test();
  meta::dispatch2<functors::complement_(float)>::type::Test();
  meta::dispatch2<functors::complement_(bool)>::type::Test();
  meta::dispatch2<functors::complement_(vector<int>)>::type::Test();
  meta::dispatch2<functors::complement_(vector<float>)>::type::Test();
  meta::dispatch2<functors::complement_(vector<bool>)>::type::Test();
}
