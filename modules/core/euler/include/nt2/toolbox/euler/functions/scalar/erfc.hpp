//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_ERFC_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/erfc.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::erfc(result_type(a0));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      static const boost::array<A0, 5 > erf0_P4 = {{
        A0(6.49254556481904E-05),
        A0(1.20339380863079E-03),
        A0(4.03259488531795E-02),
        A0(0.135894887627278   ),
        A0(1.12837916709551    )
      }};
       static const boost::array<A0, 5 > erf0_Q4 = {{
        A0(3.64915280629351E-04),
        A0(8.49717371168693E-03),
        A0(8.69936222615386E-02),
        A0(0.453767041780003   ),
        A0(1                   )
      }};

      static const boost::array<A0, 7 > erfc1_P5 = {{
        A0(0                   ),
        A0(7.06940843763253E-03),
        A0(7.14193832506776E-02),
        A0(0.331899559578213   ),
        A0(0.878115804155882   ),
        A0(1.33154163936765    ),
        A0(0.999999992049799   )
      }};
       static const boost::array<A0, 7 > erfc1_Q5 = {{
        A0(1.25304936549413E-02),
        A0(0.126579413030178   ),
        A0(0.594651311286482   ),
        A0(1.61876655543871    ),
        A0(2.65383972869776    ),
        A0(2.45992070144246    ),
        A0(1                   )
      }};

      static const boost::array<A0, 7 > erfc2_P5 = {{
        A0(0                   ),
        A0(2.25716982919218E-02),
        A0(0.157289620742839   ),
        A0(0.581528574177741   ),
        A0(1.26739901455873    ),
        A0(1.62356584489367    ),
        A0(0.99992114009714    )
      }};
       static const boost::array<A0, 7 > erfc2_Q5 = {{
        A0(4.00072964526861E-02),
        A0(0.278788439273629   ),
        A0(1.05074004614827    ),
        A0(2.38574194785344    ),
        A0(3.37367334657285    ),
        A0(2.75143870676376    ),
        A0(1                   )
      }};

       if(is_nan(a0)) return a0;
       A0 x =  nt2::abs(a0);
       A0 xx =  sqr(x);
       A0 z =  Zero<A0>();
       if(x<= A0(0.0000000001))
       {
         z = oneminus(x*Two<A0>()/sqrt(Pi<A0>()));
       }
       else if (x<= A0(0.65))
       {
         z = oneminus(x*polevl( xx, erf0_P4)/polevl( xx, erf0_Q4 ));
       }
       else if(x<= A0(2.2))
       {
         z = exp(-xx)*polevl(x, erfc1_P5)/polevl( x, erfc1_Q5);
       }
       else if(x<= A0(6))
       {
         z = exp(-xx)*polevl(x, erfc2_P5)/polevl( x, erfc2_Q5);
       }
       return is_ltz(a0) ? Two<A0>()-z : z;


//       result_type a = Eight<result_type>()*(Pi<result_type>()-Three<result_type>())/
//         (Three<result_type>()*Pi<result_type>()*(Four<result_type>()-Pi<result_type>()));
//       result_type ax2 =  a*sqr(a0);
//       return nt2::sign(a0)*nt2::sqrt(oneminus(nt2::exp(-sqr(a0)*(Four<result_type>()/Pi<result_type>()+ax2)/oneplus(ax2))));
    }
  };


} }

#endif
