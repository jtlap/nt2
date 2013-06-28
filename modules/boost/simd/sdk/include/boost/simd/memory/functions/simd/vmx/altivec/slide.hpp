//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_SLIDE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - slide between scalar values
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::altivec_
                                    , (A0)(N)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::altivec_
                                              >
                                      ))
                                      ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::altivec_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, N const&) const
    {
      return eval( a0, a1, boost::mpl::bool_<(N::value==A0::static_size)>() );
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const& a0, A0 const& a1, boost::mpl::false_ const&) const
    {
      typedef typename meta::scalar_of<result_type>::type scalar_type;
      return vec_sld( a0(), a1() , sizeof(scalar_type) * N::value );
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const&, A0 const& a1, boost::mpl::true_ const&) const
    {
      return a1;
    }
  };
} } }

#endif
#endif
