//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SCALAR_IS_INCLUDED_C_HPP_INCLUDED
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_equal.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_c_, tag::cpu_, (A0)
                            , (scalar_< fundamental_<A0> >)
			      (scalar_< fundamental_<A0> >)
                            )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (bitwise_ornot(a1, a0) == a1); 
    }
  };
} } }

#endif
