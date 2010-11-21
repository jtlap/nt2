//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_FAST_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_FAST_FREXP_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct validate<fast_frexp_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::is_floating_point<A0> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_frexp(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<fast_frexp_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::result_of<meta::floating(A0)>::type mantissa;
      typedef typename meta::as_integer<A0,signed>::type          exponent;
      typedef boost::fusion::vector<mantissa,exponent>             type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_CALL_RETURN_TYPE(1)::type res;
      int r1t;
      boost::fusion::at_c<0>(res) = ::frexp(a0, &r1t);
      boost::fusion::at_c<1>(res) = r1t;
      return res;
    }
  };

  template<class Info>
  struct  call<fast_frexp_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename boost::result_of<meta::floating(A0)>::type mantissa;
      typedef typename meta::as_integer<A0,signed>::type          exponent;
      typedef boost::fusion::vector<mantissa,exponent>             type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_CALL_RETURN_TYPE(1)::type res;
      boost::fusion::at_c<0>(res) = ::frexpf(a0, &boost::fusion::at_c<1>(res));
      return res;
    }
  };
} }

#endif
/// Revised by jt the 15/11/2010
