//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_YN_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_YN_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>

namespace nt2 { namespace functors
{
  extern "C"{
    extern float cephes_ynf ( int,float );
    extern double cephes_yn ( int,double );
    extern long double cephes_ynl ( int,long double );
  }
  template<class Info>
  struct validate<cephes::yn_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1>
      struct result<This(A0, A1)> :
         meta::is_integral<A0>{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute yn(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::yn_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_ynf(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::yn_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_yn(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is long double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::yn_,tag::scalar_(tag::arithmetic_),long double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_ynl(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::yn_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::cephes::yn((a0), type(a1));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
