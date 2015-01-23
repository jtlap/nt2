//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HISTC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HISTC_HPP_INCLUDED

#include <nt2/core/functions/histc.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/next.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/extremum/extremum.hpp>
#include <nt2/core/container/table/table.hpp>
#include <iostream>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( histc_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type value_type;
    typedef container::table<std::size_t> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return histc(a0, 10);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( histc_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef container::table<std::size_t> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const & n) const
    {
      typedef typename A0::value_type value_type;
      result_type h(of_size(1, n));
      container::table<value_type> xx = x(is_finite(x));
      value_type mi =  globalmin(xx);
      value_type ma =  globalmax(xx);
      container::table<value_type> bins = linspace(mi, ma, n+1);
      bins(end_) = next(bins(end_));
      for(A1 i=1; i <= n ; i++)
      {
        h(i) =  nbtrue(logical_and(ge(xx, bins(i)), lt(xx,  bins(i+1))));
      }
      return h;
    }
  };

  BOOST_DISPATCH_IMPLEMENT( histc_, tag::cpu_,
                            (A0)(A1)(A2),
                            ((ast_<A0, nt2::container::domain>))
                            ((ast_<A1, nt2::container::domain>))
                            (scalar_<integer_<A2> > )
                          )
  {
    typedef container::table<std::size_t> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const & bins, A2 dim) const
    {
      auto sizee = x.extent();
      std::size_t n = numel(bins);
      sizee[dim-1] = n-1;
      result_type h(sizee);
      for(A2 i=1; i < A2(n) ; i++)
      {
        along(h, i, dim) = inbtrue(logical_and(ge(x, bins(i)), lt(x,  bins(i+1))), dim);
      }
      return h;
    }

  };
} }

#endif
