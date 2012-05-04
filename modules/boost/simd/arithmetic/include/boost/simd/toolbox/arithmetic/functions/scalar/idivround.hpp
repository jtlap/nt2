//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVROUND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_IDIVROUND_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/scalar/round2even.hpp>
#include <boost/simd/include/functions/scalar/rdivide.hpp>
#include <boost/simd/include/functions/scalar/iround.hpp>
#include <boost/simd/include/functions/scalar/tofloat.hpp>

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::idivround_, tag::cpu_
                        , (A0)
                        , (scalar_< arithmetic_<A0> >)
                        (scalar_< arithmetic_<A0> >)
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
      return (!a1) ? a1 :iround(tofloat(a0)/tofloat(a1));
      }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::idivround_, tag::cpu_,
                       (A0),
                       (scalar_< floating_<A0> > )
                       (scalar_< floating_<A0> > )
                       )
  {
    typedef typename dispatch::meta::as_integer < A0 >::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return iround(a0/a1);
    }
  };
} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
