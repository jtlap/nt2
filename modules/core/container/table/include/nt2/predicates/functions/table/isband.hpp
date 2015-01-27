//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISBAND_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISBAND_HPP_INCLUDED

#include <nt2/predicates/functions/isband.hpp>
#include <nt2/include/functions/bandwidth.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( isband_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_ < integer_<A1> > )
                              (scalar_ < integer_<A2> > )
                            )
  {
    typedef bool result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 l, A2 u) const
    {
      auto r = bandwidth(a0);
      return (l <= A1(boost::fusion::at_c<0>(r)))&&(A2(boost::fusion::at_c<1>(r))<= u);
    }
  };
} }

#endif
