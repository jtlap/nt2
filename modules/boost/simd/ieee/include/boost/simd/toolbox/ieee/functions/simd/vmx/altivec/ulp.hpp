//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_VMX_ALTIVEC_ULP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_VMX_ALTIVEC_ULP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/include/constants/zero.hpp> 
#include <boost/simd/include/constants/nbmantissabits.hpp> 
#include <boost/simd/include/constants/mindenormal.hpp> 
#include <boost/simd/include/constants/smallestposval.hpp> 
#include <boost/simd/toolbox/ieee/functions/simd/common/details/ulp.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulp_, simd::tag::altivec_
                                   , (A0)
                                   , ((simd_<floating_<A0>, simd::tag::altivec_>))
                                   )
  {
    typedef A0 result_type;
    typedef typename dispatch::meta::as_integer<A0>::type in_t;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const A0 x   = simd::abs(a0);
      const in_t n = simd::Nbmantissabits<A0>();
      const A0 res = simd::if_else( simd::is_eqz(x)
                                  , simd::Mindenormal<A0>()
                                  , simd::if_else( simd::is_less(x,simd::Smallestposval<A0>())
                                                 , simd::ldexp(details::ulp(simd::ldexp(x,n)),-n)
                                                 , details::ulp(x)
                                                 )
                                  );
      return res;
    }
  };

} } }

#endif
#endif