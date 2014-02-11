//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED

#include <nt2/euler/functions/erfc.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<double_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 lim1 = nt2::splat<A0>(0.65);
      A0 lim2 = nt2::splat<A0>(2.2);
      bA0 test0 = nt2::is_ltz(a0);
      bA0 test1 = nt2::lt(x, lim1);
      A0 r1 = nt2::Zero<A0>();
      std::size_t nb = 0;
      if ((nb = (nt2::inbtrue(test1) > 0)))
      {
        r1 = nt2::oneminus(x*
                           NT2_HORNER_RAT(sA0, 5, 5, xx,
                               (0x3f110512d5b20332ull,
                                0x3f53b7664358865aull,
                                0x3fa4a59a4f02579cull,
                                0x3fc16500f106c0a5ull,
                                0x3ff20dd750429b61ull
                               ),
                               (0x3f37ea4332348252ull,
                                0x3f8166f75999dbd1ull,
                                0x3fb64536ca92ea2full,
                                0x3fdd0a84eb1ca867ull,
                                0x3ff0000000000000ull
                               ))
                          );
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
      bA0 test2 = nt2::lt(x, lim2);
      bA0 test3 = nt2::logical_andnot(test2, test1);
      std::size_t nb1 = 0;
      A0 ex = nt2::exp(-xx);
      if ((nb1 = (nt2::inbtrue(test3) > 0)))
      {
        A0 z = ex*NT2_HORNER_RAT(sA0, 7, 7, x,
                      (0x0ull,
                       0x3f7cf4cfe0aacbb4ull,
                       0x3fb2488a6b5cb5e5ull,
                       0x3fd53dd7a67c7e9full,
                       0x3fec1986509e687bull,
                       0x3ff54dfe9b258a60ull,
                       0x3feffffffbbb552bull
                      ),
                      (0x3f89a996639b0d00ull,
                       0x3fc033c113a7deeeull,
                       0x3fe307622fcff772ull,
                       0x3ff9e677c2777c3cull,
                       0x40053b1052dca8bdull,
                       0x4003adeae79b9708ull,
                       0x3ff0000000000000ull
                      )
                     );

        r1 = nt2::if_else(test1, r1, z);
        nb+= nb1;
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, Two<A0>()-r1, r1);
      }
      A0 z =  ex*NT2_HORNER_RAT(sA0, 7, 7, x,
                     (0x0ll,
                      0x3f971d0907ea7a92ull,
                      0x3fc42210f88b9d43ull,
                      0x3fe29be1cff90d94ull,
                      0x3ff44744306832aeull,
                      0x3ff9fa202deb88e5ull,
                      0x3fefff5a9e697ae2ull
                     ),
                     (0x3fa47bd61bbb3843ull,
                      0x3fd1d7ab774bb837ull,
                      0x3ff0cfd4cb6cde9full,
                      0x400315ffdfd5ce91ull,
                      0x400afd487397568full,
                      0x400602f24bf3fdb6ull,
                      0x3ff0000000000000ull
                     )
                    );
      r1 = nt2::if_else(test2, r1, z);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return  nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<single_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      bA0 test0 = nt2::is_ltz(a0);
      A0 r1 = nt2::Zero<A0>();
      bA0 test1 = nt2::lt(x, Twothird<A0>());
      std::size_t nb = 0;
      A0 z = x/oneplus(x);
      if ((nb = (nt2::inbtrue(test1) > 0)))
      {
        // approximation of erfc(z./(1-z))./(1-z) on [0 0.4]
        // with a polynomial of degree 8 gives 2 ulp on [0 2/3] for erfc
        // (exhaustive test against float(erfc(double(x))))
        r1 = oneminus(z)*
          horner < NT2_HORNER_COEFF_T(sA0, 9,
                                      (
                                        0x41aa8e55,  //   2.1319498e+01
                                        0x401b5680,  //   2.4271545e+00
                                        0xc010d956,  //  -2.2632651e+00
                                        0x3f2cff3b,  //   6.7576951e-01
                                        0xc016c985,  //  -2.3560498e+00
                                        0xbffc9284,  //  -1.9732213e+00
                                        0xbfa11698,  //  -1.2585020e+00
                                        0xbe036d7e,  //  -1.2834737e-01
                                        0x3f7ffffe   //   9.9999988e-01
                                      )
                                     )> (z);
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
      z-= nt2::splat<A0>(0.4);
      // approximation of erfc(z1./(1-z1))).*exp((z1./(1-z1)).^2) (z1 =  z+0.4) on [0 0.5]
      // with a polynomial of degree 7 gives 8 ulp on [2/3 inf] for erfc
      // (exhaustive test against float(erfc(double(x))))
      A0 r2 =   exp(-sqr(x))*
          horner < NT2_HORNER_COEFF_T(sA0, 8,
                                      (
                                        0x3f1d56a3, //     6.1460322e-01
                                        0xbf96c6af, //    -1.1779383e+00
                                        0x3ec8fa31, //     3.9253381e-01
                                        0x3d538579, //     5.1640961e-02
                                        0x3ecbecd4, //     3.9829123e-01
                                        0x3e233bd3, //     1.5940790e-01
                                        0xbf918995, //    -1.1370112e+00
                                        0x3f0a0e89  //     5.3928429e-01
                                      )
                                     )> (z);
      r1 = if_else(test1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
    }
  };
} }

#endif
