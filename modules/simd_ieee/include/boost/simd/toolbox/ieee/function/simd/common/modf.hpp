//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MODF_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/include/functions/trunc.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::modf_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
      typedef typename meta::strip<A0>::type                A00;
      typedef boost::fusion::vector<A00, A00>       result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type type;
      type res;
      eval(a0,boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  private:
    template<class AA0,class R0,class R1> inline void
    eval(AA0 const& a0, R0& r0, R1& r1)const
    {
      r1 = boost::simd::trunc(a0);
      r0 = a0-r1;
    }
  };
} } }
#endif
