//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_SVD_SOLVE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_SOLVERS_SVD_SOLVE_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/svd_solve.hpp>
#include <nt2/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/toolbox/linalg/functions/details/svd_solve.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::solvers::svd_solve_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (ast_<A1>)
                            )
  {
    typedef typename meta::strip<A0>::type                              base_t;
    typedef typename base_t::value_type                                value_t;
    typedef typename meta::as_real<value_t>::type                     bvalue_t; 
    typedef typename base_t::settings_type                          settings_t;
    typedef details::svd_solve_result< table<value_t,settings_t> > result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a,
                                             A1 const& b) const
    {
      BOOST_ASSERT_MSG(ofsameheight(a, b),
                       "a and b have different heights");
      result_type that(a, b, bvalue_t(-1));
      return that;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::solvers::svd_solve_, tag::cpu_
                              , (A0)(A1)(IP)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (unspecified_< IP >)
                              )
  {
    typedef typename meta::strip<A0>::type                              base_t;
    typedef typename base_t::value_type                                value_t;
    typedef typename meta::as_real<value_t>::type                     bvalue_t; 
    typedef details::svd_solve_result<A0&>                         result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0& a,
                                             A1 const& b,
                                             IP const&) 
    {
      BOOST_ASSERT_MSG(ofsameheight(a, b),
                       "a and b have different heights");
      result_type that(a, b, bvalue_t(-1));
      return that;
    }
  };
} }

#endif
