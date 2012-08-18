//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SX_HPP_INCLUDED

#include <nt2/core/functions/sx.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/tsxfun.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              )
  {
    typedef typename meta::call<tag::bsxfun_(nt2::functor<A0>,const A1&,const A2&)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1, A2 const& a2) const
    {
      return bsxfun(nt2::functor<A0>(), a1, a2);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              )
  {
    typedef typename meta::call<tag::tsxfun_(nt2::functor<A0>,const A1&,const A2&,const A3&)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const& a1,
                                             A2 const& a2, A3 const& a3) const
    {
      return tsxfun(nt2::functor<A0>(), a1, a2, a3);
    }
  };
} }

#endif
