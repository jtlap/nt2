//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SIGN_HPP_INCLUDED

#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for sign

  /////////////////////////////////////////////////////////////////////////////
  // Compute sign(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sign_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return is_nan(a0)?a0:is_gtz(a0)-is_ltz(a0);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sign_,tag::scalar_(tag::arithmetic_),unsigned_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
        return is_nez(a0);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is signed_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<sign_,tag::scalar_(tag::arithmetic_),signed_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return is_gtz(a0)-is_ltz(a0);
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010
