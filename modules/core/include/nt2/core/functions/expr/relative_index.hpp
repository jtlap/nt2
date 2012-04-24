//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RELATIVE_INDEX_HPP_INCLUDED

#include <nt2/core/functions/relative_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // When indexing an expression, return the evaluation of said expression
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (ast_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A4::type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& idx, const A1& bi, const A2&, const A3& p, const A4&) const
    {
      return nt2::run(idx,p-bi,meta::as_<result_type>());
    }
  };

  //============================================================================
  // When indexing a scalar, evaluate as a scalar then splat
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)(A3)(A4)
                            , ((expr_ < scalar_< unspecified_<A0> >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename A0::value_type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& idx, const A1&, const A2&, const A3&, const A4&) const
    {
      return nt2::run(idx,0u,meta::as_<result_type>());
    }
  };

  //============================================================================
  // When indexing on _, return the consecutive positions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(Arity)(A1)(A2)(A3)(A4)
                            , ((expr_ < colon_< A0 >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename boost::dispatch::meta::
            scalar_of<typename A4::type>::type  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0&, const A1&, const A2&, const A3& p, const A4&) const
    {
      return p;
    }
  };

  //============================================================================
  // When indexing on _(a, b), return the consecutive positions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_index_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , ((node_<A0, nt2::tag::colon_, boost::mpl::long_<3> >))
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (target_< unspecified_<A4> >)
                            )
  {
    typedef typename boost::dispatch::meta::
            scalar_of<typename A4::type>::type  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(const A0& idx, const A1& bi, const A2&, const A3& p, const A4&) const
    {
      return nt2::run(idx,p-bi,meta::as_<result_type>());
    }
  };
} }

#endif
