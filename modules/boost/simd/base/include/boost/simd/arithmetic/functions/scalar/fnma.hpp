//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FNMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FNMA_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fnma.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fnma_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint16_<A0> >)
                                      (scalar_< uint16_<A0> >)
                                      (scalar_< uint16_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, A0 const& a2) const
    {
      return A0(uint32_t(-a2)-uint32_t(a0)*uint32_t(a1));
    }
  };
} } }

#endif
