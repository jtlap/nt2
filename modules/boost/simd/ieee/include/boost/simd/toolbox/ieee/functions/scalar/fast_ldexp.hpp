//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FAST_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_FAST_LDEXP_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/fast_ldexp.hpp>
#include <boost/simd/include/constants/ldexpmask.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/functions/scalar/bitwise_andnot.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_ldexp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
       return (a1>=0)?(a0<<a1):(a0>>a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_ldexp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type int_type;
      // clear exponent in x
      A0 const x(b_andnot(a0, Ldexpmask<A0>()));
      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += int_type(a1) << Nbmantissabits<A0>();
      return b_or(x, e);
    }
  };
} } }


#endif
