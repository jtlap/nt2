//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_SUM_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <nt2/sdk/meta/strip.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::sum_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename meta::result_of<meta::arithmetic(base)>::type  result_type;
    
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type     type;
      return boost::fusion::fold(a0,Zero<type>(),functor<tag::plus_>());
    }
  };
} }
#endif
