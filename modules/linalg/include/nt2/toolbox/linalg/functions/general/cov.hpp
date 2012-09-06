//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_COV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_COV_HPP_INCLUDED

#include <nt2/include/functions/cov.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/zeros.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)(scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call<tag::center_(A0 const&, size_t)>::type T1; 
    typedef typename meta::call<tag::conj_(T1)>::type T2; 
    typedef typename meta::call<tag::trans_(T2)>::type T3;
    typedef typename meta::call<tag::mtimes_(T3, T1)>::type T4;
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::multiplies_(T4,value_type)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const & a1) const
    {
      T1 a0_c = nt2::center(a0, size_t(1));
      value_type n = nt2::size(a0, 1);
      std::cout << "n " << n << std::endl;
      NT2_DISPLAY(a0);
      NT2_DISPLAY(nt2::mtimes(trans(conj(a0)), a0)); 
      NT2_DISPLAY(a0_c); 
      value_type f = (n <= One<value_type>())? One<value_type>() : nt2::rec(n-(a1?value_type(0):value_type(1)));
      std::cout << "f " << f << std::endl; 
      NT2_DISPLAY(trans(conj(a0_c)));
      NT2_DISPLAY(nt2::mtimes(trans(conj(a0_c)), a0_c));
      NT2_DISPLAY(nt2::multiplies(nt2::mtimes(trans(conj(a0_c)), a0_c), f));
      std::cout << "why the return of cov (just following) is not identical to this (just above) result"<< std::endl; 
      return  nt2::multiplies(nt2::mtimes(trans(conj(a0_c)), a0_c), f); 
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0),
                              (ast_<A0>)
                              )
  {
    typedef typename meta::call<tag::center_(A0, size_t)>::type T1; 
    typedef typename meta::call<tag::conj_(T1)>::type T2; 
    typedef typename meta::call<tag::trans_(T2)>::type T3;
    typedef typename meta::call<tag::mtimes_(T3, T1)>::type T4;
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::multiplies_(T4, value_type)>::type result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      T1 a0_c = nt2::center(a0, size_t(1));
      value_type n = nt2::size(a0, 1); 
      value_type f = (n <= One<value_type>())? One<value_type>() : nt2::rec(n-1); 
      return  nt2::multiplies(nt2::mtimes(trans(conj(a0_c)), a0_c), f); 
    }   
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (ast_<A0>)(ast_<A1>)
                              )
  {
    typedef typename meta::call<tag::function_(A0 const&, tag::colon_)>::type T0;
    typedef typename meta::call<tag::function_(A1 const&, tag::colon_)>::type T1;
    typedef typename meta::call<tag::horzcat_(T0, T1)>::type H;
    typedef typename meta::call<tag::cov_(H)>::type result_type; 
    //     typedef typename A0::value_type value_type;
    //     typedef typename A0::index_type index_type; 
    //     typedef table<value_type, index_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::cov(horzcat(a0(_), a1(_))); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)(ast_<A1>)(scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename A0::index_type index_type; 
    typedef table<value_type, index_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1, const A2& a2) const
    {
      return nt2::cov(nt2::horzcat(a0(_), a1(_)), a2); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0),
                              (scalar_<floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return Zero<A0>(); 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<floating_<A0> >)
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef A0 result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const &) const
    {
      return Zero<A0>(); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<floating_<A0> >)
                              (scalar_<floating_<A1> >)
                              )
  {
    typedef A0 value_type;
    typedef table<value_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const &) const
    {
      return zeros(2, 2, meta::as_<A0>()); 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cov_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<floating_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
    {
    typedef A0 value_type;
    typedef table<value_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const&, A1 const &,  A2 const &) const
    {
      return zeros(2, 2, meta::as_<A0>()); 
    }
  };
  
} }

#endif
