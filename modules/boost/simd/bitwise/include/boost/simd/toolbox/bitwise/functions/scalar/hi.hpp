//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_HI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_HI_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/hi.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::hi_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )

  {
    typedef typename dispatch::meta::downgrade <
             typename dispatch::meta::as_integer<A0,unsigned>::type
                      >::type  result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type type;
      BOOST_STATIC_CONSTANT(type, shift   = sizeof(type)*4);
      BOOST_STATIC_CONSTANT(type, pattern = type(type(-1)<<shift));
      return b_and(pattern, a0) >> shift;
    }
  };
} } }

#endif
