//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_POSMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_POSMAX_HPP_INCLUDED
#include <boost/simd/include/functions/posmax.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/nbtrue.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/arg.hpp>
#include <boost/simd/include/functions/at_i.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::posmax_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef boost::simd::int32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::scalar_of<rtype>::type stype;
      typedef typename meta::as_logical<rtype>::type ltype;
      rtype absa0 = abs(a0); 
      boost::simd::int32_t tmp = posmax(absa0);
      ltype test = eq(absa0, absa0[tmp]); 
        if (nbtrue(test) > 1)
          {
            rtype z = if_else(test, arg(a0), Minf<rtype>);
            return posmax(z);
          }
      return tmp; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::posmax_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef boost::simd::int32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return posmax(abs(a0));
    }
  };
  
} } }

#endif
