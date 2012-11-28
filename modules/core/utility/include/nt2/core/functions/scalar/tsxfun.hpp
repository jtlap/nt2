//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_TSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_TSXFUN_HPP_INCLUDED

#include <nt2/core/functions/tsxfun.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates from a 3ary thing and 3 scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tsxfun_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                            )
  {
    typedef typename
            meta::result_of<A0 const(A1 const&, A2 const&, A3 const&)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2,
                                             A2 const& a3) const
    {
      return a0(a1,a2,a3);
    }
  };
} }

#endif
