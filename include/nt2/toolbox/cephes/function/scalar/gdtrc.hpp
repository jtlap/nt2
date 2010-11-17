//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_GDTRC_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_GDTRC_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    extern float cephes_gdtrcf ( float,float,float );
    extern double cephes_gdtrc ( double,double,double );
    extern long double cephes_gdtrcl ( long double,long double,long double );
  }
  /////////////////////////////////////////////////////////////////////////////
  // Compute gdtrc(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::gdtrc_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_gdtrcf(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::gdtrc_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_gdtrc(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is long double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::gdtrc_,tag::scalar_(tag::arithmetic_),long double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_gdtrcl(a0, a1, a2); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cephes::gdtrc_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_CALL_RETURN_TYPE(3)::type type;
      return nt2::cephes::gdtrc(type(a0), type(a1), type(a2));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
