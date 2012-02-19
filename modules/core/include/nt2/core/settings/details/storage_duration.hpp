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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/padding.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/padded_allocator.hpp>
#include <nt2/sdk/meta/make_aligned_allocator.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>

namespace nt2
{
  //============================================================================
   /*!
    * Default storage duration settings.
   **/
  //============================================================================
  struct dynamic_
  {
    // Take whatever allocator someone above me want me to use (see shared_)
    template<typename T, typename S, typename D = void> struct apply
    {
      // Get the base index
      typedef typename meta::option<S,tag::index_>::type index_t;

      // Make the allocator aligned if needed
      typedef typename
              meta::make_aligned_allocator<typename D::type>::type base_alloc_t;

      // Extract the proper Index (0 if T, 1 if T*)
      typedef typename  boost::mpl
                      ::eval_if < boost::is_pointer<T>
                                , boost::mpl::at_c< typename index_t::type, 1>
                                , boost::mpl::at_c< typename index_t::type, 0>
                                >::type base_t;

      // Here is the fancy new buffer
      typedef typename base_alloc_t::template rebind<T>::other  allocator_type;
      typedef memory::buffer<T,base_t::value,allocator_type>    type;
    };

    template<typename T, typename S> struct apply<T,S>
    {
      typedef typename meta::option<S,tag::allocator_>::type  allocator_type;
      typedef typename apply<T,S,allocator_type>::type        type;
    };
  };

  //============================================================================
  // When using automatic memory, we rely on array_buffer to stores our data
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
      // Cut-off the size at proper level for index vs data generation
      // Index is when we generate a buffer from a pointer type T
      //========================================================================
      typedef typename size_::values_type base_size;
      typedef typename  boost::mpl
                      ::if_ < boost::is_pointer<T>
                            , typename boost::mpl::pop_front<base_size>::type
                            , base_size
                            >::type               sizes;

      // Compute total size
      typedef typename  boost::mpl::fold< sizes
                                        , boost::mpl::int_<1>
                                        , boost::mpl::times < boost::mpl::_1
                                                            , boost::mpl::_2
                                                            >
                                        >::type           dims_t;
      // Get the base index
      typedef typename meta::option<S,tag::index_>::type  index_t;

      // Extract the proper Index (0 if T, 1 if T*)
      typedef typename  boost::mpl
                      ::eval_if < boost::is_pointer<T>
                                , boost::mpl::at_c< typename index_t::type, 1>
                                , boost::mpl::at_c< typename index_t::type, 0>
                                >::type base_t;

      // Make me an array_buffer sandwich
      typedef memory::array_buffer<T,dims_t::value,base_t::value>    type;
    };
  };
}

#endif
