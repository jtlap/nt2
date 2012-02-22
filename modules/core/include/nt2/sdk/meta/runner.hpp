//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_RUNNER_HPP_INCLUDED
#define NT2_SDK_META_RUNNER_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

namespace nt2 { namespace meta
{
  template<class A0, class Scalar>
  struct runner
  {
    typedef void result_type;

    runner(A0 const& a0_) : a0(a0_) {}

    template<class Position, class Step>
    BOOST_FORCEINLINE
    typename boost::enable_if_c<Step::value == 1, result_type>::type
    operator()(Position const& pos, Step const&) const
    {
      nt2::run(a0, pos, meta::as_<Scalar>());
    }
    
    template<class Position, class Step>
    BOOST_FORCEINLINE
    typename boost::disable_if_c<Step::value == 1, result_type>::type
    operator()(Position const& pos, Step const&) const
    {
      nt2::run(a0, pos, meta::as_<typename boost::simd::meta::
                                  vector_of<Scalar, Step::value
                                 >::type>());
    }

    A0 const& a0;
  };
} }

#endif
