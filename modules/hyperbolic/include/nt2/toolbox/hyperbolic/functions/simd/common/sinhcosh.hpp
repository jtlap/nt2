//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF(  nt2::tag::sinhcosh_, tag::cpu_,(A0)(A1)(X)
                                  , (boost::mpl::equal_to < nt2::meta::cardinal_of<A0> 
                                                        , nt2::meta::cardinal_of<A1>
                                                        >
                                )
                               , ((simd_<arithmetic_<A0>,X>))
                                 ((simd_<floating_<A1>,X>))
                                 ((simd_<floating_<A1>,X>))
                             )
  {
    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1,A1 & a2) const
    {
      typedef typename meta::as_logical<A1>::type ltype;
      A1 a00 =  nt2::abs(a0); 
      ltype test =  eq(a00, Inf<A1>()); 
      const A1 u = nt2::expm1(a00);
      const A1 up1 = oneplus(u);
      const A1 tmp =u/up1; 
      a1 = negif(is_negative(a0), if_else(test, a00, Half<A1>()*tmp*(oneplus(up1))));
      a2 = if_else(test, a00, oneplus(Half<A1>()*tmp*u)); 
      return 0;
    }
  };
 
  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::sinhcosh_, tag::cpu_,(A0)(A1)(X),
                                (boost::mpl::equal_to<nt2::meta::cardinal_of<A0>, 
                                                 nt2::meta::cardinal_of<A1>
                                        >
                                ),
                                ((simd_ < arithmetic_<A0>,X > ))
                                ((simd_ < floating_<A1>,X > ))
                             )
  {
    typedef A1 result_type;    
    inline result_type operator()(A0 const& a0,A1 & a2) const
    {
      A1 a1;
      sinhcosh(tofloat(a0),a1, a2);
      return a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinhcosh_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
      typedef typename meta::as_floating<A0>::type  rtype;
      typedef boost::fusion::tuple<rtype, rtype> result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::fusion::at_c<0>(res) = sinhcosh(tofloat(a0),
                                              boost::fusion::at_c<1>(res));
      return res;
    }
  };
} }
#endif
