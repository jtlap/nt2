//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_BESSEL_JN_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_BESSEL_JN_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    double gsl_sf_bessel_Jn(int, double); 
  }
  template<class Info>
  struct validate<gsl_specfun::gsl_sf_bessel_Jn_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1>
      struct result<This(A0, A1)> :
        boost::mpl::and_<
           boost::is_integral<A0>,
           meta::has_smaller_size<A1,long double>
        >{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute gsl_sf_bessel_Jn(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gsl_specfun::gsl_sf_bessel_Jn_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return gsl_sf_bessel_Jn(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gsl_specfun::gsl_sf_bessel_Jn_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2){ return gsl_sf_bessel_Jn(a0, a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A1 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gsl_specfun::gsl_sf_bessel_Jn_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::gsl_specfun::gsl_sf_bessel_Jn(type(a0), type(a1));
    }
  };

} }

#endif
/// Revised by jt the 16/11/2010
