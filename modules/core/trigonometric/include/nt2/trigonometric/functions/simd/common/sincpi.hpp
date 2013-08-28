//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINCPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINCPI_HPP_INCLUDED

#include <nt2/trigonometric/functions/sincpi.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sincpi_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), nt2::sincpi(nt2::tofloat(a0)));
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sincpi_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      // When dealing with platform with no denormal, we need to force the
      // operation order to guarantee that sinpi(x)/x is equal to pi
      #if defined(BOOST_SIMD_NO_DENORMALS)
      #define M0(x) nt2::Invpi<result_type>()*(nt2::sinpi((x))/(x))
      #else
      #define M0(x) (nt2::Invpi<result_type>()*nt2::sinpi((x)))/(x)
      #endif

      result_type r = nt2::if_else( is_eqz(a0)
                                  , nt2::One<result_type>()
                                  , M0(a0)
                                  );
      #undef M0

      #if !defined(BOOST_SIMD_NO_INFINITIES)

      return nt2::if_zero_else(nt2::is_inf(a0), r);

      #else

      return r;

      #endif
    }
  };
} }

#endif
