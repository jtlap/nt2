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


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::legendre_, tag::cpu_,
                          (A0)(A1),
                          (integer_<A0>)(arithmetic_<A1>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::legendre_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :
      std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return legendre(a0, type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::legendre_, tag::cpu_,
                          (A0)(A1),
                          (integer_<A0>)(real_<A1>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::legendre_(tag::integer_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> :
      std::tr1::result_of<meta::floating(A1)>{};

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
} }

#endif
// modified by jt the 26/12/2010
