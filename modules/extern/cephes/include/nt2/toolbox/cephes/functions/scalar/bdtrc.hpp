//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_BDTRC_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_SCALAR_BDTRC_HPP_INCLUDED
#include <nt2/toolbox/cephes/functions/bdtrc.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>

  extern "C"{
    extern float cephes_bdtrcf ( int,int,float );
    extern double cephes_bdtrc ( int,int,double );
    extern long double cephes_bdtrcl ( int,int,long double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::bdtrc_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return nt2::cephes::bdtrc((a0), (a1), result_type(a2));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::bdtrc_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< double_<A0> >)(scalar_< double_<A1> >)(scalar_< double_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    { return cephes_bdtrc(a0, a1, a2); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::bdtrc_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< single_<A0> >)(scalar_< single_<A1> >)(scalar_< single_<A2> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    { return cephes_bdtrcf(a0, a1, a2); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is long double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::cephes::tag::bdtrc_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (long_double_<A0>)(long_double_<A1>)(long_double_<A2>)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2>::type result_type;

    NT2_FUNCTOR_CALL(3)
    { return cephes_bdtrcl(a0, a1, a2); }
  };
} }


#endif
