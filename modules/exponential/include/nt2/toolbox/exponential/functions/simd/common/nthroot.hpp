//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_NTHROOT_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_NTHROOT_HPP_INCLUDED

#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nthroot_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<integer_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::nthroot(tofloat(a0), a1);
    }
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nthroot_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_logical<A0>::type  bA0; 
      typedef typename meta::as_logical<A1>::type  bA1; 
      A0 x =  nt2::abs(a0);
      A0 aa1 = tofloat(a1);
      A0 y =nt2::pow(x,rec(aa1));
      bA1 nul_a1 = is_eqz(a1);
      A0 a11 = tofloat(a1-select(nul_a1, Mone<A1>(), Zero<A1>())); 
      y = seladd( logical_or(is_nez(y), nul_a1)
                , y
                , -(pow(y, aa1) - x)/(aa1* pow(y, sub(a11, One<A0>())))
                );

      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      bA0 invalid = logical_and(is_ltz(a0), is_even(a1)); 
      return  select( is_eqz(a0),
                      Zero<A0>(), 
                      select( invalid,
                              Nan<A0>(),   
                              sel ( is_eqz(aa1)
                                  , One<A0>()
                                  , sel ( l_or(eq(a1, One<A1>()), is_inf(a0))
                                        , a0
                                        , b_or(y, bitofsign(a0))
                                        )
                                  )
                            )
                    );
    }
  };
} }

#endif
