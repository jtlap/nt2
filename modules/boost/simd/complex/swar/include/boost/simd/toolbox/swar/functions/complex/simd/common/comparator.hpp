//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_COMPARATOR_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/comparator.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/any.hpp>
#include <boost/simd/include/functions/is_not_equal_with_equal_nans.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::comparator_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((scalar_<integer_<A1> >))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                             ((simd_<complex_ <arithmetic_<A0> >,X>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1,const A1 & a2, A0 & r0, A0 & r1) const
    {
      if (a2)
      {
        r1 =  boost::simd::min(a0, a1);
        r0 =  boost::simd::max(a0, a1);
      }
      else
      {
        r0 =  boost::simd::min(a0, a1);
        r1 =  boost::simd::max(a0, a1);
      }
      return boost::simd::any(is_not_equal_with_equal_nans(a0, r0)); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::comparator_, tag::cpu_,
                             (A0)(A1)(X),
                             ((simd_<complex_ < arithmetic_<A0> >,X>))
                             ((simd_<complex_ < arithmetic_<A0> >,X>))
                             ((scalar_<integer_<A1> >))
                            )
  {
    typedef boost::fusion::vector<A0,A0,bool>           result_type;
    inline result_type operator()(A0 const& a0,A0 const & a1,const A1 & a2) const
    {
      result_type res;
      boost::fusion::at_c<2>(res) = boost::simd::comparator(a0, a1, a2, boost::fusion::at_c<0>(res),  boost::fusion::at_c<1>(res)); 
      return res; 
    }
  };
} } }
#endif
