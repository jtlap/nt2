//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LEGENDRE_P_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SCALAR_LEGENDRE_P_HPP_INCLUDED
#include <nt2/toolbox/boost_math/specific/interface.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost_math::tag::legendre_p_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0, A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return legendre_p(type(a0), result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( boost_math::tag::legendre_p_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0, A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    { return boost::math::legendre_p(a0, a1, nt2_policy()); }
  };
} }


#endif
