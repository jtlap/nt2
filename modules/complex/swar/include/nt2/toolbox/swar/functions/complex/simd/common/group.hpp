//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_GROUP_HPP_INCLUDED

#include <nt2/toolbox/swar/functions/group.hpp>
#include <nt2/include/functions/load.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is downgradable
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::downgrade<A0>::type> >),
                          ((simd_<complex_<arithmetic_<A0> >,X>))
                          ((simd_<complex_<arithmetic_<A0> >,X>))
                        )
  {
    typedef typename boost::dispatch::meta::downgrade<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(group(real(a0), group(imag(a0)))); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::downgrade<A0>::type> >),
                          ((simd_<imaginary_<arithmetic_<A0> >,X>))
                          ((simd_<imaginary_<arithmetic_<A0> >,X>))
                        )
  {
    typedef typename boost::dispatch::meta::downgrade<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(group(imag(a0), imag(a1))); 
    }
  };  
} }
#endif
