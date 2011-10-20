//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_RUNNER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_RUNNER_HPP_INCLUDED

#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/store.hpp>

namespace nt2 { namespace meta
{
  template<class A0, class Target> struct runner
  {
    typedef void result_type;

    runner(A0 a0_) : a0(a0_) {}

    template<class Position> BOOST_DISPATCH_FORCE_INLINE result_type 
    operator()(Position const& pos) const
    {
    #if 0
      nt2::store( boost::proto::child_c<0>(a0)
                , pos
                , nt2::run(boost::proto::child_c<1>(a0), pos, Target())
                );
    #else
      nt2::run(a0, pos, Target());
    #endif
    }

    A0 a0;
  };
} }

#endif
