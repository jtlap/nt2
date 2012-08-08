//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_SCHEDULE_HPP_INCLUDED

#include <boost/simd/dsl/functions/schedule.hpp>
#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/unpack.hpp>
#include <boost/dispatch/meta/terminal_of_shared.hpp>

namespace boost { namespace simd { namespace meta
{
  /* Same as boost::proto::as_expr, but doesn't do anything if input
   * is already an expression */
  template<class T, class Domain, class Dummy = void>
  struct as_expr
  {
    typedef typename Domain::template as_expr<T>::result_type type;
    static BOOST_FORCEINLINE type call(T& t)
    {
      return typename Domain::template as_expr<T>()(t);
    }
  };

  template<class T, class Domain>
  struct as_expr<T, Domain, typename T::proto_is_expr_>
  {
    typedef T type;
    static BOOST_FORCEINLINE T& call(T& t)
    {
      return t;
    }
  };

} } }

namespace boost { namespace simd { namespace ext
{
  template<class Expr, class State>
  struct unpack_schedule
  {
    typedef dispatch::
            unpack< Expr
                  , dispatch::functor< typename proto::tag_of<Expr>::type, tag::formal_ >
                  , dispatch::with_state<tag::schedule_, State> const
                  >
    transform;

    typedef typename transform::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, State& state) const
    {
      return transform()(expr, dispatch::with_state<tag::schedule_, State>(state));
    }
  };

  //==============================================================================
  // Jump to schedule_assign if assign node
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(F)
                                   , ((node_<A0, boost::simd::tag::assign_, mpl::long_<2> >))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename boost::proto::result_of::child_c<A0&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<A0&, 1>::type child1;
    typedef typename dispatch::meta::call<tag::schedule_assign_(child0, child1, F const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      return schedule_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), f);
    }
  };

  //==============================================================================
  // Elementwise
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, elementwise_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type                       child0;
    typedef typename unpack_schedule<A1, F const>::result_type                       child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F const& f) const
    {
      return boost::simd::assign(unpack_schedule<A0, F const>()(a0, f), unpack_schedule<A1, F const>()(a1, f));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, elementwise_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      return unpack_schedule<A0, F const>()(a0, f);
    }
  };

  //==============================================================================
  // Reduction
  //==============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_assign_, tag::formal_
                                   , (A0)(A1)(T1)(N1)(F)
                                   , (unspecified_<A0>)
                                     ((node_<A1, unspecified_<T1>, N1>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename unpack_schedule<A0, F const>::result_type                       child0;
    typedef typename unpack_schedule<A1, F const>::result_type                       child1;
    typedef typename dispatch::meta::call<tag::assign_(child0, child1)>::type  assigned;
    typedef typename dispatch::meta::result_of<F const(assigned)>::type              result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1, F const& f) const
    {
      return f(boost::simd::assign(unpack_schedule<A0, F const>()(a0, f), unpack_schedule<A1, F const>()(a1, f)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(F)
                                   , ((node_<A0, unspecified_<T>, N>))
                                     (unspecified_<F>)
                                   )
  {
    typedef typename dispatch::meta::semantic_of<A0&>::type             semantic;
    typedef typename dispatch::meta::terminal_of_shared<semantic>::type terminal;
    typedef meta::as_expr<terminal, typename A0::proto_domain>          terminal_expr;
    typedef typename terminal_expr::type                                result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, F const& f) const
    {
      terminal term = dispatch::meta::terminal_of_shared<semantic>::make();
      f(boost::simd::assign( boost::proto::as_child(term)
                           , unpack_schedule<A0, F const>()(a0, f)
                           )
       );
      return terminal_expr::call(term);
    }
  };

} } }

#endif
