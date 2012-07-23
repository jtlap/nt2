//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_STDEV_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_STDEV_HPP_INCLUDED

#include <nt2/core/functions/stdev.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/var.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/size.hpp>
 

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stdev_, tag::cpu_,
                              (A0),
                              (ast_<A0>) )
  {
    typedef typename meta::call < tag::var_(A0 const&)>::type T1;
    typedef typename meta::call < tag::sqrt_(T1)>::type result_type; 


    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sqrt(var(a0)); 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stdev_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call < tag::var_(A0 const&, A1 const&)>::type T1;
    typedef typename meta::call < tag::sqrt_(T1)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::sqrt(var(a0, a1));  
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stdev_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (scalar_<integer_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::call < tag::var_(A0 const&, A1 const&, const & A2)>::type T1;
    typedef typename meta::call < tag::sqrt_(T1)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::sqrt(var(a0, a1, a2));  
    }

    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stdev_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)
                              (ast_<A1>)
                              )
  {
    typedef typename meta::call < tag::var_(A0 const&, A1 const&)>::type T1;
    typedef typename meta::call < tag::sqrt_(T1)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& a2) const
    {
      return nt2::sqrt(var(a0, a1));  
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stdev_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (ast_<A1>)
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::call < tag::var_(A0 const&, A1 const&, const & A2)>::type T1;
    typedef typename meta::call < tag::sqrt_(T1)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& a2) const
    {
      return nt2::sqrt(var(a0, a1, a2));  
    }
  };

  
} }

#endif
