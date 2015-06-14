//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPER_DERIVATIVES_FUNCTIONS_GENERIC_D_TANH_HPP_INCLUDED
#define NT2_HYPER_DERIVATIVES_FUNCTIONS_GENERIC_D_TANH_HPP_INCLUDED
#include <nt2/hyper_derivatives/functions/d_tanh.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>


namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( d_tanh_, tag::cpu_
                            , (A0)
                            , (generic_<unspecified_<A0>>)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& u) const
    {
      return  oneminus(sqr(tanh(u)));;
    }
  };
} }


#endif
