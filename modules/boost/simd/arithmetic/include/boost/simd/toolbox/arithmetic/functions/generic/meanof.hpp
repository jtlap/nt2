//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_GENERIC_MEANOF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_GENERIC_MEANOF_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/meanof.hpp>
#include <boost/simd/include/functions/average.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_finite.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/include/functions/shrai.hpp>
#include <boost/simd/include/constants/half.hpp>


//no overflow average for floating numbers


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::meanof_, tag::cpu_,
                                    (A0),
                                    (generic_< floating_<A0> >) (generic_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return 
        if_else(logical_and(logical_and(is_gez(a0*a1),is_finite(a0)),is_finite(a1)), 
                if_else(ge(a1, a0),
                        a0 + (a1-a0)*Half<result_type>(),
                        a1 + (a0-a1)*Half<result_type>()),
                average(a0, a1)
                );
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::meanof_, tag::cpu_,
                                    (A0),
                                    (generic_< arithmetic_<A0> >) (generic_< arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return 
        if_else(is_gez(a0*a1), 
                if_else(ge(a1, a0),
                        a0 + shr((a1-a0), 1),
                        a1 + shr((a0-a1), 1)),
                shrai(a0+a1, 1)
                );
    }
  };  
} } }

#endif
