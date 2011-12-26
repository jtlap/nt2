//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_CONTAINER_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_CONTAINER_BASE_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/container_of.hpp>
#include <nt2/sdk/memory/block_facade.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/settings/normalize_settings.hpp>
#include <nt2/core/container/dsl/forward.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Defines the base shared elements of container class specifications
  //============================================================================
  template<class Tag, class T, class S> struct container_base
  {
    //==========================================================================
    // Builds the block from the normalizedd settings
    //==========================================================================
    typedef typename meta::normalize_settings<Tag,T,S>::type        settings_type;
    typedef typename meta::option<settings_type, tag::shape_>::type shape_t;
    typedef memory::block<shape_t,T,settings_type>                  block_t;

    //==========================================================================
    // Public type interface
    //==========================================================================
    typedef typename block_t::allocator_type   allocator_type;
    typedef typename block_t::value_type       value_type;
    typedef typename block_t::iterator         iterator;
    typedef typename block_t::const_iterator   const_iterator;
    typedef typename block_t::reference        reference;
    typedef typename block_t::const_reference  const_reference;
    typedef typename block_t::size_type        size_type;
    typedef typename block_t::difference_type  difference_type;

    //==========================================================================
    // container is handling the size/base storage for the proto terminal
    //==========================================================================
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;
    typedef typename meta::option<settings_type, tag::index_>::type   index_type;
  };
} }

namespace nt2 { namespace memory
{
  template<class Tag, class ID, class T, class S> struct container;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct is_container< memory::container<Tag, ID, T, S> > : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Register table_container as a proper Hierarchizable
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct value_of< nt2::memory::container<Tag, ID, T, S> >
  {
    typedef T type;
  };

  //============================================================================
  // table_container produce container expression from proper type and settings.
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct terminal_of< nt2::memory::container<Tag,ID,T,S> >
  {
    typedef nt2::memory::container<Tag,ID,T, S>
    /*
                                                        base_t;
    typedef typename base_t::settings_type              settings_t;
    typedef nt2::memory::container<Tag,ID,T,settings_t>*/
                                                        container_t;

    typedef nt2::container::
            expression< typename boost::proto::terminal< container_t >::type
                      , container_t
                      >                                                    type;
  };
} } }
#endif
