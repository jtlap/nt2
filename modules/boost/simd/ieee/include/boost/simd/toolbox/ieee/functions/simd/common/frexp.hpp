//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/bitwise_notand.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::frexp_, tag::cpu_, (A0)(A1)(A2)(X)
                                  ,( boost::mpl::and_ <
                                     boost::is_same<A0,A1>, 
                                     boost::is_same<typename dispatch::meta::as_integer<A0>::type, A2>
                                     >
                                  )
                            , ((simd_< floating_<A0>, X>))
                              ((simd_< floating_<A1>, X>))    
                              ((simd_< integer_<A2>, X>))
                            )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0,A1 & r0,A2 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::scalar_of<int_type>::type        sint_type;
      typedef typename meta::scalar_of<A0>::type                 s_type;
      const sint_type me = Maxexponent<s_type>()-1;
      const sint_type nmb= Nbmantissabits<s_type>();
      const sint_type n1 = ((2*me+3)<<nmb);
      const sint_type n2 = me<<nmb;
      const  int_type vme = splat<int_type>(me);
      A0 ci_exp=simd::native_cast<A0>(splat< int_type>(n1));
      r1 = simd::native_cast<int_type>(b_and(ci_exp, a0));// extract exponent
      A0 x = b_notand(ci_exp, a0);                        // clear exponent in a0
      r1 = sub(shri(r1,nmb), vme);                        // compute exponent
      r0 = b_or(x,splat<int_type>(n2));                   // insert exponent+1 in x
      A0 test0 = is_nez(a0);
      int_type test1 = gt(r1,vme);
      r1 = b_and(r1, b_notand(test1, test0));
      r0 = b_and(seladd(test1,r0,a0), test0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::frexp_, tag::cpu_, (A0)(A2)(X)
                                 , ( boost::is_same<typename dispatch::meta::as_integer<A0>::type, A2>)
                                 , ((simd_< floating_<A0>, X>))
                                   ((simd_< integer_<A2>, X>))
                            )
  {
    typedef A0 result_type;    
    inline void operator()(A0 const& a0,A2 & a2) const
    {
      A0 a1; 
      boost::simd::frexp(a0, a1, a2);
      return a1; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::frexp_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type  exponent;
    typedef boost::fusion::vector<A0,exponent>           result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::simd::frexp( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          );
      return res;
    }
  };
} } }

#endif
