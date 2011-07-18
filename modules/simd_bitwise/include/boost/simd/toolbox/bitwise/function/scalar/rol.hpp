//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_ROL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_ROL_HPP_INCLUDED

#include <boost/simd/sdk/meta/as_bits.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/sdk/meta/adapted_traits.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rol_, tag::cpu_, (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      return shli(a0, a1) | shri(a0, (sizeof(A0)*CHAR_BIT-a1));
    }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rol_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = shli(t0.bits,a1) | shri(t0.bits, (sizeof(A0)*CHAR_BIT-a1));
      return t0.value;
    }
  };
} }

#endif
