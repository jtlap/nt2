//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                        ((simd_<arithmetic_<A1>,Y>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& a1, A1& a2) const
    {
      static const std::size_t size_2 = meta::cardinal_of<A0>::value/2;
      typedef typename meta::scalar_of<A1>::type sA1;
      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp1[size_2];
      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp2[size_2];

      for(size_t i = 0; i != size_2; ++i)
      {
        tmp1[i] = a0[i];
        tmp2[i] = a0[i+size_2];
      }

      a1 = aligned_load<A1>(&tmp1[0], 0);
      a2 = aligned_load<A1>(&tmp2[0], 0);
    }
  };
} } }

#endif
