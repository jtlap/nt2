//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_HERMITE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_HERMITE_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/constant/digits.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<hermite_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :boost::is_integral<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute hermite(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<hermite_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A1,
      (2, (real_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  real_)
    {
      A0 p0 = One<A1>();
      if(a0 == 0) return p0;
      A0 p1 = a0+a0;
      uint32_t c = 1;
      while(c < a0)
	{
	  std::swap(p0, p1);
	  p1 = hermite_next(c, a1, p0, p1);
	  ++c;
	}
      return p1;
      //return boost::math::tr1::hermite(a0, a1); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::hermite(a0, type(a1)); 
    }
  private:
    template <class T>
    static inline T 
    hermite_next(uint32_t n, T x, T Hn, T Hnm1)
    {
      return (2 * x * Hn - 2 * n * Hnm1);
    }
  };
} }


      
#endif
