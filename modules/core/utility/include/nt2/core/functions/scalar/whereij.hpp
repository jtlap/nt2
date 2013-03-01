//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_WHEREIJ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_WHEREIJ_HPP_INCLUDED

#include <nt2/core/functions/whereij.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  /// Generates whereij_ from a 2ary functor and 2 scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::whereij_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename
            meta::result_of<A0 const(A1 const&, A2 const&)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return if_else(a0(0, 0),a1,a2);
    }
  };
} }

#endif
