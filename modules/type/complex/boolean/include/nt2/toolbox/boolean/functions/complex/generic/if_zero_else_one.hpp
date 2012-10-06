//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define NT2_TOOLBOX_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#include <boost/simd/toolbox/boolean/functions/if_zero_else_one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_zero_else_one_, tag::cpu_, (A0)(A1)
                                     , (scalar_< logical_<A0> >)
                                     (generic_< complex_<floating_<A1> > >)
                                     )
  {
    typedef A1 result_type;
    
   template<class A0_>
    typename enable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    operator()(A0_ const& a0, A1 const& a1) const
    {
      return bitwise_andnot(a1, genmask(a0));
    }
    
    template<class A0_>
    typename disable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    operator()(A0_ const& a0, A1 const& a1) const
    {
      return if_else_one(a0, Zero<A1>(),a1);
    }
  };

} } }

#endif
