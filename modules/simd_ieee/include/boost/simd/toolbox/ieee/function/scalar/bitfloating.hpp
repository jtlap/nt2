//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/simd/sdk/meta/as_real.hpp>
#include <boost/simd/include/constants/digits.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<arithmetic_<A0> > )
                            )
  {
 typedef typename meta::as_real<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef result_type           rtype;
      typedef typename meta::from_bits<rtype>::type       type;
      typedef typename meta::from_bits<rtype>::bits_type  bits_type;
      type that = { a0 >= Zero<A0>()
                  ? bits_type(a0)
                  : bits_type((1LL << (8*sizeof(A0)-1))-a0)
                  };
      // TOVERIFY PERFS
      return that.value;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<unsigned_<A0> > )
                            )
  {
 typedef typename meta::as_real<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef result_type rtype;
      typename meta::from_bits<rtype, signed>::type  that =  {a0};
      return that.value;
    }
  };
} } }
#endif
