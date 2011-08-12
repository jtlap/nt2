//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_MODF_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/simd/include/functions/trunc.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::modf_, tag::cpu_,
                      (A0)(A1),
                      (scalar_ < arithmetic_<A0> > )
                      (scalar_ < arithmetic_<A1> > )
                      (scalar_ < arithmetic_<A1> > )
                     )
  {  
    typedef boost::simd::int32_t result_type;    
    inline int32_t operator()(A0 const& a0,A1 & r1,A1 & r0) const
    {
      r1 = boost::simd::trunc(a0);
      r0 = a0 - r1;
      return 0; 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::modf_, tag::cpu_,
                      (A0)(A1),
                      (scalar_ < arithmetic_<A0> > )
                      (scalar_ < arithmetic_<A1> > )
                     )
  {  
    typedef A1 result_type;    
    inline A1 operator()(A0 const& a0,A1 & a1) const
    {
      a1 = boost::simd::trunc(a0);
      return a0 - a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::modf_, tag::cpu_,
                      (A0),
                      (scalar_ < arithmetic_<A0> > )
                     )
  {
      typedef typename dispatch::meta::result_of<dispatch::meta::floating(A0)>::type  etype;
      typedef boost::fusion::vector<etype, etype>        result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::fusion::at_c<0>(res) = boost::simd::modf(a0, boost::fusion::at_c<1>(res));
      return res;
    }
  };
} } }
#endif
