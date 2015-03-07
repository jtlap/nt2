//==============================================================================
//         Copyright 2015   J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_ISPOSITIVEDEFINITE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_ISPOSITIVEDEFINITE_HPP_INCLUDED

#include <nt2/predicates/functions/ispositivedefinite.hpp>
#include <nt2/include/functions/ishermitian.hpp>
#include <nt2/include/functions/chol.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( ispositivedefinite_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      typedef typename A0::value_type type_t;
      if(!ishermitian(a0)) return false;
      int p;
      container::table<type_t> t;
      tie(t, p) = chol(a0, nt2::raw_);
      return p == 0;
    }
  };
} }

#endif
