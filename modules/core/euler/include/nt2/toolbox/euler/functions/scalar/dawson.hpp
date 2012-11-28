//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_DAWSON_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_DAWSON_HPP_INCLUDED
#include <nt2/toolbox/euler/functions/dawson.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/scalar/plevl.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/abs.hpp>

#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <boost/array.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dawson_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::dawson(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dawson_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      static const boost::array<A0, 10 > AN = {{
        A0(1.13681498971755972054E-11),
        A0(8.49262267667473811108E-10),
        A0(1.94434204175553054283E-8),
        A0(9.53151741254484363489E-7),
        A0(3.07828309874913200438E-6),
        A0(3.52513368520288738649E-4),
        A0(-8.50149846724410912031E-4),
        A0(4.22618223005546594270E-2),
        A0(-9.17480371773452345351E-2),
        A0(9.99999999999999994612E-1),
      }};
      static const boost::array<A0, 11 > AD = {{
        A0(2.40372073066762605484E-11),
        A0(1.48864681368493396752E-9),
        A0(5.21265281010541664570E-8),
        A0(1.27258478273186970203E-6),
        A0(2.32490249820789513991E-5),
        A0(3.25524741826057911661E-4),
        A0(3.48805814657162590916E-3),
        A0(2.79448531198828973716E-2),
        A0(1.58874241960120565368E-1),
        A0(5.74918629489320327824E-1),
        A0(1.00000000000000000539E0),
      }};

      /* interval 3.25 to 6.25 */
      static const boost::array<A0 , 11 >BN = {{
        A0(5.08955156417900903354E-1),
        A0(-2.44754418142697847934E-1),
        A0(9.41512335303534411857E-2),
        A0(-2.18711255142039025206E-2),
        A0(3.66207612329569181322E-3),
        A0(-4.23209114460388756528E-4),
        A0(3.59641304793896631888E-5),
        A0(-2.14640351719968974225E-6),
        A0(9.10010780076391431042E-8),
        A0(-2.40274520828250956942E-9),
        A0(3.59233385440928410398E-11),
      }};
      static  const boost::array<A0, 10>BD = {{
        /*  A0(1.00000000000000000000E0),*/
        A0(-6.31839869873368190192E-1),
        A0(2.36706788228248691528E-1),
        A0(-5.31806367003223277662E-2),
        A0(8.48041718586295374409E-3),
        A0(-9.47996768486665330168E-4),
        A0(7.81025592944552338085E-5),
        A0(-4.55875153252442634831E-6),
        A0(1.89100358111421846170E-7),
        A0(-4.91324691331920606875E-9),
        A0(7.18466403235734541950E-11),
      }};

      /* 6.25 to infinity */
      static  const boost::array<A0, 5> CN = {{
        A0(-5.90592860534773254987E-1),
        A0(6.29235242724368800674E-1),
        A0(-1.72858975380388136411E-1),
        A0(1.64837047825189632310E-2),
        A0(-4.86827613020462700845E-4),
      }};
      static  const boost::array<A0, 5> CD = {{
        /* A0(1.00000000000000000000E0),*/
        A0(-2.69820057197544900361E0),
        A0(1.73270799045947845857E0),
        A0(-3.93708582281939493482E-1),
        A0(3.44278924041233391079E-2),
        A0(-9.73655226040941223894E-4),
      }};
      A0 xx =  nt2::abs(a0);
      A0 x = sqr(xx);
      if( xx < static_cast<A0>(3.25) )
      {
        A0 x = sqr(xx);
        return a0 * polevl( x, AN)/polevl( x, AD );
      }
      x =  rec(x);
      if( xx < static_cast<A0>(6.25) )
      {
        A0 y = rec(xx) + x * polevl( x, BN) / (plevl( x, BD) * xx);
        return copysign(Half<A0>()*y, a0);
      }
      if( xx > static_cast<A0>(1.0e9) ) return Half<A0>()*copysign(rec(xx), a0);
      /* 6.25 to 1.0e9 */
      A0 y = rec(xx) + x * polevl( x, CN) / (plevl( x, CD) * xx);
      return copysign(Half<A0>()*y, a0);
    }
  };
} }


#endif
