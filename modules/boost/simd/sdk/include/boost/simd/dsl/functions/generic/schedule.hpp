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
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/proto/unpack.hpp>

//==============================================================================
// Splitting of non-combinable expressions
//==============================================================================

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(A1)
                                   , ((node_<A0, elementwise_<T>, N>))
                                     (ast_<A1>)
                                   )
  {
    typedef proto::
    unpack< proto::
            call< dispatch::
                  functor< typename proto::tag_of<A0>::type, tag::formal_ >
                > ( proto::
                    when< proto::_
                        , proto::call< typename dispatch::
                                       make_functor<tag::schedule_, A0>
                                                    ::type ( proto::_expr
                                                           , proto::_state
                                                           )
                                     >
                        >
                  )
          >
    transform;

    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_>
    struct result<This(A0_, A1_)>
      : transform::template result<transform(A0_, A1_)>
    {
    };

    template<class A0_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1&)>::type
    operator()(A0_& a0, A1& a1) const
    {
      return transform()(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(T)(N)(A1)
                                   , ((node_<A0, unspecified_<T>, N>))
                                     (ast_<A1>)
                                   )
  {
    typedef proto::
    unpack< proto::
            call< dispatch::
                  functor< typename proto::tag_of<A0>::type, tag::formal_ >
                > ( proto::call< typename dispatch::
                                 make_functor<tag::schedule_, A0>::type
                               >
                  )
          >
    transform;

    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_>
    struct result<This(A0_, A1_)>
    {
      typedef typename transform::template result<transform(A0_)>::type subast;
      typedef typename dispatch::meta::call<tag::evaluate_(subast, A1_)>::type type;
    };

    template<class A0_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1&)>::type
    operator()(A0_& a0, A1& a1) const
    {
      return evaluate(transform()(a0), a1);
    }
  };

  // Do nothing if assignment present
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)
                                   , ((node_<A0, boost::simd::tag::assign_, mpl::long_<2> >))
                                   )
  {
    typedef typename boost::proto::result_of::child_c<A0 const&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<A0 const&, 1>::type child1;
    typedef typename dispatch::meta::call<tag::schedule_(child1, child0)>::type scheduled;
    typedef typename dispatch::meta::call<tag::assign_(child0, scheduled)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return assign(boost::proto::child_c<0>(a0), schedule(boost::proto::child_c<1>(a0), boost::proto::child_c<0>(a0)));
    }
  };

  // Add assignment if not present
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)
                                   , (ast_<A0>)
                                   )
  {
    typedef typename dispatch::meta::semantic_of<A0>::type semantic;
    typedef typename dispatch::meta::strip<typename dispatch::meta::terminal_of<semantic>::type>::type terminal;
    typedef typename dispatch::meta::call<tag::schedule_(A0 const&, terminal&)>::type scheduled;
    typedef typename dispatch::meta::call<tag::assign_(terminal&, scheduled)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      terminal term;
      return assign(term, schedule(a0, term));
    }
  };

  // terminal cases
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)
                                   , ((node_<A0, boost::simd::tag::terminal_, mpl::long_<0> >))
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_>
    struct result<This(A0_)>
      : dispatch::meta::as_ref<A0_>
    {
    };

    template<class A0_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&)>::type
    operator()(A0_& a0) const
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::schedule_, tag::formal_
                                   , (A0)(A1)
                                   , ((node_<A0, boost::simd::tag::terminal_, mpl::long_<0> >))
                                     (ast_<A1>)
                                   )
  {
    template<class Sig>
    struct result;

    template<class This, class A0_, class A1_>
    struct result<This(A0_, A1_)>
      : dispatch::meta::as_ref<A0_>
    {
    };

    template<class A0_>
    BOOST_DISPATCH_FORCE_INLINE typename result<implement(A0_&, A1&)>::type
    operator()(A0_& a0, A1&) const
    {
      return a0;
    }
  };

} } }

#endif
