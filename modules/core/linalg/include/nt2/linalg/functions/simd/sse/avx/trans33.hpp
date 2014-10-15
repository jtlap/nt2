//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SIMD_SSE_AVX_TRANS33_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SIMD_SSE_AVX_TRANS33_HPP_INCLUDED

#include <nt2/linalg/functions/trans33.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/trans33.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trans33_, boost::simd::tag::avx_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef boost::simd::native<value_type,boost::simd::tag::sse_ >  n_t;
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 & a0) const
    {
      BOOST_ASSERT_MSG(nt2::width(a0) == 3 && nt2::height(a0) == 3, "input is not a 3x3 matrix");
      tr(a0, value_type());
    }
  private:
    BOOST_FORCEINLINE void tr(A0& a0, float) const
    {
      n_t a = load<n_t>(a0.raw(), 0);
      n_t b  = nt2::shuffle<0,3,6,1,4,7,2,5>(a);
      store(b, a0.raw());
    }
    BOOST_FORCEINLINE void tr(A0& a0, double) const
    {
      n_t a = load<n_t>(a0.raw(), 0);
//      a = nt2::shuffle<0, 3, 2, 1 >(a);
      n_t b = load<n_t>(a0.raw(), 4);
      a = nt2::shuffle<0,3,6,1>(a, b);
//      b = nt2::shuffle<0, 3,  2, 1 >(a);
      b = nt2::shuffle<4,7,2,5>(a, b);
      store(a, a0.raw(), 0);
      store(b, a0.raw(), 4);
    }
  };

} }

#endif
