//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINTS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/touints.hpp>
#include <boost/simd/include/functions/simd/is_ngez.hpp>
#include <boost/simd/include/functions/simd/is_lez.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/touint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;
    BOOST_FORCEINLINE
    result_type
    operator()(A0 const& a0) const
    {
      return if_zero_else(is_lez(a0), bitwise_cast<result_type>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;
    BOOST_FORCEINLINE
    result_type
    operator()(A0 const& a0) const
    {
      return bitwise_cast<result_type>(a0);
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_,
                                     (A0)(X)
                                   , ((simd_< floating_<A0>,X >))
                                   )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sr_t;
      static const A0 Vax =  splat<A0>(boost::simd::Valmax<sr_t>());
      return if_zero_else(boost::simd::is_ngez(a0),
                          if_else(boost::simd::gt(a0, Vax), Valmax<result_type>(),
                                  touint(a0)
                                 )
                         );

    }
  };

} } }

#endif
