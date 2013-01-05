/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTEGRATION_MIDPAREA_HPP_INCLUDED
#define NT2_TOOLBOX_INTEGRATION_MIDPAREA_HPP_INCLUDED
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_not_finite.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/cons.hpp>
namespace nt2
{
  namespace details
  {

    template < class V, class F, class X>
    inline V
    midparea( F f, const X& a, const X& b)
    {
      // Return q = (b-a)*f((a+b)/2). Although formally correct as a low
      // order quadrature formula, this function is only used to return
      // nan or zero of the appropriate class when a == b, is_nan(a), or
      // is_nan(b).
    NT2_DISPLAY("midparea----");
      X x = nt2::average(a, b);
      if (is_finite(a) && is_finite(b) && is_not_finite(x))
      {
        // Treat overflow, e.g. when finite a and b > realmax/2
        x = (a*nt2::Half<X>()) + (b*nt2::Half<X>());
      }
      container::table<X> xx = x;
      V fx = f(xx);
//         if (is_notfinite(fx))
//             warning("Infinite or Not-a-Number value encountered.");
      return (b-a)*fx;
    }
  }
}


#endif
