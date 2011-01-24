//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTION_SCALAR_ATAN_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTION_SCALAR_ATAN_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    extern double atan_rn ( double );
    extern double atan_rd ( double );
    extern double atan_rz ( double );
    extern double atan_ru ( double );
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute atan(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Rounding, class Info>
  struct call<crlibm::atan_<Rounding>,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

      template<class A0, class R> struct inner_atan;
    NT2_CRLIBM_INNER_STRUCT(rn, atan, rn)
    NT2_CRLIBM_INNER_STRUCT(rd, atan, rd)
    NT2_CRLIBM_INNER_STRUCT(ru, atan, ru)
    NT2_CRLIBM_INNER_STRUCT(rz, atan, rd)


    NT2_FUNCTOR_CALL(1)
      {return inner_atan<A0,Rounding>::eval(a0, Rounding()); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Rounding, class Info>
  struct call<crlibm::atan_<Rounding>,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::crlibm::atan<Rounding>(double(a0));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
/// No restore -- hand modifications
