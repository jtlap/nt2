//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_SPAWNER_TRANSFORM_HPP_INCLUDED
#define NT2_SDK_HPX_SPAWNER_TRANSFORM_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <hpx/include/async.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/lcos/future_wait.hpp>

#include <nt2/sdk/shared_memory/spawner.hpp>

namespace nt2
{
  namespace tag
    {
      struct transform_;
      template<class T> struct hpx_;
    }

  template<class Site>
  struct spawner< tag::transform_, tag::hpx_<Site> >
  {

    spawner() {}

    template<typename Worker>
    void operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {
      std::size_t nblocks  = size/grain;
      std::size_t ibound   = nblocks * grain;
      std::size_t leftover = size % grain;

      std::vector< hpx::lcos::future<void> > barrier;
      barrier.reserve(nblocks+1);

      printf("spawner hpx\n");
      for(std::size_t n=0;n<nblocks;++n)
      {
         // Call operation
         barrier.push_back ( hpx::async(w, begin+n*grain, grain) );
      }

      if(leftover) barrier.push_back ( hpx::async(w, begin+ibound,leftover) );

      hpx::lcos::wait(barrier);
   }
 };
}

#endif
#endif
