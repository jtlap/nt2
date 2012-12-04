//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_HYP2F1_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_HYP2F1_HPP_INCLUDED

  extern "C"{
    extern float cephes_hyp2f1f ( float,float,float,float );
    extern double cephes_hyp2f1 ( double,double,double,double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::hyp2f1_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)(scalar_< arithmetic_<A3> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(4)
    {
      return nt2::cephes::hyp2f1(result_type(a0), result_type(a1), result_type(a2), result_type(a3));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::hyp2f1_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< double_<A0> >)(scalar_< double_<A1> >)(scalar_< double_<A2> >)(scalar_< double_<A3> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(4)
    { return cephes_hyp2f1(a0, a1, a2, a3); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::hyp2f1_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< single_<A0> >)(scalar_< single_<A1> >)(scalar_< single_<A2> >)(scalar_< single_<A3> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(4)
    { return cephes_hyp2f1f(a0, a1, a2, a3); }
  };
} }


#endif
