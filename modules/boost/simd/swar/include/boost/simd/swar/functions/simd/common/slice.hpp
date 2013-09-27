//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SLICE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SLICE_HPP_INCLUDED

#include <boost/simd/swar/functions/slice.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::slice_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , ( boost::mpl::bool_
                                          <
                                            A1::static_size == A0::static_size/2
                                          >
                                        )
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      for(size_t i=0; i!=A1::static_size; ++i)
      {
        a1[i] = a0[i];
        a2[i] = a0[i+A1::static_size];
      }
    }
  };
} } }

#endif
