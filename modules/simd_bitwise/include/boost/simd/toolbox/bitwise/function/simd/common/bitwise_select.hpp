//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED

#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_select_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < cardinal_of<A0>
                                                        , cardinal_of<A1>
                                                        >
                                  )
                                , ( boost::simd::tag::bitwise_select_
                                    ( simd_<arithmetic_<A0>,X>
                                    , simd_<arithmetic_<A1>,X>
                                    , simd_<arithmetic_<A1>,X>
                                    )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                     )
  {
    typedef A1 result_type;

    inline result_type
    operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      return bitwise_xor(a2, b_and(bitwise_xor(a2, a1),a0));
    }
  };
} } }

#endif
