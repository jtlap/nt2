//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_YN_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTION_SCALAR_YN_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>

  extern "C"{
    extern float cephes_ynf ( int,float );
    extern double cephes_yn ( int,double );
    extern long double cephes_ynl ( int,long double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( cephes::tag::yn_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::cephes::yn(a0, type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( cephes::tag::yn_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return cephes_yn(a0, a1); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( cephes::tag::yn_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< float_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return cephes_ynf(a0, a1); }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is long double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( cephes::tag::yn_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(long_double_<A1>)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return cephes_ynl(a0, a1); }
  };
} }


#endif
