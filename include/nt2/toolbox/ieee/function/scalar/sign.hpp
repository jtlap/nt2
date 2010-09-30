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
  template<class Info>
  struct call<sign_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (3, (real_,unsigned_,signed_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
       return is_nan(a0)?a0:is_gtz(a0)-is_ltz(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,   unsigned_)
    {
        return is_nez(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     signed_)
    {
       return is_gtz(a0)-is_ltz(a0);
    }
  };
} }


      
#endif
