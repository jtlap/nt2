//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_MULS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/shrai.hpp>
#include <boost/simd/include/functions/simd/is_not_equal.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/is_upgradable_to.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::muls_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<floating_<A0>, X>))((simd_<floating_<A0>, X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0*a1;
    }
  }

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::muls_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::mpl::
                                          not_< simd::meta::is_upgradable_to<A0,A0> >
                                        )
                                      , ((simd_<uint_<A0>, X>))((simd_<uint_<A0>, X>))
                                      )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype a00, a01, a10, a11;
      split(a0, a00, a01);
      split(a1, a10, a11);

      utype res0 = a00*a10;
      utype res1 = a01*a11;

      return group(res0, res1)
           | group( shrai(res0, sizeof(stype)*CHAR_BIT)
                  , shrai(res1, sizeof(stype)*CHAR_BIT)
                  );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::muls_, tag::cpu_
                                      , (A0)(X)
                                      , ( boost::mpl::
                                          not_< simd::meta::is_upgradable_to<A0,A0> >
                                        )
                                      , ((simd_<int_<A0>, X>))((simd_<int_<A0>, X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::as_unsigned<A0>::type untype;
      typedef typename dispatch::meta::upgrade<A0>::type utype;

      utype a00, a01, a10, a11;
      split(a0, a00, a01);
      split(a1, a10, a11);

      utype res0 = a00*a10;
      utype res1 = a01*a11;

      untype res2 = bitwise_cast<untype>(shrai(a0 ^ a1, sizeof(stype)*CHAR_BIT-1)) + Valmax<stype>();

      A0 hi = group( shrai(res0, sizeof(stype)*CHAR_BIT)
                   , shrai(res1, sizeof(stype)*CHAR_BIT)
                   );
      A0 lo = group(res0, res1);

      return if_else( hi != shrai(lo, sizeof(stype)*CHAR_BIT-1)
                    , bitwise_cast<A0>(res2)
                    , lo
                    );
    }
  };
} } }

#endif
