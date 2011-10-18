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

#include <boost/simd/include/functions/is_true.hpp>

// #ifdef BOOST_MSVC
//   #pragma warning(push)
//   #pragma warning(disable: 4146) // unary minus applied to unsigned
// #endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::negif_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (scalar_< signed_<A1> >)
                            )
  {
    typedef A1 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return boost::simd::is_true(a0)?-a1:a1; }
  };
} } }

// #ifdef BOOST_MSVC
//   #pragma warning(pop)
// #endif

#endif
