//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_FORWARD_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_FORWARD_HPP_INCLUDED

#include <boost/dispatch/functor/meta/hierarchy.hpp>
#include <boost/dispatch/meta/counter.hpp>
#include <boost/dispatch/meta/combine.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>

BOOST_DISPATCH_COUNTER_INIT(default_site_stack)

namespace boost { namespace dispatch
{
  using meta::default_site_stack;
  template<class Tag, int N = BOOST_DISPATCH_COUNTER_VALUE_TPL(default_site_stack, Tag)>
  struct default_site_impl
  {
    typedef tag::cpu_ type;
  };

  //============================================================================
  /*
   * default_site defines the architecture dependent default evaluation context
   * for functors.
   */
  //============================================================================
  template<class Tag>
  struct default_site
   : default_site_impl<Tag>
  {
  };

  template< class Tag
          , class EvalContext = typename default_site<Tag>::type
          >
  struct functor;
} }

namespace boost { namespace dispatch { namespace meta
{
  template< class Signature , class Site, class Dummy = void> struct implement;
} } }

#define BOOST_DISPATCH_COMBINE_SITE(new_site)                                                      \
namespace boost { namespace dispatch                                                               \
{                                                                                                  \
  template<class Tag>                                                                              \
  struct default_site_impl<Tag, BOOST_DISPATCH_COUNTER_VALUE(default_site_stack) + 1>              \
   : meta::combine< typename default_site_impl<Tag                                                 \
                                              , BOOST_DISPATCH_COUNTER_VALUE(default_site_stack)   \
                                              >::type                                              \
                  , BOOST_DISPATCH_PP_STRIP(new_site)                                              \
                  >                                                                                \
  {                                                                                                \
  };                                                                                               \
} }                                                                                                \
BOOST_DISPATCH_COUNTER_INCREMENT(default_site_stack)                                               \
/**/

#define BOOST_DISPATCH_DEFAULT_SITE_FOR(Tag)                                                       \
namespace boost { namespace dispatch                                                               \
{                                                                                                  \
  template<>                                                                                       \
  struct default_site<BOOST_DISPATCH_PP_STRIP(Tag)>                                                \
    : default_site_impl<BOOST_DISPATCH_PP_STRIP(Tag), 0>                                           \
  {                                                                                                \
  };                                                                                               \
} }                                                                                                \
/**/

#endif
