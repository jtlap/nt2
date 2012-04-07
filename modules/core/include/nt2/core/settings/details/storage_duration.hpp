//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_STORAGE_DURATION_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/meta/make_aligned_allocator.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>

namespace nt2
{
  //============================================================================
   /*!
    * Default storage duration settings.
   **/
  //============================================================================
  struct dynamic_
  {
    //==========================================================================
    // If specified, use Alloc as an allocator
    //==========================================================================
    template<typename T, typename S, typename Alloc = void> struct apply
    {
      //========================================================================
      // Make the allocator aligned if needed
      //========================================================================
      typedef typename
              meta::make_aligned_allocator<typename Alloc::type>::type alloc_t;

      //========================================================================
      // Make me an buffer sandwich with a proper allocator
      //========================================================================
      typedef typename alloc_t::template rebind<T>::other allocator_type;
      typedef memory::buffer<T,allocator_type>            type;
    };

    //==========================================================================
    // By default, ask for the settings allocator type
    //==========================================================================
    template<typename T, typename S> struct apply<T,S>
    {
      typedef typename meta::option<S,tag::allocator_>::type  allocator_type;
      typedef typename apply<T,S,allocator_type>::type        type;
    };
  };

  //============================================================================
  // When using automatic memory, we rely on array_buffer to store our data
  //============================================================================
  struct automatic_
  {
    template <typename T, typename S, typename D = void>
    struct apply
    {
      typedef typename meta::option<S,tag::of_size_>::type  size_;

      //========================================================================
      // If you trigger this assertion, you specified an automatic storage for
      // a container with a dynamic size. Check your container settings.
      //========================================================================
      BOOST_MPL_ASSERT_MSG
      ( (size_::static_status)
      , SETTINGS_MISMATCH_AUTOMATIC_STORAGE_REQUESTED_WITH_DYNAMIC_SIZES
      , (size_)
      );

      //========================================================================
      // Make me an array_buffer sandwich of proper size
      //========================================================================
      typedef typename boost::mpl::fold < typename size_::values_type
                                        , boost::mpl::size_t<1>
                                        , boost::mpl::times < boost::mpl::_1
                                                            , boost::mpl::_2
                                                            >
                                        >::type           dims_t;
      typedef memory::array_buffer<T,dims_t>              type;
    };
  };
}

#endif
