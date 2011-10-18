//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_NAN_ELSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_NAN_ELSE_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/is_simd_logical.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::if_nan_else_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                        , boost::simd::meta::cardinal_of<A1>
                                                        >
                                  )
                                , (boost::simd::tag::if_nan_else_ ( simd_<arithmetic_<A0>,X>
                                                , simd_<arithmetic_<A1>,X>
                                                )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                )
  {
    typedef A1 result_type;

    inline result_type
    operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG(is_simd_logical(a0), "Some entries are not legal SIMD True or False in first parameter"); 
      return bitwise_or(a1, a0);
    }
  };
} } }

#endif
