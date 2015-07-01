//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          REALLOGistributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_REALLOG_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_REALLOG_HPP_INCLUDED
#include <nt2/exp_derivatives/functions/reallog.hpp>
#include <nt2/exp_derivatives/functions/log.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_negative.hpp>


namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( reallog_, nt2::tag::cpu_
                            , (order)(A0)
                            , (unspecified_<order>)
                              (generic_<floating_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const order&
                                            , const A0& u) const
    {
      return if_allbits_else(is_negative(u), log(order(), u));
    }
  };
} }


#endif
