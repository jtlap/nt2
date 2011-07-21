//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SHRAI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_SHRAI_HPP_INCLUDED

#include <boost/simd/include/functions/shri.hpp>

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shrai_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<unsigned_<A0>,X>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(2) { return shri(a0, a1); }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::shrai_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<signed_<A0>,X>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      return map(functor<tag::shift_right_>(), a0, splat<A0>(a1));
    }
  };
} } }

#endif
