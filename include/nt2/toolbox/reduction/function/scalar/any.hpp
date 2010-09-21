//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_ANY_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_ANY_HPP_INCLUDED

#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<any_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute any(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<any_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(1) { return is_nez(a0); }
  };
} }


      
#endif
