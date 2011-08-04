//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_ANP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_ANP_HPP_INCLUDED
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/is_ngez.hpp>
#include <nt2/include/functions/exp.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::anp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)(scalar_< fundamental_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::result_of<meta::floating(A0, A1)>::type type;
      typedef result_type rtype;
      if (is_ngez(a0)||is_ngez(a1)) return (rtype)Nan<type>();
      if (lt(a0,a1)) return (rtype)Zero<type>();
      const type n = oneplus(round2even(a0));
      const type p = round2even(a1);
      return (rtype)round2even(exp(gammaln(n)-gammaln(n-p)));
    }
  };
} }


#endif
