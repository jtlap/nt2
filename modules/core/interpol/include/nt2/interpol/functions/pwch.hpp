//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_PWCH_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_PWCH_HPP_INCLUDED

#include <nt2/include/functions/ppval.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/fms.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{


//  pc = pwch(x,y,s) returns the ppform of the piecewise cubic hermite
//  interpolant f to the given data values y and the given slopes s
//  at the given data sites x. x must be a vector, and s must be of the same
//  size as y.
//  if y is a vector, then it must be of the same length as x and will be
//  resized if necessary to be a row vector.
//  if y is a matrix, then size(y,2) must equal length(x).
//
//  with d equal to size(y,1), the piecewise cubic hermite interpolant f to
//  these data is the d-valued piecewise cubic function with breaks at the
//  data sites x that satisfies
//
//         f(x(j)) = y(:,j),  df(x(j)) = s(:,j),  j=1:length(x) .
//
//  pc = pwch(x,y,s,dx,divdif) also asks for dx := diff(x) and divdif :=
//  diff(y,1,2)./dx .
//

  template < class A0,  class A1, class A2, class A3, class A4>
  auto pwch(const A0 & x,
            const A1 & y,
            const A2 & s,
            const A3 & dx,
            const A4 & divdif)-> ppval<typename A1::value_type>
  {
    using vtype = typename A1::value_type;
    size_t n = numel(x);
    size_t d = height(y);
    auto dxd = repmat(dx,d,1);
    table<vtype> dzzdx = (divdif-s(nt2::_,nt2::_(1, end_-1)))/dxd;
    table<vtype> dzdxdx = (s(nt2::_,nt2::_(2, end_))-divdif)/dxd;
    size_t dnm1 = d*(n-1);
    auto coefs =
      nt2::cath(
        nt2::cath(
          nt2::cath(
            reshape((dzdxdx-dzzdx)/dxd, dnm1, 1),
            reshape(fms(Two<vtype>(), dzzdx, dzdxdx), dnm1, 1)
          ),
          reshape(s(nt2::_,_(1, end_-1)),dnm1,1)
        ),
        reshape(y(_, _(1, end_-1)),dnm1,1)
      );
    return ppval<vtype>(x, coefs, d);
  }
  template < class A0,  class A1, class A2, class A3>
  auto pwch(const A0 & x,
            const A1 & y,
            const A2 & s,
            const A3 & dx
           )-> ppval<typename A1::value_type>
  {
    return pwch(x, y, s, dx, diff(y,1,2)/dx);
  }
  template < class A0,  class A1, class A2>
  auto pwch(const A0 & x,
            const A1 & y,
            const A2 & s
            )-> ppval<typename A1::value_type>
  {
    auto dx =  evaluate(diff(x));
    return pwch(x, y, s, diff(x), diff(y,1,2)/dx);
  }

} }


#endif
