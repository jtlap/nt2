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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/proto/debug.hpp>

template<class T, class N0>
struct node1 {};

template<class T, class N0, class N1>
struct node2 {};

template<class T, class N0, class N1, class N2>
struct node3 {};

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

template<class Tag, class Expr>
struct as_node_impl<Tag, Expr, 3>
{
  typedef node3<Tag, typename as_node< typename boost::proto::result_of::child_c<Expr, 0>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 1>::type >::type
                   , typename as_node< typename boost::proto::result_of::child_c<Expr, 2>::type >::type
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

    typedef typename boost::mpl::eval_if< boost::is_same<typename boost::proto::tag_of<stripped>::type, boost::proto::tag::assign>
                                        , boost::proto::result_of::child_c<stripped const&, 0>
                                        , boost::dispatch::meta::terminal_of<semantic>
                                        >::type type;
  };

  template<class T>
  typename boost::disable_if< boost::is_same<typename boost::proto::tag_of<T>::type, boost::proto::tag::assign>
                            , typename result<scheduler(T const&)>::type
                            >::type
  operator()(T const&) const
  {
    trees.push_back(&typeid(typename as_node<T>::type));

    static typename boost::remove_reference<typename result<scheduler(T const&)>::type>::type r;
    return r;
  }

  template<class T>
  typename boost::enable_if< boost::is_same<typename boost::proto::tag_of<T>::type, boost::proto::tag::assign>
                           , typename result<scheduler(T const&)>::type
                           >::type
  operator()(T const& t) const
  {
    trees.push_back(&typeid(typename as_node<T>::type));

    return boost::proto::child_c<0>(t);
  }

  mutable std::vector<std::type_info const*> trees;
};

#define SCHEDULE(Expr, f, N, Ret)                                              \
f.trees.clear();                                                               \
std::cout << "\nScheduling `" << NT2_PP_STRINGIZE(Expr) << "`\n";              \
NT2_TEST_EXPR_TYPE( nt2::schedule(Expr, f), as_node<boost::mpl::_>, Ret );     \
NT2_TEST_EQUAL( f.trees.size(), N )                                            \
/**/

NT2_TEST_CASE( element_wise )
{
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4;
  using nt2::schedule;
  scheduler f;

  SCHEDULE( nt2::assign(a0, a1), f, 0u
          , ( node2< boost::proto::tag::assign
                   , boost::proto::tag::terminal
                   , boost::proto::tag::terminal
                   >
            )
          );

  SCHEDULE( nt2::assign(a0, a1 + a2), f, 0u
          , ( node2< boost::proto::tag::assign
                   , boost::proto::tag::terminal
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::terminal
                          >
                   >
            )
          );

  SCHEDULE( nt2::assign(a0, nt2::plus(a1, a2)), f, 0u
          , ( node2< boost::proto::tag::assign
                   , boost::proto::tag::terminal
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::terminal
                          >
                   >
            )
          );

  SCHEDULE( nt2::assign(a0, a1 + a2 + a3), f, 0u
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

  SCHEDULE( a0 + a1, f, 0u
          , ( node2< boost::proto::tag::plus
                   , boost::proto::tag::terminal
                   , boost::proto::tag::terminal
                   >
            )
          );

  SCHEDULE( a0 + a1 + a2, f, 0u
          , ( node2< boost::proto::tag::plus
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::terminal
                          >
                   , boost::proto::tag::terminal
                   >
            )
          );
}

namespace tag
{
  struct red_ : boost::dispatch::meta::unspecified_<red_> { typedef boost::dispatch::meta::unspecified_<red_> parent; };
}

template<class A0> BOOST_FORCEINLINE
typename boost::dispatch::meta::call<tag::red_(A0 const&)>::type
red(A0 const& a0)
{
  return typename boost::dispatch::make_functor<tag::red_, A0>::type()(a0);
}

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_IMPLEMENT( (boost)(dispatch)(meta)
                          , ::tag::red_, tag::cpu_
                          , (A0)
                          , (scalar_< unspecified_<A0> >)
                          )
  {
    typedef A0 result_type;
    result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} } }

NT2_TEST_CASE( reduction )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4, a5;
  scheduler f;

  SCHEDULE( red(a0), f, 1u, boost::proto::tag::dereference );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( nt2::assign(a0, red(a1)), f, 1u, boost::proto::tag::terminal );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + red(a1), f, 1u
          , ( node2< boost::proto::tag::plus
                   , boost::proto::tag::terminal
                   , boost::proto::tag::dereference
                   >
             )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( nt2::assign(a0, a1 + red(a2)), f, 1u
          , ( node2< boost::proto::tag::assign
                   , boost::proto::tag::terminal
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::dereference
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + red(a1 + a2) + a3, f, 1u
          , ( node2< boost::proto::tag::plus
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::dereference
                          >
                   , boost::proto::tag::terminal
                   >
             )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    >
                             >
                      )
                    );

  SCHEDULE( a0 + red(a1 + red(a2 + a3) + a4) + a5, f, 2u
          , ( node2< boost::proto::tag::plus
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::dereference
                          >
                   , boost::proto::tag::terminal
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , node2< boost::proto::tag::plus
                                           , boost::proto::tag::terminal
                                           , boost::proto::tag::terminal
                                           >
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , node2< boost::proto::tag::plus
                                           , node2< boost::proto::tag::plus
                                                  , boost::proto::tag::terminal
                                                  , boost::proto::tag::dereference
                                                  >
                                           , boost::proto::tag::terminal
                                           >
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

  table<T> a0, a1, a2, a3, a4;
  scheduler f;

  SCHEDULE( nt2::assign(a0(a1), red(a2)), f, 1u
          , ( node3 < boost::proto::tag::function
                    , boost::proto::tag::terminal
                    , node1<nt2::tag::aggregate_,boost::proto::tag::terminal>
                    , boost::simd::tag::box_
                    >
            )
          );

  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , node3< boost::proto::tag::function
                                    , boost::proto::tag::terminal
                                    , node1 < nt2::tag::aggregate_
                                            , boost::proto::tag::terminal
                                            >
                                    , boost::simd::tag::box_
                                    >
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
          );

  SCHEDULE( nt2::assign(a0(a1), a2 + red(a3)), f, 1u
          , ( node2< boost::proto::tag::assign
                   , node3< boost::proto::tag::function
                          , boost::proto::tag::terminal
                          , node1 < nt2::tag::aggregate_
                                  , boost::proto::tag::terminal
                                  >
                          , boost::simd::tag::box_
                          >
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::dereference
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( nt2::assign(a0(red(a1)), red(a2)), f, 2u
          , ( node3 < boost::proto::tag::function
                    , boost::proto::tag::terminal
                    , node1 < nt2::tag::aggregate_
                            , boost::proto::tag::dereference
                            >
                    , boost::simd::tag::box_
                    >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , node3< boost::proto::tag::function
                                    , boost::proto::tag::terminal
                                    , node1 < nt2::tag::aggregate_
                                            , boost::proto::tag::dereference
                                            >
                                    , boost::simd::tag::box_
                                    >
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );

  SCHEDULE( nt2::assign(a0(a1 + red(a2)), a3 + red(a4)), f, 2u
          , ( node2< boost::proto::tag::assign
                    , node3 < boost::proto::tag::function
                            , boost::proto::tag::terminal
                            , node1 < nt2::tag::aggregate_
                                    , node2 < boost::proto::tag::plus
                                            , boost::proto::tag::terminal
                                            , boost::proto::tag::dereference
                                            >
                                    >
                            , boost::simd::tag::box_
                            >
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::dereference
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::dereference
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
}

struct child0
{
  template<class X>
  struct apply
  {
    typedef typename boost::proto::result_of::child_c<X, 0>::value_type type;
  };
};

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
  using nt2::memory::container;
  typedef double T;
  typedef nt2::settings S(nt2::_4D);

  table<T, S> a0, a1;
  scheduler f;

  SCHEDULE( a0, f, 0u, boost::proto::tag::terminal );

  NT2_TEST_EXPR_TYPE( boost::mpl::identity< nt2::meta::call<nt2::tag::schedule_(table<T, S>&, scheduler const&)>::type >()
                    , type
                    , (table<T, S>&)
                    );

  NT2_TEST_EXPR_TYPE( nt2::schedule(nt2::assign(a0, a1), f)
                    , child0
                    , (nt2::container::expression< boost::proto::basic_expr< boost::proto::tag::terminal
                                                                           , boost::proto::term< container<T, S>& >
                                                                           , 0
                                                                           >
                                                 ,  container<T, S>&
                                                 >
                      )
                    );
}
