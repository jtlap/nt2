//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_DETAILS_CHECK2_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_DETAILS_CHECK2_HPP_INCLUDED

#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/havesamesize.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/iscolumn.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/transpose.hpp>

#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/squeeze.hpp>

namespace nt2 { namespace details
{
  template < class Z,  class X,  class Y,  class XI,  class YI,
             class XOUT,  class YOUT,  class XIOUT,  class YIOUT>
  BOOST_FORCEINLINE
  void check2(const Z& z, const X& x, const Y& y, const XI & xi, const YI & yi,
              XOUT& xout, YOUT& yout, XIOUT & xiout, YIOUT & yiout)
  {
    BOOST_ASSERT_MSG(issorted(x, 'a')&&issorted(y, 'a'),
                     " x and y values must be sorted in ascending order");
    xout = x;
    yout = y;
    xiout = xi;
    yiout = yi;

    if (isvector (x) && isvector (y))
    {
      xout = x(_); yout = y(_);
    }
    else if (havesamesize(x, y))
    {
      xout = trans(x(1,_)); yout = y(_,1); // keep the first line of x and the first col of y
    }
    else
    {
      BOOST_ASSERT_MSG (false, "x and y must be matrices of same size");
    }
    // xout and yout are now defined and are vectors
    BOOST_ASSERT_MSG((numel(xout) == width(z) && numel(yout) == height(z))
                    , "x and y size must match the dimensions of z.");

//   if xi and yi are vectors of different orientation build a grid
    if ((isrow (xi) && iscolumn (yi)) || (iscolumn (xi) && isrow(yi)))
    {
      tie(xiout, yiout) = meshgrid (xi, yi);
    }
    else if (!havesamesize(xi, yi))
    {
      BOOST_ASSERT_MSG(false, "xi and yi  must be matrices of equal size.");
    }
    else
    {
      xiout = xi;  yiout = yi;
    }
    // xiout and yiout are defined and if they are vectors
    // x and y should share their orientation.
    if (isrow(xiout))
    {
      if (iscolumn(xout)) xout = rowvect(x);
      if (iscolumn(yout)) yout = rowvect(y);
    }
    else if (iscolumn (xiout))
    {
      if (isrow (xout)) xout = colvect(x);
      if (isrow (yout)) yout = colvect(y);
    }
  }

} }

#endif
