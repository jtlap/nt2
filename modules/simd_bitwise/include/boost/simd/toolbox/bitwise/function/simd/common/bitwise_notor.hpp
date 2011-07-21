//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_BITWISE_NOTOR_HPP_INCLUDED

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_IF ( tag::bitwise_notor_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < cardinal_of<A0>
                                                        , cardinal_of<A1>
                                                        >
                                  )
                                , ( tag::bitwise_notor_
                                    ( simd_<arithmetic_<A0>,X>
                                    , simd_<arithmetic_<A1>,X>
                                    )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<arithmetic_<A1>,X>))
                     )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2) { return b_or(complement(a0),a1); }
  };
} } }

#endif
