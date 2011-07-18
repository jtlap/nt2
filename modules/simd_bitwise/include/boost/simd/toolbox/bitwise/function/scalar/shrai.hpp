//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHRAI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHRAI_HPP_INCLUDED

#include <boost/simd/sdk/meta/as_bits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shrai_, tag::cpu_, (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2) { return a0 >> a1; }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shrai_, tag::cpu_, (A0)(A1)
                            , (scalar_< unsigned_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2) { return a0 >> a1; }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shrai_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_bits<A0, signed>::type type;
      type that = {a0};
      that.bits >>= a1;
      return that.value;
    }
  };
} }

#endif
