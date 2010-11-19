//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_LIBC_FUNCTION_SCALAR_FMOD_HPP_INCLUDED
#define NT2_TOOLBOX_LIBC_FUNCTION_SCALAR_FMOD_HPP_INCLUDED

namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Compute fmod(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is long double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<libc::fmod_,tag::scalar_(tag::arithmetic_),long double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2){ return ::fmodl(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<libc::fmod_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2){ return ::fmod(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<libc::fmod_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2){ return ::fmodf(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<libc::fmod_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::libc::fmod(type(a0), type(a1));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
