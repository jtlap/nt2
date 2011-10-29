//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELSUB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_SELSUB_HPP_INCLUDED

#include <boost/simd/toolbox/boolean/functions/selsub.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/simd/sdk/meta/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <iostream>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::selsub_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                        , boost::simd::meta::cardinal_of<A1>
                                                        >
                                  )
                                , ((simd_<logical_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
//       std::cout << "icitt" << std::endl;
//       std::cout << "a0 " << a0 <<  std::endl;
//       std::cout << "a1 " << a1 <<  std::endl;
//       std::cout << "a2 " << a2 <<  std::endl;
//       std::cout << "if_else_zero(a0, a2) " << if_else_zero(a0, a2)<<  std::endl;
//     return a1 - if_else_zero(a0, a2);
     A1 tmp =  a1;
     tmp -=  if_else_zero(a0, a2);
     return tmp; 
    }
  };
} } }

#endif
