//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/include/constants/digits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::minusone_, tag::cpu_,
			     (A0),
			     (scalar_ < fundamental_<A0> > )
			     )
  {
//     typedef typename meta::strip<A0>::type sA0; 
//     typedef typename meta::result_of<meta::arithmetic(sA0)>::type tmp;
    typedef typename meta::as_signed<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return result_type(a0)-One<result_type>();
    }

  };
} }

#endif
