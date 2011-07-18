//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELADD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELADD_HPP_INCLUDED

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::seladd_, tag::cpu_, (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)
                              (scalar_< fundamental_<A1> >)
                              (scalar_< fundamental_<A2> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A1,A2)>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(3)
    {
      if(a0) return result_type(a1) + result_type(a2);
      else   return result_type(a1);
    }
  };
} }

#endif
