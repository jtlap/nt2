//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_DETAILS_EXTRAPOL2_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_DETAILS_EXTRAPOL2_HPP_INCLUDED
/////////////////////////////////////////////////////////////////////
// When no extrapol2ation is done conforming to the current
// interpolation  method extrapol2 replaces the values corresponding
// to out of ranges abscisae by exrapval.
/////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/havesamesize.hpp>
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
  template < class ZI,  class X,  class Y,  class XI,  class YI,  class T>
  BOOST_FORCEINLINE
  void extrapol2(ZI& zi, const X& x, const Y& y,  const XI& xi,  const YI& yi,  const T& extrapval)
  {
    using value_type = typename ZI::value_type;
    using x_type = typename XI::value_type;
    x_type  bx =  x_type(x(begin_));
    x_type  ex =  x_type(x(end_));
    x_type  by =  x_type(y(begin_));
    x_type  ey =  x_type(y(end_));
    auto extrapvals = repnum(extrapval, zi.extent());
    auto test0  =  nt2::logical_or(boost::simd::is_nge(xi, bx),
                                   boost::simd::is_nle(xi, ex));
    auto test1  =  nt2::logical_or(boost::simd::is_nge(yi, by),
                                   boost::simd::is_nle(yi, ey));
    if (havesamesize(xi, zi)&&havesamesize(yi, zi))
    {
      zi = if_else(logical_or(test0, test1), extrapvals, zi);
    }
    else
    {
      auto expt0 = expand_to(colvect(test0), zi.extent());
      auto expt1 = expand_to(rowvect(test1), zi.extent());
      zi = if_else(logical_or(expt0, expt1), extrapvals, zi);
    }
  }
} }

#endif
