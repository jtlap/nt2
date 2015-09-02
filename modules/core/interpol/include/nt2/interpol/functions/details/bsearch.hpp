//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_DETAILS_BSEARCH_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_DETAILS_BSEARCH_HPP_INCLUDED
/////////////////////////////////////////////////////////////////////
/// by          : J. Falcou and J.T. Lapresté
/// description :
///  Perform a binary search of a vector of values.
///  The parameters index_lo and index_hi provide an initial bracket,
///  and it is assumed that index_lo < index_hi. The resulting index
///  is guaranteed to be strictly less than index_hi and greater than
///  or equal to index_lo, so that the implicit bracket [index, index+1]
///  always corresponds to a region within the implicit value range of
///  the value array.
///  Note that this means the relationship of 'x' to xx(index)
///  and xx(index+1) depends on the result region, i.e. the
///  behaviour at the boundaries may not correspond to what you
///  expect. We have the following complete specification of the
///  behaviour.
///  Suppose the input is xx = { x0, x1, ..., xN }
///     if ( x == x0 )           then  index == 0
///     if ( x > x0 && x <= x1 ) then  index == 0, and sim. for other interior pts
///     if ( x == xN )           then  index == N-1
///     if ( x > xN )            then  index == N-1
///     if ( x < x0 )            then  index == 0
/////////////////////////////////////////////////////////////////////
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/iscolumn.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/globalany.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace details
{
//   template < class A0, class OR >
//   struct bsearch;

    template < class I,  class X,  class XI>
    BOOST_FORCEINLINE
    void bsearch(I& ilo, const X& xx,  const XI& xi)
    {
      using value_type = typename X::value_type;
      using index_type = typename I::value_type;
      using bvalue_type = typename nt2::meta::as_logical<value_type>::type;
      using bindex_type = typename nt2::meta::as_logical<index_type>::type;
      using Ti = table<index_type>;
      using Tbi= table<bindex_type>;
      using Tbv= table<bvalue_type>;
      BOOST_ASSERT_MSG(isvector(xx), "first search input must be a vector");
      size_t n =  numel(xi);
      if (iscolumn(xx))
      {
        ilo.resize(of_size(n, 1u));
        ilo = nt2::repnum(index_type(first_index<1>(xx)), n, 1u);
        Ti ihi   = nt2::repnum(index_type(last_index<1>(xx)), n, 1u);
        Ti i(of_size(n, 1));
        Tbi toiter = nt2::gt(ihi, nt2::oneplus(ilo));
        Tbv ok;
        bindex_type tmp =  nt2::globalany(toiter);
        while (bool(tmp))
        {
          i =  nt2::if_else(toiter, nt2::average(ihi, ilo), i);
          ok =  nt2::gt(xx(i), colvect(xi));
          ihi = nt2::if_else(ok,i,ihi);
          ilo = nt2::if_else(ok,ilo,i);
          toiter =  nt2::gt(ihi, nt2::oneplus(ilo));
          tmp = nt2::globalany(toiter);
        }
       }
      else
      {
        ilo.resize(of_size(1u, n));
        ilo = nt2::repnum(index_type(first_index<2>(xx)), 1u, n);
        Ti ihi   = nt2::repnum(index_type(last_index<2>(xx)),  1u, n);
        Ti  i(of_size(1, n));
        Tbi toiter = nt2::gt(ihi, nt2::oneplus(ilo));
        Tbv ok;
        bindex_type tmp =  nt2::globalany(toiter);
        while (bool(tmp))
        {
          i =  nt2::if_else(toiter, nt2::average(ihi, ilo), i);
          ok =  nt2::gt(xx(first_index<1>(xx), i), rowvect(xi));
          ihi = nt2::if_else(ok,i,ihi);
          ilo = nt2::if_else(ok,ilo,i);
          toiter =  nt2::gt(ihi, nt2::oneplus(ilo));
          tmp = nt2::globalany(toiter);
        }
      }
      ilo = reshape(ilo, size(xi));
    }

} }

#endif
