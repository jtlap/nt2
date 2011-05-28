//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMALN_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMALN_HPP_INCLUDED

#include <nt2/toolbox/euler/details/math.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <boost/math/special_functions/gamma.hpp>

#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/signnz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type is double_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gammaln_, tag::cpu_,
                         (A0),
                         (real_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gammaln_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 == Inf<A0>()) | is_eqz(a0) ) return Inf<A0>(); 
      if ((a0 < Zero<A0>()) | is_invalid(a0)) return Nan<A0>();
    #ifdef NT2_TOOLBOX_EULER_HAS_LGAMMA
      return ::lgamma(a0);
    #else
      return boost::math::lgamma(a0);
    #endif
    }

  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is float_
/////////////////////////////////////////////////////////////////////////////
#ifdef NT2_TOOLBOX_EULER_HAS_LGAMMAF
NT2_REGISTER_DISPATCH(tag::gammaln_, tag::cpu_,
                         (A0),
                         (float_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gammaln_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 == Inf<A0>()) | is_eqz(a0) ) return Inf<A0>(); 
      if ((a0 < Zero<A0>()) | is_invalid(a0)) return Nan<A0>();
      return ::lgammaf(a0);
    }

  };
} }
#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gammaln_, tag::cpu_,
                         (A0),
                         (arithmetic_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gammaln_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::gammaln(type(a0)); 
    }

  };
} }

#endif
// modified by jt the 26/12/2010
