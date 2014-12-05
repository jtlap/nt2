//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_FUTURE_WHEN_ALL_HPP_INCLUDED
#define NT2_SDK_HPX_FUTURE_WHEN_ALL_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <nt2/sdk/shared_memory/future.hpp>
#include <nt2/sdk/hpx/future/details/when_all_result.hpp>
#include <hpx/lcos/when_all.hpp>

#include <utility>
#include <vector>

namespace nt2
{
  template<class Site>
  struct when_all_impl< tag::hpx_<Site> >
  {
    template< typename ... A >
    inline typename when_all_result < tag::hpx_<Site>, A ... >::type
    call(A && ... a)
    {
      return hpx::when_all(std::forward<A>(a)...);
    }

    template <typename Future>
    inline typename when_all_vec_result< tag::hpx_<Site>, Future>::type
    call( std::vector<Future> && lazy_values )
    {
      return hpx::when_all(
        std::forward< std::vector<Future> > ( lazy_values )
        );
    }
  };
}

#endif
#endif
