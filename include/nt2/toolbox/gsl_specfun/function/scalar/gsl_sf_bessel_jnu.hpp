//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_BESSEL_JNU_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_BESSEL_JNU_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    extern double gsl_sf_bessel_Jnu ( double,double );
  }
  template<class Info>
  struct validate<gsl_specfun::gsl_sf_bessel_Jnu_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1>
      struct result<This(A0, A1)> :
        boost::mpl::and_<
           meta::has_smaller_size<A0,long double>,
           meta::has_smaller_size<A1,long double>
        >{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute gsl_sf_bessel_Jnu(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gsl_specfun::gsl_sf_bessel_Jnu_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : boost::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH( 2, A1, (3, (float,double,arithmetic_)) )
    NT2_FUNCTOR_CALL_EVAL_IF(2,  float){ return gsl_sf_bessel_Jnu(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2,  double){ return gsl_sf_bessel_Jnu(a0, a1);}
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::gsl_specfun::gsl_sf_bessel_Jnu(type(a0), type(a1));
    }
  };
} }


      
#endif
