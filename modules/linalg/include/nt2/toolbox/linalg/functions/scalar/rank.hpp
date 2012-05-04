/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_RANK_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_RANK_HPP_INCLUDED
#include <nt2/include/functions/scalar/rank.hpp>
#include <nt2/include/functions/scalar/svd.hpp>

namespace nt2{ namespace ext 
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)
                                ,((ast_<A0>))
                                )
  {
    typedef size_t result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::details::svd_result<A0>(a0, 'N', 'N').rank(); 
    }
  };
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)(A1)
                                ,((ast_<A0>))
                                (scalar_<floating_<A1 > >)
                                )
  {
    typedef size_t result_type; 
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::details::svd_result<A0>(a0, 'N', 'N').rank(a1); 
    }
  };

} }


#endif
