//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_HI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_HI_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shri.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::hi_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_integer<A0, unsigned>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      typedef typename meta::scalar_of<result_type>::type int_type;

      BOOST_STATIC_CONSTANT(int_type, shift = sizeof(int_type)*4);
      BOOST_STATIC_CONSTANT(int_type, pattern = int_type(int_type(-1)<<shift));

      result_type that(shri((integral_constant<result_type,pattern>()&a0),shift));
      return that;
    }
  };
} }


#endif
