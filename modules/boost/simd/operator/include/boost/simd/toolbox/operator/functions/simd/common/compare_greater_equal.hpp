//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_COMPARE_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_COMPARE_GREATER_EQUAL_HPP_INCLUDED

#include <boost/simd/include/functions/compare_less.hpp>

namespace boost { namespace simd { namespace ext
{
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_greater_equal_,
//                                      tag::cpu_, (X)(A0)
//                                    , ((simd_<real_<A0>,X>))
//                                      ((simd_<real_<A0>,X>))
//                                    )
//   {
//     typedef bool result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       for(std::size_t i=0;i<meta::cardinal_of<A0>::value;++i)
//       {
//         if (a0[i] > a1[i])  return true;
//         if (a1[i] > a0[i])  return false;
//         if (a1[i] != a0[i])  return false;
//       }
//       return true; 	
//     }
//   };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_greater_equal_,
                                     tag::cpu_, (X)(A0)
                                   , ((simd_<arithmetic_<A0>,X>))
                                     ((simd_<arithmetic_<A0>,X>))
                                   )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return !(a0<a1); }
  };
} } }

#endif
