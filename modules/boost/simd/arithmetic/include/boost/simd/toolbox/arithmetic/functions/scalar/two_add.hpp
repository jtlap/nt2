//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_ADD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TWO_ADD_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/two_add.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_add_, tag::cpu_,
                          (A0),
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                         )
  {
    typedef int result_type;
    inline result_type operator()(A0 const& a,A0 const& b,
                                  A0 & r0,A0 & r1) const
    {
      r0 = a+b;
      if (is_invalid(r0))
      {
        r1 = Zero<A0>();
      }
      else
      {
        A0 z = (r0-a);
        r1 =  (a-(r0-z))+(b-z);
      }
      return 0;
    }
  }; 
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_add_, tag::cpu_,
                          (A0),
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                         )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1,A0 & a3) const
    {
      A0 a2;
      two_add(a0, a1, a2, a3); 
      return a2;
    }
  }; 
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::two_add_, tag::cpu_,
                          (A0),
                          ((scalar_<floating_<A0> >))
                          ((scalar_<floating_<A0> >))
                         )
  {
    typedef typename boost::fusion::tuple<A0,A0>        result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type res;
      two_add(a0,a1, boost::fusion::at_c<0>(res),boost::fusion::at_c<1>(res));
      return res;
    }
  };
} } }

#endif
