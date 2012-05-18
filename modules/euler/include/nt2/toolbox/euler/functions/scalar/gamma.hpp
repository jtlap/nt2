//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMA_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/gamma.hpp>
#include <nt2/toolbox/euler/details/math.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/nbtrue.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/trunc.hpp>
#include <nt2/include/functions/scalar/frac.hpp>
#include <nt2/include/functions/scalar/bitwise_ornot.hpp>
#include <nt2/include/functions/scalar/sinpi.hpp>
#include <nt2/include/functions/scalar/negif.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp> 
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::gamma(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type is single_
/////////////////////////////////////////////////////////////////////////////
#ifdef NT2_TOOLBOX_EULER_HAS_TGAMMAF
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return ::tgammaf(a0);
    }
  };
} }

#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (a0 == Inf<A0>()) return a0;
      if(is_eqz(a0)) return rec(a0); 
      if (is_invalid(a0) || (is_ltz(a0) && is_flint(a0))) return Nan<A0>();
    #ifdef NT2_TOOLBOX_EULER_HAS_TGAMMA
       return ::tgamma(a0);
    #else
       return boost::math::tgamma(a0);
    #endif
//       const double g_p[] = { -1.71618513886549492533811,
// 			     24.7656508055759199108314,-379.804256470945635097577,
// 			     629.331155312818442661052,866.966202790413211295064,
// 			     -31451.2729688483675254357,-36144.4134186911729807069,
// 			     66456.1438202405440627855 };
//       const double g_q[] = { -30.8402300119738975254353,
// 			     315.350626979604161529144,-1015.15636749021914166146,
// 			     -3107.77167157231109440444,22538.1184209801510330112,
// 			     4755.84627752788110767815,-134659.959864969306392456,
// 			     -115132.259675553483497211 };
//       const double g_c[] = { -.001910444077728,8.4171387781295e-4,
// 			     -5.952379913043012e-4,7.93650793500350248e-4,
// 			     -.002777777777777681622553,.08333333333333333331554247,
// 			     .0057083835261 };
//       const double g_xbig = 171.624;
//       const A0 LOGSQRT2PI =  nt2::log(sqrt(Two<A0>()*Pi<A0>())); 

//       double fact=1.0, xden, xnum;
//       int i, n=0;
//       double y=a0, z, y1;
//       bool neg=false;
//       double res, sum, ysq;
//       if (is_eqz(a0)) return rec(a0); 
//       if (y < 0.0)
// 	{
// 	  if (is_flint(y)) return Nan<A0>(); 
// 	  neg =  true;
// 	  y =  1-y;
// 	  fact = Pi<A0>()/sinpi(y);
// 	  // ----------------------------------------------------------------------
// 	  //  Argument is negative
// 	  // ----------------------------------------------------------------------
// 	}
//       // ----------------------------------------------------------------------
//       //  Argument is positive
//       // ----------------------------------------------------------------------
//       if (y < Eps<A0>())
// 	{
// 	  // ----------------------------------------------------------------------
// 	  //  Argument .LT. EPS
// 	  // ----------------------------------------------------------------------
// 	  res = rec(y);
// 	} else if (y < 12.0)
// 	{
// 	  y1 = y;
// 	  if (y < 1.0)
// 	    {
// 	      // ----------------------------------------------------------------------
// 	      //  0.0 .LT. argument .LT. 1.0
// 	      // ----------------------------------------------------------------------
// 	      z = y;
// 	      y++;
// 	    }
// 	  else
// 	    {
// 	      // ----------------------------------------------------------------------
// 	      //  1.0 .LT. argument .LT. 12.0, reduce argument if necessary
// 	      // ----------------------------------------------------------------------
// 	      n = (int)y - 1;
// 	      y -= n;
// 	      z = y - 1.0;
// 	    }
// 	  // ----------------------------------------------------------------------
// 	  //  Evaluate approximation for 1.0 .LT. argument .LT. 2.0
// 	  // ----------------------------------------------------------------------
// 	  xnum = 0.0;
// 	  xden = 1.0;
// 	  for (i = 0; i < 8; ++i) {
// 	    xnum = (xnum + g_p[i]) * z;
// 	    xden = xden * z + g_q[i];
// 	  }
// 	  res = xnum / xden + 1.0;
// 	  if (y1 < y)
// 	    // ----------------------------------------------------------------------
// 	    //  Adjust result for case  0.0 .LT. argument .LT. 1.0
// 	    // ----------------------------------------------------------------------
// 	    res /= y1;
// 	  else if (y1 > y)
// 	    {
// 	      // ----------------------------------------------------------------------
// 	      //  Adjust result for case  2.0 .LT. argument .LT. 12.0
// 	      // ----------------------------------------------------------------------
// 	      for (i = 0; i < n; ++i)
// 		{
// 		  res *= y;
// 		  y++;
// 		}
// 	    }
// 	}
//       else
// 	{
// 	  // ----------------------------------------------------------------------
// 	  //  Evaluate for argument .GE. 12.0
// 	  // ----------------------------------------------------------------------
// 	  if (y <= g_xbig)
// 	    {
// 	      ysq = y * y;
// 	      sum = g_c[6];
// 	      for (i = 0; i < 6; ++i)
// 		sum = sum / ysq + g_c[i];
// 	      sum = sum / y - y + LOGSQRT2PI;
// 	      sum += (y - 0.5) * nt2::log(y);
// 	      res = exp(sum);
// 	    }
// 	  else
// 	    return Inf<A0>();
// 	}
//       // ----------------------------------------------------------------------
//       //  Final adjustments and return
//       // ----------------------------------------------------------------------
//       if (fact != 1.0)
// 	res = fact / res;
//       return res;
    }
  };
} }
       
#endif
