/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container scheduler"

#include <nt2/table.hpp>
#include <nt2/include/functions/schedule.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/proto/debug.hpp>

template<class T, class N0>
struct node1 {};

template<class T, class N0, class N1>
struct node2 {};

template<class Tag, class Expr, int N>
struct as_node_impl;

template<class Expr>
struct as_node
 : as_node_impl< typename boost::proto::tag_of<Expr>::type
               , Expr
               , boost::proto::arity_of<Expr>::type::value
               >
{
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 0>
{
  typedef Tag type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 1>
{
  typedef node1<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
               > type;
};

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 2>
{
  typedef node2<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
               > type;
};

struct scheduler
{
  template<class Sig>
  struct result;

  template<class This, class T>
  struct result<This(T)>
  {
    typedef typename boost::dispatch::meta::strip<T>::type stripped;
    typedef typename boost::dispatch::meta::semantic_of<stripped const&>::type semantic;
    typedef typename boost::dispatch::meta::terminal_of<semantic>::type type;
  };

  template<class T>
  typename result<scheduler(T const&)>::type operator()(T const&) const
  {
    trees.push_back(&typeid(typename as_node<T>::type));

    static typename boost::remove_reference<typename result<scheduler(T const&)>::type>::type r;
    return r;
  }

  mutable std::vector<std::type_info const*> trees;
};

#define SCHEDULE(Expr, f, N)                                                   \
f.trees.clear();                                                               \
std::cout << "\nScheduling `" << NT2_PP_STRINGIZE(Expr) << "`\n";              \
nt2::schedule(Expr, f);                                                        \
NT2_TEST_EQUAL( f.trees.size(), N )                                            \
/**/

NT2_TEST_CASE( element_wise )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4;
  using nt2::schedule;
  scheduler f;

  SCHEDULE( assign(a0, a1), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , boost::proto::tag::terminal
                             >
                      )
                    );

  SCHEDULE( assign(a0, a1 + a2), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( assign(a0, nt2::plus(a1, a2)), f, 1);
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( assign(a0, a1 + a2 + a3), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + a1, f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + a1 + a2, f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
}

NT2_TEST_CASE( reduction )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4, a5;
  scheduler f;

  using nt2::sum;

  SCHEDULE( sum(a0), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( assign(a0, sum(a1)), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );

  SCHEDULE( a0 + sum(a1), f, 2 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );

  SCHEDULE( assign(a0, a1 + sum(a2)), f, 2 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );

  SCHEDULE( a0 + sum(a1 + a2) + a3, f, 2 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    >
                      )      >
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );

  SCHEDULE( a0 + sum(a1 + sum(a2 + a3) + a4) + a5, f, 3 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    >
                      )      >
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< boost::simd::tag::sum_
                                    , node2< boost::proto::tag::plus
                                           , node2< boost::proto::tag::plus
                                                  , boost::proto::tag::terminal
                                                  , boost::proto::tag::terminal
                                                  >
                                           , boost::proto::tag::terminal
                                           >
                                    >
                      )      >
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(2)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                      )      >
                    );
}

namespace tag
{
  struct mtimes_ : nt2::ext::unspecified_<mtimes_> { typedef nt2::ext::unspecified_<mtimes_> parent; };
}

template<class A0, class A1>
BOOST_FORCEINLINE typename boost::dispatch::meta::call<tag::mtimes_(A0 const&, A1 const&)>::type
mtimes(A0 const& a0, A1 const& a1)
{
  return typename boost::dispatch::make_functor<tag::mtimes_, A0>::type()(a0, a1);
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( ::tag::mtimes_, tag::cpu_, (A0), (scalar_< unspecified_<A0> >)(scalar_< unspecified_<A0> >) )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return a0 * a1;
    }
  };
} }

NT2_TEST_CASE( unspecified )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4, a5;
  scheduler f;

  SCHEDULE( mtimes(a0, a1), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< tag::mtimes_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( assign(a0, mtimes(a1, a2)), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< tag::mtimes_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + mtimes(a1, a2) + a3, f, 2 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< tag::mtimes_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + mtimes(a1 + a2, a3) + a4, f, 3 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< tag::mtimes_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(2)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< boost::proto::tag::plus
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
}

NT2_TEST_CASE( subscript )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3;
  using nt2::sum;
  scheduler f;

  SCHEDULE( assign(a0(a1), sum(a2)), f, 1 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , node2< boost::proto::tag::function
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             , node1< boost::simd::tag::sum_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( assign(a0(a1), mtimes(a2, a3)), f, 2 );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node2< tag::mtimes_
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , node2< boost::proto::tag::function
                                    , boost::proto::tag::terminal
                                    , boost::proto::tag::terminal
                                    >
                             , boost::proto::tag::terminal
                             >
                      )
                    );
}

struct type
{
  template<class X>
  struct apply
  {
    typedef typename X::type type;
  };
};

NT2_TEST_CASE( terminal )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1;
  scheduler f;
  boost::dispatch::identity id;

  SCHEDULE( a0, f, 0 );

  NT2_TEST_EXPR_TYPE( boost::mpl::identity< nt2::meta::call<nt2::tag::schedule_(table<T>&, scheduler const&)>::type >()
                    , type
                    , table<T>&
                    );

  typedef BOOST_DISPATCH_TYPEOF(a0(1)) index;
  NT2_TEST_EXPR_TYPE( boost::mpl::identity< nt2::meta::call<nt2::tag::schedule_(index const&, scheduler const&)>::type >()
                    , type
                    , T&
                    );
}
