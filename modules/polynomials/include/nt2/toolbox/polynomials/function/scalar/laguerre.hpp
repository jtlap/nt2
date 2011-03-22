//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_LAGUERRE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_LAGUERRE_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/oneplus.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::laguerre_, tag::cpu_,
                          (A0)(A1),
                          (integer_<A0>)(arithmetic_<A1>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::laguerre_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::laguerre(a0, type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::laguerre_, tag::cpu_,
                          (A0)(A1),
                          (integer_<A0>)(real_<A1>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::laguerre_(tag::integer_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      A1 p0 = One<A1>();
      if(a0 == 0) return p0;
      A1 p1 = p0-a1;
      A0 c = 1;
      while(c < a0)
      {
        std::swap(p0, p1);
        p1 = laguerre_next(c, a1, p0, p1);
        ++c;
      }
      return p1;
    }
  private:
    template <class T, class T1, class T2>
    static inline T
    laguerre_next(const uint32_t& n, const T& x, const T1 &Ln, const T2& Lnm1)
    {
      const T np1 = oneplus(n);
      return ((n + np1 - x) * Ln - n *Lnm1) / np1;
    }
  };
} }

#endif
// modified by jt the 26/12/2010
