//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_SCALAR_GSL_SF_ERF_Z_HPP_INCLUDED
#define NT2_TOOLBOX_GSL_SPECFUN_FUNCTIONS_SCALAR_GSL_SF_ERF_Z_HPP_INCLUDED

  extern "C"{
    extern double gsl_sf_erf_Z ( double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::gsl_specfun::tag::gsl_sf_erf_z_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::gsl_specfun::gsl_sf_erf_z(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::gsl_specfun::tag::gsl_sf_erf_z_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { return gsl_sf_erf_Z(a0); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::gsl_specfun::tag::gsl_sf_erf_z_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    { return gsl_sf_erf_Z(a0); }
  };
} }


#endif
