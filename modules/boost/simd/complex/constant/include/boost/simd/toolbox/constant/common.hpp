//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_COMMON_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_COMMON_HPP_INCLUDED

#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/complex/complex.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)
                                   , ((target_< generic_< complex_< arithmetic_<A0> > > >))
                                   )
  {
    typedef typename A0::type                               result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
           
      return result_type( dispatch::functor<Tag>()(dispatch::meta::as_<real_t>())
                        , Zero<real_t>()
                        );
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)
                                   , ((target_< generic_< imaginary_< arithmetic_<A0> > > >))
                                   )
  {
    typedef typename A0::type                               result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
      return result_type(dispatch::functor<Tag>()(dispatch::meta::as_<real_t>()));
    }
  };
  
} } }

#endif
