//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/simd/shri.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_, tag::cpu_, (A0)(A1)(X)
                            , ( boost::is_same<typename dispatch::meta::as_integer<A0>::type, A1> )
                            , ((simd_< floating_<A0>, X>))
                              ((simd_< floating_<A0>, X>))    
                              ((simd_< integer_<A1>, X>))
                            )
  {
    typedef int result_type;
    inline int operator()(A0 const& a0,A0 & r0,A1 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::scalar_of<int_type>::type        sint_type;
      typedef typename meta::scalar_of<A0>::type                 s_type;
      const sint_type me = Maxexponent<s_type>()-1;
      const sint_type nmb= Nbmantissabits<s_type>();
      const int_type vn1 = boost::simd::splat<int_type>((2*me+3)<<nmb);
      const sint_type n2 = me<<nmb;
      r1 = b_and(vn1, a0);                                 //extract exponent
      A0 x = b_andnot(a0, vn1);                            //clear exponent in a0
      r1 = shri(r1,nmb) - splat<int_type>(me);             //compute exponent
      r0 = b_or(x,splat<int_type>(n2));                    //insert expon+1 in x
      return 0;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_, tag::cpu_, (A0)(A1)(X)
                                 , ( boost::is_same<typename dispatch::meta::as_integer<A0>::type, A1>)
                                 , ((simd_< floating_<A0>, X>))
                                   ((simd_< integer_<A1>, X>))
                            )
  {
    typedef A0 result_type;    
    inline A0 operator()(A0 const& a0,A1 & a2) const
    {
      A0 a1; 
      boost::simd::fast_frexp(a0, a1, a2);
      return a1; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::fast_frexp_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type  exponent;
    typedef boost::fusion::vector<A0,exponent>        result_type;
     
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      result_type res;
      boost::simd::fast_frexp( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          );
      return res;
    }
  };
} } }
#endif
