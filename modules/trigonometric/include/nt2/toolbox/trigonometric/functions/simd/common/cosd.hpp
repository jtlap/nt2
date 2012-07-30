//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_COSD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_COSD_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/cosd.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/strip.hpp>
 #include <nt2/toolbox/trigonometric/functions/simd/common/impl/trigo.hpp>
//  MIGRATION WARNING you have to provide the file for the previous include from
//  nt2/core/numeric/functions/details/simd/common/impl/trigo.hpp
//  of the old nt2
#include <nt2/include/functions/simd/tofloat.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosd_, boost::simd::tag::simd_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return impl::trig_base<result_type,degree_tag,  tag::simd_type>::cosa(tofloat(a0));
    }
  };
} }


#endif
