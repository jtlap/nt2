//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/core/functions/tie.hpp>
#include <nt2/include/functions/assign.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(N0)(A1)
                            , ((node_<A0, nt2::tag::tie_, N0>))
                              ((ast_<A1>))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& ) const
    {
      //========================================================================
      //              ****NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION****
      // If you trigger this static assertion, an invalid expression has been
      // assigned to a tie expression.
      //              ****NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (sizeof(A0) == 0)
                          , NT2_INCORRECT_RHS_FOR_TIE_EXPRESSION
                          , (A1)
                          );
      return a0;
    }
  };
} }

#endif
