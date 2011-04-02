//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTION_SCALAR_ASIN_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTION_SCALAR_ASIN_HPP_INCLUDED

  extern "C"{
    extern double asin_rn ( double );
    extern double asin_rd ( double );
    extern double asin_rz ( double );
    extern double asin_ru ( double );
  };


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(crlibm::tag::asin_<Rounding>, tag::cpu_,
                      (A0)(Rounding),
                      (arithmetic_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Rounding,class Dummy>
  struct call<crlibm::tag::asin_<Rounding>(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::crlibm::asin<Rounding>(double(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(crlibm::tag::asin_<Rounding>, tag::cpu_,
                      (A0)(Rounding),
                      (double_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Rounding,class Dummy>
  struct call<crlibm::tag::asin_<Rounding>(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    template<class A0, class R> struct inner_asin;
    NT2_CRLIBM_INNER_STRUCT(rn, asin, rn)
    NT2_CRLIBM_INNER_STRUCT(rd, asin, rd)
    NT2_CRLIBM_INNER_STRUCT(ru, asin, ru)
    NT2_CRLIBM_INNER_STRUCT(rz, asin, rd)

    NT2_FUNCTOR_CALL(1)
      {return inner_asin<A0,Rounding>::eval(a0, Rounding()); }
  };
} }

#endif
// modified by jt the 29/12/2010