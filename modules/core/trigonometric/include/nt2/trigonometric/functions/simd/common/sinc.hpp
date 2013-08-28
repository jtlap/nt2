//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINC_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_SINC_HPP_INCLUDED

#include <nt2/trigonometric/functions/sinc.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>

#if !defined(BOOST_SIMD_NO_INFINITIES)
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinc_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), nt2::sinc(nt2::tofloat(a0)));
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinc_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type r = nt2::if_else( nt2::is_eqz(a0)
                                  , nt2::One<result_type>()
                                  , nt2::sin(a0)/a0
                                  );

      #if !defined(BOOST_SIMD_NO_INFINITIES)

      return nt2::if_zero_else(nt2::is_inf(a0), r);

      #else

      return r;

      #endif
    }
  };
} }

#endif
