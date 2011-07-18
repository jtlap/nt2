//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_SDK_FUNCTOR_DETAILS_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_SDK_FUNCTOR_DETAILS_COMPLEMENT_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/meta/as_bits.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::complement_, tag::cpu_, (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1) { return ~a0; }
  };
} }

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::complement_, tag::cpu_, (A0)
                            , (scalar_< real_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = ~t0.bits;
      return t0.value;
    }
  };
} }

#endif
