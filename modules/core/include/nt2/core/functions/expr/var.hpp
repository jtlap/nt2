//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_VAR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_VAR_HPP_INCLUDED

#include <nt2/core/functions/var.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/var.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/wmean.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
 

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0),
                              (ast_<A0>) )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::mean_(A0 const&)>::type T1;
    typedef typename meta::call < tag::bsxfun(tag::minus_ const&, A0 const &, T1)>::type T2;
    typedef typename meta::call < tag::asum2_(T2 const&)>::type T3;
    typedef typename meta::call < tag::multiplies_(value_type, T3)>::type result_type; 


    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      value_type f =  nt2::rec(nt2::size(a0, nt2::firstnonsingleton(a0))-1u); 
      return nt2::multiplies(f, asum2(nt2::bsxfun(tag::minus_, a0, mean(a0)))); 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::mean_(A0 const&)>::type T1;
    typedef typename meta::call < tag::bsxfun(tag::minus_ const&, A0 const &, T1)>::type T2;
    typedef typename meta::call < tag::asum_(T2 const&)>::type T3;
    typedef typename meta::call < tag::multiplies_(value_type, T3)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      value_type f =  nt2::rec(nt2::size(a0, nt2::firstnonsingleton(a0))-size_t(a1==0)); 
      return nt2::multiplies(f, asum2(nt2::bsxfun(tag::minus_, a0, mean(a0)))); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::mean_(A0 const&, A2 const&)>::type T1;
    typedef typename meta::call < tag::bsxfun(tag::minus_ const&, A0 const &, T1)>::type T2;
    typedef typename meta::call < tag::asum_(T2 const&, const &A2)>::type T3;
    typedef typename meta::call < tag::multiplies_(value_type, T3)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      value_type f =  nt2::rec(nt2::size(a0, nt2::firstnonsingleton(a0))-size_t(a1==0)); 
      return nt2::multiplies(f, asum2(nt2::bsxfun(tag::minus_, a0, mean(a0, a2))), a2); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (ast_<A1>)
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::wmean_(A0 const&, A1 const &)>::type T1;
    typedef typename meta::call < tag::bsxfun(tag::minus_ const&, A0 const &, T1)>::type T2;
    typedef typename meta::call < tag::sqr_abs_(T2 const&, const &A2)>::type T3;
    typedef typename meta::call < tag::wmean_(T3)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& a2) const
    {
      value_type f =  nt2::rec(nt2::sum(w(_))); 
      return nt2::wmean(nt2::sqr_abs(nt2::bsxfun(tag::minus_, a0, nt2::wmean(a0, w))), w); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::var_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (ast_<A1>)
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::wmean_(A0 const&, A1 const &, A2 const&)>::type T1;
    typedef typename meta::call < tag::bsxfun(tag::minus_ const&, A0 const &, T1)>::type T2;
    typedef typename meta::call < tag::sqr_abs_(T2 const&)>::type T3;
    typedef typename meta::call < tag::wmean_(T3, const A1&, const A2&)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& a2) const
    {
      value_type f =  nt2::rec(nt2::sum(w(_))); 
      return nt2::wmean(nt2::sqr_abs(nt2::bsxfun(tag::minus_, a0, nt2::wmean(a0, w, a2))), w, a2); 
    }
  };

  
} }

#endif
