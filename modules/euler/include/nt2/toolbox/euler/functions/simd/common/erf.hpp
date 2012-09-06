//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_ERF_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_ERF_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/erf.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/polevl.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return erf(tofloat(a0));
   }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      static const boost::array<sA0, 5 > erf0_P4 = {{
          sA0(6.49254556481904E-05),
          sA0(1.20339380863079E-03),
          sA0(4.03259488531795E-02),
          sA0(0.135894887627278   ),
          sA0(1.12837916709551    )
        }};
      static const boost::array<sA0, 5 > erf0_Q4 = {{
          sA0(3.64915280629351E-04),
          sA0(8.49717371168693E-03),
          sA0(8.69936222615386E-02),
          sA0(0.453767041780003   ),
          sA0(1                   )
        }};

      static const boost::array<sA0, 7 > erfc1_P5 = {{
          sA0(0                   ),
          sA0(7.06940843763253E-03),
          sA0(7.14193832506776E-02),
          sA0(0.331899559578213   ),
          sA0(0.878115804155882   ),
          sA0(1.33154163936765    ),
          sA0(0.999999992049799   )
        }};
      static const boost::array<sA0, 7 > erfc1_Q5 = {{
          sA0(1.25304936549413E-02),
          sA0(0.126579413030178   ),
          sA0(0.594651311286482   ),
          sA0(1.61876655543871    ),
          sA0(2.65383972869776    ),
          sA0(2.45992070144246    ),
          sA0(1                   )
        }};

      static const boost::array<sA0, 7 > erfc2_P5 = {{
          sA0(0                   ),
          sA0(2.25716982919218E-02),
          sA0(0.157289620742839   ),
          sA0(0.581528574177741   ),
          sA0(1.26739901455873    ),
          sA0(1.62356584489367    ),
          sA0(0.99992114009714    )
        }};
      static const boost::array<sA0, 7 > erfc2_Q5 = {{
          sA0(4.00072964526861E-02),
          sA0(0.278788439273629   ),
          sA0(1.05074004614827    ),
          sA0(2.38574194785344    ),
          sA0(3.37367334657285    ),
          sA0(2.75143870676376    ),
          sA0(1                   )
        }};
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 xx =  sqr(x);
      A0 lim1 = splat<A0>(0.65);
      A0 lim2 = splat<A0>(2.2);
      bA0 test1 = lt(x, lim1);
      A0 r1 = Zero<A0>();
      uint32_t nb = 0;
      if ((nb = (inbtrue(test1) > 0)))
        {
          r1 = a0*polevl( xx, erf0_P4)/polevl( xx, erf0_Q4 );
          if (nb >= meta::cardinal_of<A0>::value) return r1;
        }
      bA0 test2 = lt(x, lim2);
      bA0 test3 = logical_andnot(test2, test1);
      uint32_t nb1 = 0;
      A0 ex = nt2::exp(-xx);
      if ((nb1 = (inbtrue(test3) > 0)))
        {
          A0 z = oneminus(ex*polevl(x, erfc1_P5)/polevl( x, erfc1_Q5));
          A0 r2 = negif(is_ltz(a0), z);
          r1 = select(test1, r1, r2);
          nb+= nb1;
          if (nb >= meta::cardinal_of<A0>::value) return r1;
        }
      A0 z = negif(is_ltz(a0), oneminus(ex*polevl(x, erfc2_P5)/polevl( x, erfc2_Q5)));
      return select(nt2::is_inf(a0), nt2::sign(a0), select(test2, r1, z));

 //       if(x<= A0(0.0000000001))
//          return a0*Two<A0>()/sqrt(Pi<A0>());
//        else if (x<= A0(0.65))
//          {
//            return a0*polevl( xx, erf0_P4)/polevl( xx, erf0_Q4 );
//          }
//        else if(x<= A0(2.2))
//          {
//            A0 z = oneminus(exp(-xx)*polevl(x, erfc1_P5)/polevl( x, erfc1_Q5));
//            return negif(is_ltz(a0), z);
//          }
//        else if(x<= A0(6))
//          {
//            A0 z = oneminus(exp(-xx)*polevl(x, erfc2_P5)/polevl( x, erfc2_Q5));
//            return negif(is_ltz(a0), z);
//          }
//        else
//          return One<A0>();

       //      result_type a = Eight<result_type>()*(Pi<result_type>()-Three<result_type>())/
       //        (Three<result_type>()*Pi<result_type>()*(Four<result_type>()-Pi<result_type>()));
       //      result_type ax2 =  a*sqr(a0);
       //      return nt2::sign(a0)*nt2::sqrt(oneminus(nt2::exp(-sqr(a0)*(Four<result_type>()/Pi<result_type>()+ax2)/(oneplus(ax2)))));
   }
  };


} }
#endif
