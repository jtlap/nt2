//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ASINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ASINH_HPP_INCLUDED
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/sdk/simd/logical.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asinh(tofloat(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 xx, sign;
      xx =  nt2::abs(a0);
      sign =  bitofsign(a0);
      const A0 x2            = nt2::sqr(xx);
      return b_xor(sel(is_equal(xx, Inf<A0>()),
		       xx, 
		       nt2::log1p(xx+x2/nt2::oneplus(nt2::sqrt(nt2::oneplus(x2))))
		       ),
		   sign
		   );
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0; 
      A0 x = nt2::abs(a0);
      bA0 lthalf = lt(x,Half<A0>());
      A0 x2 = nt2::sqr(x);
      A0 z = Zero<A0>();
      uint32_t nb;
      if( ( nb = nbtrue(lthalf)) > 0)
        {
          z = madd(single_constant<A0,(0x3ca4d6e6) >(),  x2, single_constant<A0,(0xbd2ee581)>());
          z = madd(x2, z,  single_constant<A0,(0x3d9949b1)>());
          z = madd(x2, z,  single_constant<A0,(0xbe2aa9ad)>())* x2 * x + x;
          if(nb >= meta::cardinal_of<A0>::value) return  b_xor(z, bitofsign(a0));
        }
      A0 zz = log(x+sqrt(oneplus(x2)));
      return b_xor(select(lthalf, z, zz), bitofsign(a0));
    }
  };
} }


#endif
