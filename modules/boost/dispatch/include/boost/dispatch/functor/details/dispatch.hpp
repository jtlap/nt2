//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>

namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};

  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Sig, class Site = void>
  struct dispatch_call;

  //==============================================================================
  // What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
  // it is mandated by the standard so ADL kicks in on resolving calls to
  // dispatching without having to order them BEFORE the actual dispatch_call
  // class definitions. Without it, the whole system brittles.
  //==============================================================================

  template< class Tag, class Site
          , class... A
          >
  BOOST_FORCEINLINE
  boost::dispatch::meta::
  implement<tag::unknown_, Site, Tag(A...)>
  dispatching ( adl_helper
              , meta::unknown_<Tag>, meta::unknown_<Site>
              , meta::unknown_<A>...
              )
  {
    boost::dispatch::meta::implement< tag::unknown_, Site
                                    , Tag(A...)
                                    > that;
    return that;
  }

  template< class Tag, class Site_
          , class... A
          >
  struct dispatch_call<Tag(A...), Site_>
  {
    typedef typename boost::mpl::
            eval_if< is_void<Site_>
                   , default_site<Tag>
                   , mpl::identity<Site_>
                   >::type Site;

    typedef decltype
    ( hierarchy_of_t<Tag>::dispatching ( hierarchy_of_t<Site>()
                                       , hierarchy_of_t<A>()...
                                       )
    ) type;
  };

} } }

#endif
