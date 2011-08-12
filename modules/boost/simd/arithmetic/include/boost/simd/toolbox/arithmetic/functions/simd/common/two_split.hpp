//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TWO_SPLIT_HPP_INCLUDED
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_split_, tag::cpu_,
                            (A0)(X),
                            ((simd_<arithmetic_<A0>,X>))
                           )
  {
      typedef A0                    str_t;
      typedef typename boost::fusion::tuple<str_t, str_t>        result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      eval(a0,boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private :
    template<class AA0,class R0,class R1> inline void
    eval(AA0 const& a, R0& r0, R1& r1)const
    {
      using boost::simd::Splitfactor;

      typedef typename meta::scalar_of<A0>::type s_type;
      AA0 c = Splitfactor<A0>()*a  ;
      r0 =  c-(c-a);
      r1 = a-r0;
    }
  };
} } }
#endif
