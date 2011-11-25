//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXT_HPP_INCLUDED
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/frexp.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_finite.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>
#include <boost/simd/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/oneplus.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::next_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return a0+One<A0>();
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::next_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type iA0;
      //decommenting the following lines make clang works with the ieee.ulp.simd.unit      
//       std::cout << "---------------------------------------" << a0 << std::endl;
//       std::cout << "a0                                     " << a0 << std::endl;
//       std::cout << "bitinteger(a0)                         " << bitinteger(a0)<< std::endl;
//       std::cout << "oneplus(bitinteger(a0))                " << oneplus(bitinteger(a0))<< std::endl;
//       std::cout << "bitfloating(oneplus(bitinteger(a0)))   " << bitfloating(oneplus(bitinteger(a0)))<< std::endl;
//       std::cout << "---------------------------------------" << a0 << std::endl;
       return select(eq(a0, Inf<A0>()), a0,  bitfloating(One<iA0>()+bitinteger(a0)));
    }
  };
} } }
#endif
