//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_LEGENDRE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_LEGENDRE_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/abs.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<legendre_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :meta::is_integral<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute legendre(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<legendre_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> : 
      boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      if(nt2::abs(a1) > 1) return Nan<A1>(); 
      A1 p0 = One<A1>();
      if(a0 == 0)  return p0;
      A1 p1 = a1;
      uint32_t n = 1;
      
      while(n < a0)
	{
	  std::swap(p0, p1);
	  p1 = legendre_next(n, a1, p0, p1);
	  ++n;
	}
      return p1;
    }
  private :
    template <class T1, class T2, class T3 >
    static inline T1 
    legendre_next(const uint32_t& l,const T1& x, const T2& Pl, const T3& Plm1)
    {
      return ((2 * l + 1) * x * Pl - l * Plm1) / (l + 1);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<legendre_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> : 
      boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return legendre(a0, type(a1));
    }
  };

} }

#endif
/// Revised by jt the 14/11/2010
