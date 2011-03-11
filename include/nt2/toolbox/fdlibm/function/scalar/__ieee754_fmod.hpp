//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR__IEEE754_FMOD_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR__IEEE754_FMOD_HPP_INCLUDED

  extern "C"{
    extern double fd___ieee754_fmod ( double,double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::__ieee754_fmod_, tag::cpu_,
                                (A0)(A1),
                                (arithmetic_<A0>)(arithmetic_<A1>)
                               )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::__ieee754_fmod_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::fdlibm::__ieee754_fmod(double(a0), double(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::__ieee754_fmod_, tag::cpu_,
                                (A0)(A1),
                                (double_<A0>)(double_<A1>)
                               )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::__ieee754_fmod_(tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2){ return fd___ieee754_fmod(a0, a1); }
  };
} }

#endif
// modified by jt the 29/12/2010