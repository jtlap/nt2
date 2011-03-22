//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_INCBET_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_INCBET_HPP_INCLUDED

  extern "C"{
    extern float cephes_incbetf ( float,float,float );
    extern double cephes_incbet ( double,double,double );
    extern long double cephes_incbetl ( long double,long double,long double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::incbet_, tag::cpu_,
                        (A0)(A1)(A2),
                        (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::incbet_(tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      return nt2::cephes::incbet(type(a0), type(a1), type(a2));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::incbet_, tag::cpu_,
                        (A0)(A1)(A2),
                        (double_<A0>)(double_<A1>)(double_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::incbet_(tag::double_,tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_incbet(a0, a1, a2); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::incbet_, tag::cpu_,
                        (A0)(A1)(A2),
                        (float_<A0>)(float_<A1>)(float_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::incbet_(tag::float_,tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_incbetf(a0, a1, a2); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is long double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::incbet_, tag::cpu_,
                        (A0)(A1)(A2),
                        (long_double_<A0>)(long_double_<A1>)(long_double_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::incbet_(tag::long_double_,tag::long_double_,tag::long_double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(3){ return cephes_incbetl(a0, a1, a2); }
  };
} }

#endif
// modified by jt the 29/12/2010