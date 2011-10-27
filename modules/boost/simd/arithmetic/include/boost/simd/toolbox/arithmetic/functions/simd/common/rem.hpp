//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REM_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/rem.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/selsub.hpp>
#include <boost/simd/include/functions/divfix.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>
#include <boost/simd/include/functions/if_nan_else.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rem_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return selsub(is_nez(a1), a0,idivfix(a0,a1)*a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rem_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      //      return b_or(is_invalid(a1), selsub(is_nez(a1), a0, tofloat(idivfix(a0,a1))*a1));
      return if_nan_else(is_invalid(a1),
                      selsub(is_nez(a1), a0, divfix(a0,a1)*a1));
 
    }
  };
} } }

#endif
