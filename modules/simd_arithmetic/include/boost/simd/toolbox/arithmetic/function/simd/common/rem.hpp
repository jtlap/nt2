//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REM_HPP_INCLUDED

#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/selsub.hpp>
#include <boost/simd/include/functions/idivfix.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rem_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return selsub(is_nez(a1), a0,idivfix(a0,a1)*a1);
    }
  };

  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rem_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return b_or(is_invalid(a1), selsub(is_nez(a1), a0, tofloat(idivfix(a0,a1))*a1));
    }
  };
} } }

#endif
