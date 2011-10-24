//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_NEXTPOW2_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/functions/frexp.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/minusone.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::nextpow2_, tag::cpu_,
                          (A0),
                          (scalar_ < arithmetic_<A0> > )
                         )
  {
    typedef typename dispatch::meta::as_integer<typename dispatch::meta::result_of<dispatch::meta::floating(A0)>::type, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::nextpow2(tofloat(a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::nextpow2_, tag::cpu_,
                          (A0),
                          (scalar_ < floating_<A0> > )
                         )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 m;
      result_type p;
      boost::simd::frexp(boost::simd::abs(a0), m, p);
      std::cout << "m " <<  m <<  " p " << p << std::endl; 
      return (m == Half<A0>())  ? minusone(p) :  p;
    }
  };
} } }
#endif
