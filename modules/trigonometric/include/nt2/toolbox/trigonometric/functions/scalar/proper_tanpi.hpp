//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_PROPER_TANPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_PROPER_TANPI_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/proper_tanpi.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/trigo.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_nan.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    inline result_type operator()(A0 const&)const 
    {
      return Zero<result_type>();
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0; 
      A0 absa0 = nt2::abs(a0);
      if (absa0 > Half<A0>()) return Nan<A0>();
      bool test = (absa0 <= Quarter<A0>());
      absa0 = test ? absa0 : Half<A0>()-absa0; 
      A0 that = impl::trig_base<A0,pi_tag,tag::not_simd_type, clipped_pio4>::tana(absa0);
      that = nt2::negif(nt2::is_ltz(a0), that); 
      return test ? that : rec(that); 
    }
  };
} }


#endif
