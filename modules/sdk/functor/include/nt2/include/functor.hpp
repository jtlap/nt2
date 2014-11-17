//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INCLUDE_FUNCTOR_HPP_INCLUDED
#define NT2_INCLUDE_FUNCTOR_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>
#include <nt2/sdk/functor/site.hpp>
#include <nt2/sdk/simd/category.hpp>

namespace nt2 { namespace ext
{
  struct adl_helper {};

  template<class Tag, class Site, class... Args>
  BOOST_FORCEINLINE boost::dispatch::functor<Tag, Site>
  dispatching(adl_helper, unknown_<Tag>, unknown_<Site>, unknown_<Args>...)
  {
    return boost::dispatch::functor<Tag, Site>();
  }
} }

namespace nt2
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
}

#endif
