#include <iostream>
#include <boost/tr1/functional.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/apply.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/operators.hpp>

using namespace std;
using namespace nt2;

struct callable { typedef void callable_type; };

template<class Tag,class Category,class Hierarchy,class Info=void>
struct call;

template<class Tag,class Category, class Hierarchy, class Info = void>
struct  enable_dispatch : boost::mpl::false_
{};

template<class Tag,class Category, class Hierarchy>
struct  enable_dispatch < Tag,Category,Hierarchy
                        , typename call<Tag,Category,Hierarchy>::callable_type
                        >
      : boost::mpl::true_ {};

template<class Tag,class Category>
struct  make_dispatch_list
{
  typedef boost::mpl::if_ < enable_dispatch <Tag, Category, boost::mpl::_2>
                          , boost::mpl::push_back<boost::mpl::_1,boost::mpl::_2>
                          , boost::mpl::_1
                          > selector;

  typedef typename  boost::mpl::fold< boost::mpl::
                                      vector10< nt2::uint8_t  , nt2::int8_t
                                              , nt2::uint16_t , nt2::int16_t
                                              , nt2::uint32_t , nt2::int32_t
                                              , nt2::uint64_t , nt2::int64_t
                                              , float         , double
                                              >
                                    , boost::mpl::vector<>
                                    , selector
                                    >::type base;

  typedef typename  boost::mpl::fold< functors::hierarchies
                                    , base, selector
                                    >::type type;
};

namespace nt2 { namespace meta
{
  template<class Tag, class Category, class Target>
  struct dispatch
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type   pool;
      typedef typename boost::mpl::apply1 < Target
                                          , typename strip<A0>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef ::call<Tag,Category,hierarchy_type> type;
    };

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply2 < Target
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef ::call<Tag,Category,hierarchy_type> type;
    };

    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply3 < Target
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          , typename strip<A2>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef ::call<Tag,Category,hierarchy_type> type;
    };

    template<class This,class A0,class A1,class A2,class A3>
    struct result<This(A0,A1,A2,A3)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply4 < Target
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          , typename strip<A2>::type
                                          , typename strip<A3>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef ::call<Tag,Category,hierarchy_type> type;
    };
  };
} }

template<class Info>
struct  call<functors::plus_, tag::scalar_(tag::arithmetic_),functors::real_,Info>
      : callable {};

template<class Info>
struct  call<functors::plus_, tag::scalar_(tag::arithmetic_),functors::integer_,Info>
      : callable {};

template<class Info>
struct  call<functors::plus_, tag::scalar_(tag::arithmetic_),functors::int8_,Info>
      : callable {};

template<class Info>
struct  call<functors::plus_, tag::scalar_(tag::arithmetic_),nt2::int8_t,Info>
      : callable {};

template<class Info>
struct  call<functors::plus_, tag::scalar_(tag::arithmetic_),double,Info>
      : callable {};

int main()
{
  typedef meta::dispatch< functors::plus_
                        , tag::scalar_(tag::arithmetic_)
                        , boost::mpl::_2
                        > d_t;

  typedef std::tr1::result_of<d_t(nt2::int32_t,float)>::type r1;
  typedef std::tr1::result_of<d_t(nt2::int32_t,nt2::int32_t)>::type r2;
  typedef std::tr1::result_of<d_t(nt2::int32_t,double)>::type r3;
  typedef std::tr1::result_of<d_t(nt2::int32_t,nt2::uint8_t)>::type r4;
  typedef std::tr1::result_of<d_t(nt2::int32_t,nt2::int8_t)>::type r5;

  cout << type_id<r1>() << endl;
  cout << type_id<r2>() << endl;
  cout << type_id<r3>() << endl;
  cout << type_id<r4>() << endl;
  cout << type_id<r5>() << endl;
}
