//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED

#include <nt2/euler/functions/erfc.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>

#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/twothird.hpp>

#include <boost/simd/sdk/config.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
#ifndef BOOST_SIMD_NO_INVALIDS
      if(nt2::is_nan(a0)) return a0;
#endif
      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 z =  nt2::Zero<A0>();
      if(x <= A0(0.0000000001))
      {
        z = nt2::oneminus(x*nt2::Two<A0>()/nt2::sqrt(nt2::Pi<A0>()));
      }
      else if (x< A0(0.65))
      {
        z = nt2::oneminus(x*
                          NT2_HORNER_RAT(A0, 5, 5, xx,
                                  (0x3f110512d5b20332ull, // 6.49254556481904E-05
                                   0x3f53b7664358865aull, // 1.20339380863079E-03
                                   0x3fa4a59a4f02579cull, // 4.03259488531795E-02
                                   0x3fc16500f106c0a5ull, // 0.135894887627278
                                   0x3ff20dd750429b61ull  // 1.12837916709551
                                  ),
                                  (0x3f37ea4332348252ull, // 3.64915280629351E-04
                                   0x3f8166f75999dbd1ull, // 8.49717371168693E-03
                                   0x3fb64536ca92ea2full, // 8.69936222615386E-02
                                   0x3fdd0a84eb1ca867ull, // 0.453767041780003
                                   0x3ff0000000000000ull  // 1
                                  ))
                         );
      }
      else if(x< A0(2.2))
      {
        z = nt2::exp(-xx)*
          NT2_HORNER_RAT(A0, 7, 7, x,
                  (0x0ull,                // 0
                   0x3f7cf4cfe0aacbb4ull, // 7.06940843763253E-03
                   0x3fb2488a6b5cb5e5ull, // 7.14193832506776E-02
                   0x3fd53dd7a67c7e9full, // 0.331899559578213
                   0x3fec1986509e687bull, // 0.878115804155882
                   0x3ff54dfe9b258a60ull, // 1.33154163936765
                   0x3feffffffbbb552bull  // 0.999999992049799
                  ),
                  (0x3f89a996639b0d00ull, // 1.25304936549413E-02
                   0x3fc033c113a7deeeull, // 0.126579413030178
                   0x3fe307622fcff772ull, // 0.594651311286482
                   0x3ff9e677c2777c3cull, // 1.61876655543871
                   0x40053b1052dca8bdull, // 2.65383972869776
                   0x4003adeae79b9708ull, // 2.45992070144246
                   0x3ff0000000000000ull  // 1
                  )
                 );
      }
      else if(x< A0(6))
      {
        z = nt2::exp(-xx)*
          NT2_HORNER_RAT(A0, 7, 7, x,
                  (0x0ll,                 //0
                   0x3f971d0907ea7a92ull, //2.25716982919218E-02
                   0x3fc42210f88b9d43ull, //0.157289620742839
                   0x3fe29be1cff90d94ull, //0.581528574177741
                   0x3ff44744306832aeull, //1.26739901455873
                   0x3ff9fa202deb88e5ull, //1.62356584489367
                   0x3fefff5a9e697ae2ull  //0.99992114009714
                  ),
                  (0x3fa47bd61bbb3843ull, //4.00072964526861E-02
                   0x3fd1d7ab774bb837ull, //0.278788439273629
                   0x3ff0cfd4cb6cde9full, //1.05074004614827
                   0x400315ffdfd5ce91ull, //2.38574194785344
                   0x400afd487397568full, //3.37367334657285
                   0x400602f24bf3fdb6ull, //2.75143870676376
                   0x3ff0000000000000ull  //1
                  )
                 );
      }
      return (a0 < 0.0) ? 2.0-z : z;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)
                              , ((scalar_<single_<A0> >))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x =  nt2::abs(a0);
      A0 r1 = nt2::Zero<A0>();
      A0 z =  x/oneplus(x);
      if (x < Twothird<A0>())
      {
        r1 = oneminus(z)*
          horner < NT2_HORNER_COEFF_T(A0, 9,
                                      (
                                        0x41aa8e55,
                                        0x401b5680,
                                        0xc010d956,
                                        0x3f2cff3b,
                                        0xc016c985,
                                        0xbffc9284,
                                        0xbfa11698,
                                        0xbe036d7e,
                                        0x3f7ffffe
                                      )
                                     )> (z);
      }
      #ifndef BOOST_SIMD_NO_INFINITIES
      else if (BOOST_UNLIKELY(x == Inf<A0>()))
      {
        r1 = Zero<A0>();
      }
      #endif
      else
      {
       z-= 0.4f;
        r1 = exp(-sqr(x))*
          horner < NT2_HORNER_COEFF_T(A0, 8,
                                      (
                                        0x3f1d56a3,
                                        0xbf96c6af,
                                        0x3ec8fa31,
                                        0x3d538579,
                                        0x3ecbecd4,
                                        0x3e233bd3,
                                        0xbf918995,
                                        0x3f0a0e89
                                      )
                                     )> (z);
      }
      return (a0 < 0.0f) ? 2.0f-r1 : r1;
    }
  };


} }

#endif
