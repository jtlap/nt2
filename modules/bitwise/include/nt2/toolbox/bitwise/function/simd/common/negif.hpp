//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_NEGIF_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_NEGIF_HPP_INCLUDED

#include <nt2/sdk/meta/size.hpp>
#include <nt2/include/functions/is_true.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/constants/properties.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( tag::negif_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , (tag::negif_( simd_<arithmetic_<A0>,X>
                                              , simd_<signed_<A1>,X>
                                              )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<signed_<A1>,X>))
                       )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2) { return  sel(is_true(a0),-a1,a1); }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF ( tag::negif_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , (tag::negif_( simd_<arithmetic_<A0>,X>
                                              , simd_<real_<A1>,X>
                                              )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<real_<A1>,X>))
                       )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2) { return b_xor(a1,b_and(is_true(a0),Signmask<A0>())); }
  };
} }

#endif
