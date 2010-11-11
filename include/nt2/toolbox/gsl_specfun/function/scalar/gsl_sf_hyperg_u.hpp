//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_HYPERG_U_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTION_SCALAR_GSL_SF_HYPERG_U_HPP_INCLUDED

namespace nt2 { namespace functors
{
  extern "C"{
    double gsl_sf_hyperg_U(int,int,double); 
  }
  template<class Info>
  struct validate<gsl_specfun::gsl_sf_hyperg_U_,tag::scalar_(tag::arithmetic_),Info>
    {
      template<class Sig> struct result;
      template<class This,class A0, class A1, class A2>
      struct result<This(A0, A1, A2)> :
        boost::mpl::and_<
           boost::is_integral<A0>,
           boost::is_integral<A1>,
           meta::has_smaller_size<A2,long double>
        >{};
    };
  /////////////////////////////////////////////////////////////////////////////
  // Compute gsl_sf_hyperg_U(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<gsl_specfun::gsl_sf_hyperg_U_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1, class A2>
    struct result<This(A0, A1, A2)> : boost::result_of<meta::floating(A2)>{};

    NT2_FUNCTOR_CALL_DISPATCH( 3, A2, (3, (float,double,arithmetic_)) )
    NT2_FUNCTOR_CALL_EVAL_IF(3,  float){ return gsl_sf_hyperg_U(a0, a1, a2);}
    NT2_FUNCTOR_CALL_EVAL_IF(3,  double){ return gsl_sf_hyperg_U(a0, a1, a2);}
    NT2_FUNCTOR_CALL_EVAL_IF(3, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(3)::type type;
      return nt2::gsl_specfun::gsl_sf_hyperg_U(type(a0), type(a1), type(a2));
    }
  };
} }


      
#endif
