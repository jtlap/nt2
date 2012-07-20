//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_PROPER_TANPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_PROPER_TANPI_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/proper_tanpi.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/toolbox/trigonometric/functions/simd/common/impl/trigo.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/sdk/simd/logical.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;
    inline result_type operator()(A0 const&)const 
    {
      return Zero<result_type>();
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 absa0 = nt2::abs(a0);
      bA0 test = le(absa0,  Quarter<A0>()); 
      A0 a = if_else(test, absa0, Half<A0>()-absa0);  
      A0 that = {impl::trig_base<A0,pi_tag,tag::simd_type, clipped_pio4>::tana(a)};
      that = negif(is_ltz(a0), that); 
      return if_nan_else(gt(absa0, Half<A0>()), if_else(test, that, rec(that))); 
    }
  };
} }

#endif
