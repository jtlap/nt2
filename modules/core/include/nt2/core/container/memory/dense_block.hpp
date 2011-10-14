//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DENSE_BLOCK_HPP
#define NT2_CORE_CONTAINER_MEMORY_DENSE_BLOCK_HPP

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::dense_block class
  **/
//==============================================================================
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/core/container/memory/iliffe_buffer.hpp>
#include <cstdio>

namespace nt2 { namespace memory
{
  template<class Type, class Layout>
  struct dense_block
  {
    //==========================================================================
    // Retrieve size & number of dimensions from Layout
    //==========================================================================
    typedef typename meta::option<Layout, tag::of_size_>::type extent_type;
    static const std::size_t  dimensions  = extent_type::static_size;
    static const bool         is_static   = extent_type::static_status;

    //==========================================================================
    // Simply builds a iliffe_buffer from gathered informations
    //==========================================================================

    typedef iliffe_buffer < dimensions
                          , Type
                          , lead_padding
                          , allocator<Type>
                          >                       buffer_type;

    dense_block()
    {
      init( boost::mpl::bool_<is_static>() );
    }

    dense_block( extent_type const& sz )
    {
      boost::array<std::ptrdiff_t,4> bases= {{1,1,1,1}};
      initialize( data_,sz.data(), bases, lead_padding() );
    }

    ~dense_block() {}


    //private:

    void init( boost::mpl::true_ const& )
    {
      puts("herp");
      boost::array<std::ptrdiff_t,4> bases= {{1,1,1,1}};
      extent_type e;
      initialize( data_,e.data(), bases, lead_padding() );
    }

    void init( boost::mpl::false_ const& ) { puts("mout"); }

    buffer_type data_;
  };
} }

#endif
