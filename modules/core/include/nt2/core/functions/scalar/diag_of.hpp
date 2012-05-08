//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_DIAG_OF_HPP_INCLUDED

#include <nt2/core/functions/diag_of.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // diag_of extracts the diagonal of a scalar value
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diag_of_, tag::cpu_
                              , (A0)
                              , (scalar_< arithmetic_<A0> >)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const { return a0; }
  };
  //============================================================================
  // diag_of extracts the diagonal of a scalar value
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_diag_of_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_< arithmetic_<A0> >)
                                (scalar_< integer_<A1> >)
                              )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(a1 == 1, "diag_of cannot be called on a scalar to return an empty array"); 
      return a0;
    }
  };
} }

#endif
