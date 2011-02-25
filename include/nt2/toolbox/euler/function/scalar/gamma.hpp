//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMA_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <boost/math/tr1.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/frac.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <iostream>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gamma_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gamma_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      if (a0 == -Inf<A0>()) return Nan<A0>();
      return boost::math::tr1::tgamma(type(a0));
    }

  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gamma_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gamma_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
//       typedef typename NT2_RETURN_TYPE(1)::type type;
//       if (a0 == -Inf<A0>()) return Nan<A0>();
//       return boost::math::tr1::tgamma(type(a0));
      const double g_p[] = { -1.71618513886549492533811,
			     24.7656508055759199108314,-379.804256470945635097577,
			     629.331155312818442661052,866.966202790413211295064,
			     -31451.2729688483675254357,-36144.4134186911729807069,
			     66456.1438202405440627855 };
      const double g_q[] = { -30.8402300119738975254353,
			     315.350626979604161529144,-1015.15636749021914166146,
			     -3107.77167157231109440444,22538.1184209801510330112,
			     4755.84627752788110767815,-134659.959864969306392456,
			     -115132.259675553483497211 };
      const double g_c[] = { -.001910444077728,8.4171387781295e-4,
			     -5.952379913043012e-4,7.93650793500350248e-4,
			     -.002777777777777681622553,.08333333333333333331554247,
			     .0057083835261 };
      const double g_xbig = 171.624;
      const A0 LOGSQRT2PI =  log(sqrt(Two<A0>()*Pi<A0>())); 

      double fact=1.0, xden, xnum;
      int i, n=0;
      double y=a0, z, y1;
      bool parity=false;
      double res, sum, ysq;
      
      if (y <= 0.0)
	{
	  // ----------------------------------------------------------------------
	  //  Argument is negative
	  // ----------------------------------------------------------------------
	  y = -(a0);
	  y1 = (int)y;
	  res = y - y1;
	  if (res != 0.0)
	    {
	      if (y1 != (((int)(y1*0.5)) * 2.0))
		parity = true;
	      fact = -Pi<A0>()/sinpi(res);
	      y++;
	    }
	  else
	    return Inf<A0>();
	}
      // ----------------------------------------------------------------------
      //  Argument is positive
      // ----------------------------------------------------------------------
      if (y < Eps<A0>())
	{
	  // ----------------------------------------------------------------------
	  //  Argument .LT. EPS
	  // ----------------------------------------------------------------------
	  res = rec(y);
	} else if (y < 12.0)
	{
	  y1 = y;
	  if (y < 1.0)
	    {
	      // ----------------------------------------------------------------------
	      //  0.0 .LT. argument .LT. 1.0
	      // ----------------------------------------------------------------------
	      z = y;
	      y++;
	    }
	  else
	    {
	      // ----------------------------------------------------------------------
	      //  1.0 .LT. argument .LT. 12.0, reduce argument if necessary
	      // ----------------------------------------------------------------------
	      n = (int)y - 1;
	      y -= n;
	      z = y - 1.0;
	    }
	  // ----------------------------------------------------------------------
	  //  Evaluate approximation for 1.0 .LT. argument .LT. 2.0
	  // ----------------------------------------------------------------------
	  std::cout << "z " << z << " y " << y << std::endl; 
	  xnum = 0.0;
	  xden = 1.0;
	  for (i = 0; i < 8; ++i) {
	    xnum = (xnum + g_p[i]) * z;
	    xden = xden * z + g_q[i];
	  }
	  res = xnum / xden + 1.0;
	  if (y1 < y)
	    // ----------------------------------------------------------------------
	    //  Adjust result for case  0.0 .LT. argument .LT. 1.0
	    // ----------------------------------------------------------------------
	    res /= y1;
	  else if (y1 > y)
	    {
	      // ----------------------------------------------------------------------
	      //  Adjust result for case  2.0 .LT. argument .LT. 12.0
	      // ----------------------------------------------------------------------
	      for (i = 0; i < n; ++i)
		{
		  res *= y;
		  y++;
		}
	    }
	  std::cout << "res  "<< res << std::endl; 

	}
      else
	{
	  // ----------------------------------------------------------------------
	  //  Evaluate for argument .GE. 12.0
	  // ----------------------------------------------------------------------
	  if (y <= g_xbig)
	    {
	      ysq = y * y;
	      sum = g_c[6];
	      for (i = 0; i < 6; ++i)
		sum = sum / ysq + g_c[i];
	      sum = sum / y - y + LOGSQRT2PI;
	      sum += (y - 0.5) * log(y);
	      res = exp(sum);
	    }
	  else
	    return Inf<A0>();
	}
      // ----------------------------------------------------------------------
      //  Final adjustments and return
      // ----------------------------------------------------------------------
      if (parity)
	res = -res;
      if (fact != 1.0)
	res = fact / res;
      return res;
    }
  
  };
} }       
#endif
// modified by jt the 26/12/2010
