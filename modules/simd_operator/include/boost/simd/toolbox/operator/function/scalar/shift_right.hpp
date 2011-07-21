//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SHIFT_RIGHT_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/meta/as_bits.hpp>

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shift_right_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = t0.bits >> a1;
      return t0.value;
    }
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shift_right_ , tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    static A0& a0; static A1& a1;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0 >> a1)
    typedef typename nested::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2) { return a0 >> a1; }
  };
} } }

#endif
