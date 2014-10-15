//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SIMD_TRANS22_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SIMD_TRANS22_HPP_INCLUDED

#include <nt2/linalg/functions/trans22.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/trans22.hpp>
#include <nt2/include/functions/shuffle.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trans22_, boost::simd::tag::sse2_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef boost::simd::native<value_type,boost::simd::tag::sse_ >  n_t;
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 & a0) const
    {
      BOOST_ASSERT_MSG(nt2::width(a0) == 2 && nt2::height(a0) == 2, "input is not a 2x2 matrix");
      tr(a0, value_type());
    }
  private:
    BOOST_FORCEINLINE void tr(A0& a0, float) const
    {
      n_t a = load<n_t>(a0.raw(), 0);
      a = nt2::shuffle<0,2,1,3>(a);
      store(a, a0.raw());
    }
    BOOST_FORCEINLINE void tr(A0& a0, double) const
    {
      n_t a = load<n_t>(a0.raw(), 1);
      a = nt2::shuffle<1,0>(a);
      store(a, a0.raw(), 1);
    }
  };

} }

#endif
