//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CSUM_HPP_INCLUDED

#include <nt2/core/functions/csum.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/ifloor.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/sdk/meta/as.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( csum_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , nt2::csum(a0,firstnonsingleton(a0))
                          );
  };


  BOOST_DISPATCH_IMPLEMENT  ( csum_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::value_type type_t;
    typedef container::table<type_t> result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& n) const
    {
      if (size(a0, n) <= 1) return a0;
      container::table<type_t> y =  along(a0, 1, n);
      container::table<type_t> s =  zeros(y.extent(), meta::as_<type_t>());
      container::table<type_t> tmp;
      container::table<type_t> e = s;
      for(std::size_t k = 2; k <=  size(a0, n); ++k)
      {
        tmp = s;
        y = along(a0,k,n)+e;
        s = tmp+y;
        e = (tmp-s)+y;
      }
      return s;
    }
  };

} }

#endif
