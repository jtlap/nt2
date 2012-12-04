//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_NEGIF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SCALAR_NEGIF_HPP_INCLUDED
#include <boost/simd/toolbox/boolean/functions/negif.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::negif_, tag::cpu_, (A0)(A1)
                            , (scalar_< logical_<A0> >)
                              (scalar_< signed_<A1> >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return a0?-a1:a1; }
  };
} } }

#endif
