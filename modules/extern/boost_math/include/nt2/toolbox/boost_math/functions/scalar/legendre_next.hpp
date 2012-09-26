//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_LEGENDRE_NEXT_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTIONS_SCALAR_LEGENDRE_NEXT_HPP_INCLUDED


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A2 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::legendre_next_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< arithmetic_<A2> >)(scalar_< arithmetic_<A3> >)(scalar_< arithmetic_<A4> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2, A3, A4>::type result_type;

    NT2_FUNCTOR_CALL(5)
    {
      return legendre_next(a0, a1, result_type(a2), result_type(a3), result_type(a4));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::boost_math::tag::legendre_next_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)(scalar_< floating_<A2> >)(scalar_< floating_<A3> >)(scalar_< floating_<A4> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A2, A3, A4>::type result_type;

    NT2_FUNCTOR_CALL(5)
    { return boost::math::legendre_next(a0, a1, a2, a3, a4); }
  };
} }


#endif
