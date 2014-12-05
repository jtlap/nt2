//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_SHARED_MEMORY_HPP_INCLUDED
#define NT2_SDK_HPX_SHARED_MEMORY_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>
#include <nt2/sdk/shared_memory/shared_memory.hpp>

namespace nt2 { namespace tag
{
  template<typename Site> struct hpx_ : shared_memory_< hpx_<Site>, Site >
  {
    typedef shared_memory_< hpx_<Site>, Site > parent;
  };
} }

#if defined(NT2_USE_HPX)

BOOST_DISPATCH_COMBINE_SITE( nt2::tag::hpx_<tag::cpu_> )

#include <nt2/sdk/hpx/spawner.hpp>
#include <nt2/sdk/hpx/future.hpp>

#endif
#endif
