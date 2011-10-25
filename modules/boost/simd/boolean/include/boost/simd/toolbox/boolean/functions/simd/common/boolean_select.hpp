//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_BOOLEAN_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_BOOLEAN_SELECT_HPP_INCLUDED
#include <boost/simd/toolbox/bitwise/functions/bitwise_select.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/simd/toolbox/boolean/logical.hpp>
b#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::boolean_select_, tag::cpu_, (A0)(A1)(X), 
                                 (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                        , boost::simd::meta::cardinal_of<A1>
                                                        >
                                  )
                                    //                                     (boost::is_same <A0,meta::as_logical<A1>::type> )
                                , ( boost::simd::tag::boolean_select_
                                    ( simd_<logical_<A0>,X>
                                    , simd_<arithmetic_<A1>,X>
                                    , simd_<arithmetic_<A1>,X>
                                    )
                                  )
                                , ((simd_<logical_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                     )
  {
    typedef A1 result_type;
    inline result_type
    operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      return bitwise_select(native_cast<A1>(a0), a1, a2);
    }
  };
} } }

#endif
