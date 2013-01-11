//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_IF_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_IF_ELSE_ZERO_HPP_INCLUDED
#include <boost/simd/toolbox/boolean/functions/if_else_zero.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/is_nez.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_zero_, tag::cpu_, (A0)(A1)
                            , (scalar_< logical_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef A1 result_type;
    inline A1 operator()(const A0 & a0,const A1 & a1) const
    { return is_nez(a0) ? a1 :Zero<result_type>(); }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_zero_, tag::cpu_, (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef A1 result_type;
    inline A1 operator()(const A0 & a0,const A1 & a1) const
    { return is_nez(a0) ? a1 :Zero<result_type>(); }
  };
} } }

#endif
