//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FROM_DIAG_HPP_INCLUDED

#include <nt2/core/functions/from_diag.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // from_diag build a diagonal matrix from a scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::from_diag_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const { return a0; }
  };
} }

#endif
