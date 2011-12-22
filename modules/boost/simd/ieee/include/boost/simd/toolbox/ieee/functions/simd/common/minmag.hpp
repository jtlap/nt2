//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_MINMAG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_MINMAG_HPP_INCLUDED
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/abs.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minmag_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return select(lt(abs(a0), boost::simd::abs(a1)), a0, a1);
    }
  };
} } }


#endif
