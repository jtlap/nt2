//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVFIX_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVFIX_HPP_INCLUDED

#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/rdivide.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivfix_, tag::cpu_, (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;
    NT2_FUNCTOR_CALL(2) { return rdivide(a0, a1); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::idivfix_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> > )(scalar_< real_<A1> > )
                            )

  {
    typedef typename meta::
            as_integer < typename meta::
                                  result_of<meta::arithmetic(A0,A1)>::type
                       >::type                                      result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type type;
      const type z = a0/a1; 
      return is_nan(z) ? Zero<result_type>() : result_type(trunc(z)); //TO DO itrunc
    }
  };
} }

#endif
