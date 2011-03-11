//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_PDTRC_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_PDTRC_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>

  extern "C"{
    extern float cephes_pdtrcf ( int,float );
    extern double cephes_pdtrc ( int,double );
    extern long double cephes_pdtrcl ( int,long double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::pdtrc_, tag::cpu_,
                       (A0)(A1),
                       (arithmetic_<A0>)(arithmetic_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::pdtrc_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::cephes::pdtrc((a0), type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::pdtrc_, tag::cpu_,
                       (A0)(A1),
                       (double_<A0>)(double_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::pdtrc_(tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_pdtrc(a0, a1); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::pdtrc_, tag::cpu_,
                       (A0)(A1),
                       (float_<A0>)(float_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::pdtrc_(tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_pdtrcf(a0, a1); }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is long double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(cephes::tag::pdtrc_, tag::cpu_,
                       (A0)(A1),
                       (long_double_<A0>)(long_double_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<cephes::tag::pdtrc_(tag::long_double_,tag::long_double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return cephes_pdtrcl(a0, a1); }
  };
} }

#endif
// modified by jt the 29/12/2010