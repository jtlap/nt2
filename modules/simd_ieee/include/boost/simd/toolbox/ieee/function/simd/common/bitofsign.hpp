//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/sdk/details/ignore_unused.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<signed_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1) { return b_and(a0, Signmask<A0>()); }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1) { ignore_unused(a0); return Zero<A0>(); }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<real_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1) { return b_and(a0, Mzero<result_type>()); }
  };
} }

#endif
