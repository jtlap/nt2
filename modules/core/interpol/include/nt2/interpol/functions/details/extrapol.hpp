//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_DETAILS_EXTRAPOL_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_DETAILS_EXTRAPOL_HPP_INCLUDED
/////////////////////////////////////////////////////////////////////
// When no extrapolation is done conforming to the current
// interpolation  method extrapol replaces the values corresponding
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
  template < class YI,  class X,  class XI,  class T,  class S>
  BOOST_FORCEINLINE
  void extrapol(YI& yi, const X& x,  const XI& xi,  const T& extrapval, const S&/* finalsize*/)
  {
    using value_type = T;
    value_type  b =  value_type(x(begin_));
    value_type  e =  value_type(x(end_));
    auto extrapvals = repnum(extrapval, yi.extent());
    auto test0  =  nt2::logical_or(boost::simd::is_nge(xi, b),
                                   boost::simd::is_nle(xi, e));
    if (havesamesize(xi, yi))
    {
      yi = if_else(test0, extrapvals, yi);
    }
    else
    {
      yi = if_else(expand_to(colvect(test0), yi.extent()), extrapvals, yi);
//      yi = squeeze(reshape(yi, finalsize));
    }
  }
} }

#endif
