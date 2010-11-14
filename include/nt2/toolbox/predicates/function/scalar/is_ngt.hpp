//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NGT_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NGT_HPP_INCLUDED

#include <nt2/include/functions/is_nan.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for is_ngt

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_ngt(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_ngt_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
       return ((a0 <= a1) || is_nan(a0)|| is_nan(a1));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_ngt_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
       return a0 <= a1;
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
