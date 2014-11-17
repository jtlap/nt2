//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_INCLUDE_FUNCTOR_HPP_INCLUDED
#define BOOST_SIMD_INCLUDE_FUNCTOR_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/sdk/functor/preprocessor/function.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch
{
  template<class Tag, class Site>
  struct generic_dispatcher
  {
    template<class... Args>
    BOOST_FORCEINLINE
    BOOST_AUTO_DECLTYPE operator()(Args&&... args) const
    BOOST_AUTO_DECLTYPE_BODY(
      dispatching(meta::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args>()...)(static_cast<Args&&>(args)...)
    )
  };
} }

namespace boost { namespace simd { namespace ext
{
  struct adl_helper {};

  template<class Tag, class Site, class... Args>
  BOOST_FORCEINLINE boost::dispatch::generic_dispatcher<Tag, Site>
  dispatching(adl_helper, unknown_<Tag>, unknown_<Site>, unknown_<Args>...)
  {
    return boost::dispatch::generic_dispatcher<Tag, Site>();
  }
} } }

namespace boost { namespace simd
{
  template<class Tag, class Site>
  struct generic_dispatcher
  {
    template<class... Args>
    BOOST_FORCEINLINE
    BOOST_AUTO_DECLTYPE operator()(Args&&... args) const
    BOOST_AUTO_DECLTYPE_BODY(
      dispatching(ext::adl_helper(), Tag(), boost::dispatch::default_site_t<Site>(), boost::dispatch::meta::hierarchy_of_t<Args>()...)(static_cast<Args&&>(args)...)
    )
  };
} }

#endif
