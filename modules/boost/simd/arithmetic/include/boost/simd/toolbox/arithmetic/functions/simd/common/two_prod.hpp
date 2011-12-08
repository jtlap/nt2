//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_PROD_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/two_split.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/logical_or.hpp>
#include <boost/simd/include/functions/if_zero_else.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/toolbox/arithmetic/functions/two_prod.hpp>
#include <boost/fusion/tuple.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_prod_, tag::cpu_,
                          (A0)(X),
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                         )
  {
    typedef int result_type;
    inline result_type operator()(A0 const& a,A0 const& b,
                                  A0 & r0,A0 & r1) const
    {
      typedef typename meta::as_logical<A0>::type bA0;
      r0 = a*b;
      A0 a1, a2, b1, b2; 
      bA0 isinf = logical_and(logical_or(is_inf(b), is_inf(a)), is_inf(r0)); 
      two_split(a, a1, a2);
      two_split(b, b1, b2);
      r1 = if_zero_else(isinf, a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2));
      return 0;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_prod_, tag::cpu_,
                          (A0)(X),
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                          ((simd_<floating_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1,A0 & a3) const
    {
      A0 a2;
      two_prod(a0, a1, a2, a3); 
      return a2;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_prod_, tag::cpu_,
                           (A0)(X),
                           ((simd_<floating_<A0>,X>))
                           ((simd_<floating_<A0>,X>))
                          )
  {
    typedef typename boost::fusion::tuple<A0,A0> result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      two_prod(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  };
} } }
#endif
