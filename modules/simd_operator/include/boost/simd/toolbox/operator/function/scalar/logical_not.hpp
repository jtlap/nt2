//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SCALAR_LOGICAL_NOT_HPP_INCLUDED

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::logical_not_, tag::cpu_, (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1) { return !a0; }
  };
} }

#endif
