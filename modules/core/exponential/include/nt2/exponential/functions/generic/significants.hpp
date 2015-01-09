//==============================================================================
//          Copyright 2015 - J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_SIGNIFICANTS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_SIGNIFICANTS_HPP_INCLUDED

#include <nt2/exponential/functions/significants.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/tenpower.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_invalid.hpp>
#endif

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( significants_, tag::cpu_
                          , (A0)(A1)
                          , ((generic_< floating_<A0>>))
                            ((generic_< integer_<A1>>))
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( all(is_gtz(a1))
                      , "Number of significant digits must be positive"
                      );
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0;
      iA0 exp = a1 - iceil(log10(abs(a0)));
      A0 fac = tenpower(exp);
      A0 scaled = round(a0*fac);
#ifndef BOOST_SIMD_NO_INVALIDS
      A0 r = if_else(is_invalid(a0), a0, scaled/fac);
#else
      A0 r =  scaled/fac;
#endif
      return if_zero_else(is_eqz(a0), r);
    }
  };

} }

#endif
