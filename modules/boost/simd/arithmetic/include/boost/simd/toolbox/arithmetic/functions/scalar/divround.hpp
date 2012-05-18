//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_DIVROUND_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/divround.hpp>
#include <boost/simd/include/functions/scalar/round2even.hpp>
#include <boost/simd/include/functions/rdivide.hpp>
#include <boost/simd/include/functions/scalar/iround.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divround_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                        (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (a1) ? static_cast<A0>(round2even(static_cast<double>(a0)/static_cast<double>(a1)))
                : ((a0 > 0) ? Valmax<A0>()
                          : ((a1) ? Valmin<A0>()
                              : Zero<A0>()
                         )
                 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divround_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                        (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::round2even(a0/a1);
    }
  };
} } }

#endif
