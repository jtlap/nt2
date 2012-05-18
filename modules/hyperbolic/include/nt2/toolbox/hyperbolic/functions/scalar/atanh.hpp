//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_ATANH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_ATANH_HPP_INCLUDED
#include <nt2/toolbox/hyperbolic/functions/atanh.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>

#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sign.hpp>
#include <nt2/include/functions/scalar/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::atanh(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 absa0 = nt2::abs(a0);
      //     const A0 small_mask    = lt(absa0, Twotom10<A0>());  /* x <  2**-10 */
      //     if (small_mask) { return a0*fma(Third<A0>(), sqr(a0), One<A0>()); }
      A0 t =  absa0+absa0;
      if (absa0 < Half<A0>())
	return sign(a0)*Half<A0>()*log1p(t+t*absa0/(One<A0>()-absa0));
      else
	return sign(a0)*Half<A0>()*log1p(t/(One<A0>()-absa0));
    }
  };
} }


#endif
