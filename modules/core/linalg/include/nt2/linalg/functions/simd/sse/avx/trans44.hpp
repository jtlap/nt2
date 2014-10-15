//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SIMD_SSE_SSE2_TRANS44_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SIMD_SSE_SSE2_TRANS44_HPP_INCLUDED

#include <nt2/linalg/functions/trans44.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/trans44.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trans44_, boost::simd::tag::avx_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef boost::simd::native<value_type,boost::simd::tag::sse_ >  n_t;
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 & a0) const
    {
      BOOST_ASSERT_MSG(nt2::width(a0) == 4 && nt2::height(a0) == 4, "input is not a 4x4 matrix");
      tr(a0, value_type());
    }
  private:
    BOOST_FORCEINLINE void tr(A0& a0, float) const
    {
      n_t c0 = load<n_t>(a0.raw(), 0);
      n_t c1 = load<n_t>(a0.raw(), 8);
      n_t t0 = nt2::shuffle<0,4,1,5,8,12,9,13>(c0, c1);
      n_t t2 = nt2::shuffle<2,6,3,7,10,14,11,15>(c0, c1);
      store(c0, a0.raw(), 0);
      store(c1, a0.raw(), 8);
    }

    BOOST_FORCEINLINE void tr(A0& a0, double) const
    {
      n_t c0 = load<n_t>(a0.raw(), 0);
      n_t c1 = load<n_t>(a0.raw(), 4);
      n_t c2 = load<n_t>(a0.raw(), 8);
      n_t c3 = load<n_t>(a0.raw(), 12);

      n_t t0 = nt2::shuffle<0,4,1,5>(c0, c1);
      n_t t1 = nt2::shuffle<0,4,1,5>(c2, c3);
      n_t t2 = nt2::shuffle<2,6,3,7>(c0, c1);
      n_t t3 = nt2::shuffle<2,6,3,7>(c2, c3);

      c0 = nt2::shuffle<0,1,4,5>(t0, t1);
      c1 = nt2::shuffle<2,3,6,7>(t0, t1);
      c2 = nt2::shuffle<0,1,4,5>(t2, t3);
      c3 = nt2::shuffle<2,3,6,7>(t2, t3);
      store(c0, a0.raw(), 0);
      store(c1, a0.raw(), 4);
      store(c2, a0.raw(), 8);
      store(c3, a0.raw(), 12);

    }

  };

} }

#endif
