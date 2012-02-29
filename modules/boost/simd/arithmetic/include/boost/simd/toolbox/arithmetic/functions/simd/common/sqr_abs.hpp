//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SQR_ABS_HPP_INCLUDED
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/abss.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/is_greater_equal.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqr_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return muls(a0, a0); //TODO perhaps optimize but this involves split
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqr_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<ints64_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        A0 aa0 =  select(is_nez(a0), boost::simd::abss(a0), One<A0>()); 
        A0 z = Valmax<A0>()/aa0;
        return select( ge(z, aa0), sqr(a0), Valmax<A0>()); 
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqr_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return sqr(a0); }
  };
} } }


#endif
