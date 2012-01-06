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
#include <nt2/sdk/memory/block_facade.hpp>
#include <nt2/core/utility/of_size/pad.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/adapted/container.hpp>
#include <nt2/core/settings/normalize_settings.hpp>

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
    typedef typename allocator_type::pointer   pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    //==========================================================================
    // container is handling the size/base storage for the proto terminal
    //==========================================================================
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;
    typedef typename meta::option<settings_type, tag::index_>::type   index_type;

    //==========================================================================
    // Potential container lead padding value
    //==========================================================================
    typedef typename meta::option<settings_type,tag::lead_padding_>::type lead_t;

    //==========================================================================
    // container knows if its size is statically defined or not
    //==========================================================================
    typedef boost::mpl::bool_<extent_type::static_status>  is_static_sized;

    //==========================================================================
    // If size is static, perform allocation from default constructor
    //==========================================================================
    template<class Size>
    inline void init( block_t& block, Size const& sz, boost::mpl::true_ const& )
    {
      block.resize( pad(sz,lead_t::value) );
    }

    template<class Size>
    inline void init( block_t&, Size const&, boost::mpl::false_ const& ) {}

    //==========================================================================
    // Resize inner block if resizing is allowed
    //==========================================================================
    template<class Size> inline
    void resize ( block_t& block, Size const& new_sz, extent_type& old_sz
                , boost::mpl::false_ const&
                )
    {
      if( new_sz != old_sz )
      {
        old_sz = extent_type(new_sz);
        block.resize( pad(old_sz,lead_t::value) );
      }
    }

    //==========================================================================
    // Force a static assert if a statically sized container is resized
    //==========================================================================
    template<class Size> inline
    void resize( block_t&, Size const&, extent_type&, boost::mpl::true_ const&)
    {
      BOOST_MPL_ASSERT_MSG
      ( (sizeof(Size) == 0)
      , STATICALLY_SIZED_CONTAINER_CANT_BE_RESIZED_DYNAMICALLY
      , (Size)
      );
    }
  };
} }

namespace nt2 { namespace memory
{
  template<class Tag, class ID, class T, class S> struct container;

  //============================================================================
  // Generic swap for container of any kind
  //============================================================================
  template<class Tag, class ID, class T, class S>
  void swap(container<Tag,ID,T,S>& a,container<Tag,ID,T,S>& b)
  {
    a.swap(b);
  }
} }

#endif
