//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_POLEVL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_POLEVL_HPP_INCLUDED
#include <nt2/include/functions/tchebeval.hpp>
#include <nt2/toolbox/polynomials/category.hpp>

namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Compute polevl(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<polevl_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typename A1::const_iterator p = a1.begin();
      A0 ans = *p++;
      do
	ans = fma(ans, a0, *p);
      while( ++p !=  a1.end());
      return ans;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return polevl(type(a0), a1);
    }
  };
} }


      
#endif
