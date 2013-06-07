//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/correct_fma.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::correct_fma_, tag::cpu_
                                      , (A0)(X)
                                      , ( simd::meta::is_upgradable_on_ext<A0,X> )
                                      , ((simd_<single_<A0>,X>))
                                        ((simd_<single_<A0>,X>))
                                        ((simd_<single_<A0>,X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      typedef typename dispatch::meta::upgrade<A0>::type ivtype;
      ivtype a0l, a0h, a1l, a1h, a2l, a2h;
      split(a0, a0l, a0h);
      split(a1, a1l, a1h);
      split(a2, a2l, a2h);
      return group(a0l*a1l+a2l, a0h*a1h+a2h);
    }
  };

} } }


#endif
