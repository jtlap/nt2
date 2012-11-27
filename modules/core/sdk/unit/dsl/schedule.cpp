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

#include "as_node.hpp"
#include "schedule.hpp"

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

  BOOST_DISPATCH_IMPLEMENT( (boost)(dispatch)(meta)
                          , nt2::tag::run_assign_, tag::cpu_
                          , (A0)(T0)(N0)(A1)
                          , ((node_<A0, unspecified_<T0>, N0, nt2::container::domain>))
                            ((node_<A1, ::tag::red_, mpl::long_<1>, nt2::container::domain>))
                          )
  {
    typedef A0& result_type;
    result_type operator()(A0& a0, A1&) const
    {
      return a0;
    }
  };
} } }

// Scheduling now done at construction
#if 0
NT2_TEST_CASE( reduction )
{
  using boost::mpl::_;
  using nt2::table;
  typedef double T;

  table<T> a0, a1, a2, a3, a4, a5;
  scheduler f;

  SCHEDULE( red(a0), f, 1u, boost::proto::tag::terminal );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                   , boost::proto::tag::terminal
                   >
             )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                          , boost::proto::tag::terminal
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                          , boost::proto::tag::terminal
                          >
                   , boost::proto::tag::terminal
                   >
             )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                          , boost::proto::tag::terminal
                          >
                   , boost::proto::tag::terminal
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                             , boost::proto::tag::terminal
                             , node1< tag::red_
                                    , node2< boost::proto::tag::plus
                                           , node2< boost::proto::tag::plus
                                                  , boost::proto::tag::terminal
                                                  , boost::proto::tag::terminal
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
                          , boost::proto::tag::terminal
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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
                            , boost::proto::tag::terminal
                            >
                    , boost::simd::tag::box_
                    >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
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

  SCHEDULE( nt2::assign(a0(a1 + red(a2)), a3 + red(a4)), f, 2u
          , ( node2< boost::proto::tag::assign
                    , node3 < boost::proto::tag::function
                            , boost::proto::tag::terminal
                            , node1 < nt2::tag::aggregate_
                                    , node2 < boost::proto::tag::plus
                                            , boost::proto::tag::terminal
                                            , boost::proto::tag::terminal
                                            >
                                    >
                            , boost::simd::tag::box_
                            >
                   , node2< boost::proto::tag::plus
                          , boost::proto::tag::terminal
                          , boost::proto::tag::terminal
                          >
                   >
            )
          );
  NT2_TEST_TYPE_INFO( *f.trees.at(0)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
  NT2_TEST_TYPE_INFO( *f.trees.at(1)
                    , ( node2< boost::proto::tag::assign
                             , boost::proto::tag::terminal
                             , node1< tag::red_
                                    , boost::proto::tag::terminal
                                    >
                             >
                      )
                    );
}
#endif

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
  using nt2::memory::container_ref;
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
                                                                           , boost::proto::term< container_ref< container<T, S> > >
                                                                           , 0
                                                                           >
                                                 ,  container<T, S>&
                                                 >
                      )
                    );
}
