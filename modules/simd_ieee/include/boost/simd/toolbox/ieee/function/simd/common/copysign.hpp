//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#include <boost/simd/sdk/details/ignore_unused.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/bitofsign.hpp>
#include <boost/simd/include/functions/signnz.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::copysign_, tag::cpu_,
                           (A0)(X),
                           ((simd_<arithmetic_<A0>,X>))
                           ((simd_<arithmetic_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
        return  signnz(a1)*abs(a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::copysign_, tag::cpu_,
                           (A0)(X),
                           ((simd_<unsigned_<A0>,X>))
                           ((simd_<unsigned_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      ignore_unused(a1);
      return  a0;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::copysign_, tag::cpu_,
                           (A0)(X),
                           ((simd_<real_<A0>,X>))
                           ((simd_<real_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return b_or(abs(a0), bitofsign(a1));
    }
  };
} } }
#endif
