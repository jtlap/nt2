//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_BITWISE_SELECT_HPP_INCLUDED
#include <boost/simd/toolbox/bitwise/functions/bitwise_select.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/simd/include/functions/scalar/bitwise_andnot.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_select_, tag::cpu_, (A0)(A1),
                                        (boost::mpl::bool_<sizeof(A0) == sizeof(A1)>)
                                      , (scalar_< arithmetic_<A0> >)
                                        (scalar_< arithmetic_<A1> >)
                                        (scalar_< arithmetic_<A1> >)
                                      )
  {
    typedef A1 result_type;
    inline A1 operator()(const A0 & a0,const A1 & a1,const A1 & a2) const
    {
      return b_or(b_and(a1, a0), b_andnot(a2, a0));
    }
  };
} } }

#endif
