//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SQRT1PM1_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SQRT1PM1_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/oneminus.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sqrt1pm1_, tag::cpu_,
                          (A0),
                          (arithmetic_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sqrt1pm1_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return sqrt1pm1(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sqrt1pm1_, tag::cpu_,
                          (A0),
                          (real_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sqrt1pm1_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return boost::math::sqrt1pm1(a0);
    }
  };
} }

#endif
// modified by jt the 26/12/2010