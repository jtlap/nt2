//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LAGUERRE_NEXT_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LAGUERRE_NEXT_HPP_INCLUDED


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( boost_math::tag::laguerre_next_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< arithmetic_<A2> >)(scalar_< arithmetic_<A3> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1, A2, A3)>::type result_type;

    NT2_FUNCTOR_CALL(4)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::boost_math::laguerre_next(a0, type(a1), type(a2), type(a3));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( boost_math::tag::laguerre_next_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< integer_<A0> >)(scalar_< real_<A1> >)(scalar_< real_<A2> >)(scalar_< real_<A3> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A1, A2, A3)>::type result_type;

    NT2_FUNCTOR_CALL(4)
    { return boost::math::laguerre_next(a0, a1, a2, a3); }
  };
} }


#endif
