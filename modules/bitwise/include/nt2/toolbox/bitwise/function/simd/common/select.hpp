//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SELECT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SELECT_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( tag::select_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < cardinal_of<A0>
                                                        , cardinal_of<A1>
                                                        >
                                  )
                                , (tag::select_ ( simd_<arithmetic_<A0>,X>
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
      return b_or(b_and(a1,a0),b_andnot(a2,a0));
    }
  };
} }

#endif
