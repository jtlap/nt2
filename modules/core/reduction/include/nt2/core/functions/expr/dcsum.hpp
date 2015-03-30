//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DCSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DCSUM_HPP_INCLUDED

#include <nt2/core/functions/dcsum.hpp>
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
  BOOST_DISPATCH_IMPLEMENT  ( dcsum_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 a0)
                          , nt2::dcsum(a0,firstnonsingleton(a0))
                          );
  };


  BOOST_DISPATCH_IMPLEMENT  ( dcsum_, tag::cpu_,
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
      container::table<type_t> x =  sort(a0,'d',n);
      container::table<type_t> s =  along(x, 1, n);
      container::table<type_t> c =  zeros(s.extent(), meta::as_<type_t>());
      container::table<type_t> y(s.extent());
      container::table<type_t> t(s.extent());
      container::table<type_t> v(s.extent());
      container::table<type_t> z(s.extent());
      container::table<type_t> u(s.extent());

      for(std::size_t k = 2; k <=  size(x, n); ++k)
      {
        y = c+along(x,k,n);
        u = along(x,k,n)-(y-c);
        t = y+s;
        v = y-(t-s);
        z = u+v;
        s = t+z;
        c = z-(s-t);
      }
      return s;
    }
  };

} }

#endif
