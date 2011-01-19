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
  typedef boost::mpl::vector1 < fundamental_
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
  template< class Functor
          , class A0
          , class A1 = na_
          , class A2 = na_
          , class A3 = na_
          >
  struct make_call;

  template<class Functor, class A0>
  struct make_call<Functor,A0>
  {
    typedef Functor type(A0);
  };

  template<class Functor, class A0,class A1>
  struct make_call<Functor, A0, A1>
  {
    typedef Functor type(A0,A1);
  };

  template<class Sig> struct dispatch2;

  template<class Functor,class A0>
  struct dispatch2<Functor(A0)>
  {
    // Clean up A0
    typedef typename strip<A0>::type                                arg0_t;
    typedef typename raw_type<arg0_t>::type                         raw0_t;

    // Insert into hierarchy
    typedef typename
    boost::mpl::push_front< typename get_hierarchy<raw0_t>::type
                          , typename canonize<arg0_t,raw0_t>::type
                          >::type                                   list0_t;

    // Find proper hierarchy to start digging in
    typedef typename boost::mpl::find_if< typename get_hierarchy<raw0_t>::type
                                        , can_dispatch< make_call<Functor, canonize<arg0_t,boost::mpl::_1> > >
                                        >::type iter0_t;

    // Select the proper specialization with respect to everything
    typedef typename boost::mpl::eval_if< can_dispatch<Functor(typename canonize<arg0_t,raw0_t>::type)>
                                        , canonize<arg0_t,raw0_t>
                                        , canonize<arg0_t,typename boost::mpl::deref<iter0_t>::type>
                                        >::type target_t;

    typedef functors::call2<Functor(target_t)>                      type;
  };

  template<class Functor,class A0,class A1>
  struct dispatch2<Functor(A0,A1)>
  {
    // Clean up A0,A1
    typedef typename strip<A0>::type        arg0_t;
    typedef typename strip<A1>::type        arg1_t;
    typedef typename raw_type<arg0_t>::type raw0_t;
    typedef typename raw_type<arg1_t>::type raw1_t;

    // Insert into hierarchy
    typedef typename
    boost::mpl::push_front< typename get_hierarchy<raw0_t>::type
                          , typename canonize<arg0_t,raw0_t>::type
                          >::type               list0_t;

    typedef typename
    boost::mpl::push_front< typename get_hierarchy<raw1_t>::type
                          , typename canonize<arg1_t,raw1_t>::type
                          >::type               list1_t;


    template<class V, class State>
    struct inner
    {
      typedef typename
      boost::mpl::fold< typename get_hierarchy<raw1_t>::type//list1_t
                      , State
                      , boost::mpl::
                        push_back< boost::mpl::_1
                                  , make_call < Functor
                                              , typename canonize<arg0_t
                                                                ,typename boost::mpl::protect<V>::type>::type
                                              , canonize<arg1_t,boost::mpl::_2>
                                              >
                                  >
                     >::type type;
    };

    // Generate the cartesian_product
    typedef typename boost::mpl::fold < typename get_hierarchy<raw0_t>::type//list0_t
                                      , boost::mpl::vector<>
                                      , inner<boost::mpl::_2, boost::mpl::_1>
                                      >::type list_t;

    // Find proper hierarchy to start digging in
    typedef typename boost::mpl::
    find_if< list_t, can_dispatch<boost::mpl::_1> >::type  iter_t;

    typedef typename boost::mpl::deref<iter_t>::type typee;
    typedef typename boost::mpl::at_c<list_t,3>::type typee2;

/*
    typedef typename canonize < arg0_t
                              , typename boost::mpl::deref<iter0_t>::type
                              >::type           target_t;

    typedef functors::call2<Functor(target_t)>  type;*/
  };
} }

int main()
{
  /*
  meta::dispatch2<functors::complement_(int)>::type::Test();
  meta::dispatch2<functors::complement_(float)>::type::Test();
  meta::dispatch2<functors::complement_(bool)>::type::Test();
  meta::dispatch2<functors::complement_(vector<int>)>::type::Test();
  meta::dispatch2<functors::complement_(vector<float>)>::type::Test();
  meta::dispatch2<functors::complement_(vector<bool>)>::type::Test();
  */
  cout  <<
        type_id<meta::dispatch2<functors::plus_(bool,bool)>::list_t>()
        << "\n";
}
