//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELSUB_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELSUB_HPP_INCLUDED



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::selsub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)(scalar_< fundamental_<A1> >)(scalar_< fundamental_<A2> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A1,A2)>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      if (a0) return type(a1)-type(a2); else return type(a1);
    }
  };
} }


#endif
