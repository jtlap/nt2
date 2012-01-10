//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_EXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_EXPONENTBITS_HPP_INCLUDED

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::exponentbits_, tag::cpu_
                            , (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return b_and((2*Maxexponent<A0>()+1)<<Nbmantissabits<A0>(), a0);
    }
  };
} } }


#endif
