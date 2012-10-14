//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/is_simd_logical.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/all.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_simd_logical_, tag::cpu_,(A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename boost::dispatch::meta::as_integer<A0, signed>::type iA0;
      iA0 tmp = bitwise_cast<iA0>(a0);
      return result_type(simd::all(l_or(is_equal(tmp, Mone<iA0>()), is_eqz(tmp))));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_simd_logical_, tag::cpu_,(A0)(X)
                            , ((simd_<logical_<A0>,X>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return True<sA0>();
    }
  };
} } }

#endif
