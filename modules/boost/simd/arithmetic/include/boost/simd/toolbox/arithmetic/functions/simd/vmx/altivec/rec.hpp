//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_REC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_REC_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/arithmetic/functions/rec.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/functions/copysign.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_
                                   , boost::simd::tag::altivec_
                                   , (A0)
                                   , ((simd_<arithmetic_<A0>, boost::simd::tag::altivec_>))
                                   )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type erb   = vec_re(a0());
      result_type vmadd = vec_madd( vec_nmsub(erb(), a0(), One<result_type>()())
                                             , erb()
                                             , erb()
                                             );
      result_type rec_b  = if_else( is_eqz(a0)
                                  , copysign(Inf<result_type>(),a0)
                                  , vmadd
                                  );
      return if_else(is_eqz(erb), copysign(erb,a0), rec_b);
    }
  };
} } }
#endif
#endif
