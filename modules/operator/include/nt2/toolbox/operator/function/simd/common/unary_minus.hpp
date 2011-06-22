//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_NEG_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_NEG_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/bitwise_xor.hpp>
#include <nt2/include/functions/minus.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::unary_minus_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return Zero<A0>() - a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::unary_minus_, tag::cpu_, (A0)(X)
                            , ((simd_<real_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return b_xor(Mzero<A0>(),a0);
    }
  };
} }

#endif
