//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_STREAM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_STREAM_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/stream.hpp>
#include <boost/simd/include/functions/simd/store.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  // If no stream intrinsic, do a classical store.
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::stream_ , tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , ((simd_< fundamental_<A0>, X >))
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename dispatch::meta::
            call<tag::store_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(a1,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::is_aligned(a1+a2,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to store with a pointer that"
        " is not aligned on the simd vector size.");
      return store(a0, a1, a2);
    }
  };
} } }

#endif
