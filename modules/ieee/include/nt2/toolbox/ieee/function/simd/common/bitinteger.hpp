//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_positive.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::bitinteger_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_integer<A0, signed>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type type;
      type a00 = simd::native_cast<type>(a0);
      return simd::native_cast<type>(sel( is_positive(a0)
              , a00
              , Signmask<type>()-a00
                                ));
    }
  };
} }


#endif
