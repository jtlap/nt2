//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SCALAR_LCM_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SCALAR_LCM_HPP_INCLUDED
#include <nt2/include/functions/rdivide.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/gcd.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/is_invalid.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lcm_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
     return nt2::abs(a0*rdivide(a1,gcd(a0,a1)));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
// namespace nt2 { namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lcm_, tag::cpu_
//                             , (A0)(A1)
//                             , (scalar_< floating_<A0> >)(scalar_< floating_<A1> >)
//                             )
//   {

//     typedef typename boost::common_type<A0,A1>::type result_type;

//     NT2_FUNCTOR_CALL(2)
//     {
//       typedef result_type type; 
//       if (is_invalid(a0+a1)) return Nan<type>(); 
//       return nt2::abs(trunc(a0)*(a1/gcd(a0,a1)));
//     }
//   };
// } }


#endif
