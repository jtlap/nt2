//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_UNARY_MINUS_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_UNARY_MINUS_HPP_INCLUDED

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4146) // unary minus applied to unsigned
#endif

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::unary_minus_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    static A0& a0;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,-a0)
    typedef typename nested::type result_type;

    NT2_FUNCTOR_CALL(1) { return -a0; }
  };
} }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
