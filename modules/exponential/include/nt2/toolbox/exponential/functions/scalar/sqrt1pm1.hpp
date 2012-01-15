//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_SQRT1PM1_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_SQRT1PM1_HPP_INCLUDED
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt1pm1_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return sqrt1pm1(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt1pm1_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp = sqrt(oneplus(a0)); 
      return lt(nt2::abs(a0), Half<A0>()) ? a0/(oneplus(tmp) : minusone(tmp); 
    }
  };
} }


#endif
