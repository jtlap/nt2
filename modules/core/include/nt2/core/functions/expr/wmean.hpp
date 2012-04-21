//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MEAN_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/wmean.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
 

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_,
                              (A0),
                              (ast_<A0>)
                              (ast_<A1>)
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::bsxfun(tag::multiplies_, const A0&, const A1&)>::type T1;
    typedef typename meta::call < tag::sum_(T1 const&)>::type T2;
    typedef typename meta::call < tag::multiplies_(value_type, T1)>::type result_type; 


    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& w) const
    {
      value_type f =  rec(nt2::sum(w(_))); 
      return nt2::multiplies(f, nt2::sum(nt2::bsxfun(tag::multiplies_(), a0, w)));
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (ast_<A1>)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call < tag::bsxfun(tag::multiplies_, const A0&, const A1&)>::type T1;
    typedef typename meta::call < tag::sum_(T1 const&, A1 const&)>::type T2;
    typedef typename meta::call < tag::multiplies_(value_type, T1)>::type result_type; 

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      value_type f =  rec(nt2::sum(w(_))); 
      return nt2::multiplies(f, nt2::sum(nt2::bsxfun(tag::multiplies_(), a0, w), a1));
    }
  };
} }

#endif
