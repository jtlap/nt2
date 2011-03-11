//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/is_nan.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ulpdist_, tag::cpu_,
                         (A0)(A1),
                         (arithmetic_<A0>)(arithmetic_<A1>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ulpdist_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return dist(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is bool_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ulpdist_, tag::cpu_,
                         (A0)(A1),
                         (bool_<A0>)(bool_<A1>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ulpdist_(tag::bool_,tag::bool_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return dist(a0, is_nez(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ulpdist_, tag::cpu_,
                         (A0)(A1),
                         (real_<A0>)(real_<A1>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ulpdist_(tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename std::tr1::result_of<meta::arithmetic(A0, A1) >::type type;
      typedef typename meta::as_integer<A0>::type itype;
      if (a0 == a1)               return Zero<type>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<type>();
      itype e1, e2;
      type m1, m2;
      boost::fusion::tie(m1, e1) = nt2::frexp(type(a0));
      boost::fusion::tie(m2, e2) = nt2::frexp(type(a1));
      itype expo = -nt2::max(e1, e2);
      double e = (e1 == e2) ? nt2::abs(m1-m2)
      : nt2::abs(nt2::ldexp(a0, expo)-nt2::ldexp(a1, expo));
      return e/Eps<type>();
    }
  };
} }

#endif
// modified by jt the 26/12/2010
