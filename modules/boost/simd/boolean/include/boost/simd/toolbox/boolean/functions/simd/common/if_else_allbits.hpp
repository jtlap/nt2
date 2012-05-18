//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ELSE_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ELSE_ALLBITS_HPP_INCLUDED

#include <boost/simd/toolbox/boolean/functions/if_else_allbits.hpp>
#include <boost/simd/toolbox/boolean/functions/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_ornot.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
 BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::if_else_allbits_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                        , boost::simd::meta::cardinal_of<A1>
                                                        >
                                  )
                                , ((simd_<fundamental_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                )
  {
    typedef A1 result_type;
    
    template<class A0_>
    typename enable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    operator()(A0_ const& a0, A1 const& a1) const
    {
      return bitwise_ornot(a1, genmask(a0));
    }
    
    template<class A0_>
    typename disable_if< meta::is_bitwise_logical<A0_>, result_type>::type
    operator()(A0_ const& a0, A1 const& a1) const
    {
      return if_else(a0, a1, Allbits<A1>());
    }
  };
} } }

#endif
