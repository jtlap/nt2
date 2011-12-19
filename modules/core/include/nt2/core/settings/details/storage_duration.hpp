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

#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/padding.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/settings/alignment.hpp>
#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/container/meta/padded_size.hpp>
#include <nt2/core/container/memory/array_buffer.hpp>
#include <nt2/core/container/meta/make_aligned_allocator.hpp>
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
      // Get the alignment hint
      typedef typename meta::option<S,tag::alignment_>::type  align_t;
      
      // Make it aligned if needed
      typedef typename boost::mpl::
              eval_if < align_t
                      , D
                      , meta::make_aligned_allocator<typename D::type>
                      >::type                             allocator_type;

      typedef memory::buffer<T,allocator_type>            type;
    };  

    template<typename T, typename S> struct apply<T,S>
    {
      typedef typename meta::option<S,tag::allocator_>::type  alloc_t;
      typedef typename apply<T,S,alloc_t>::type  type;
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
      // If you trigger this assertion, you specified a lead padding value
      // which is either runtime-specified or not aligned on a power of 2.
      // Check your container settings.
      //========================================================================
      typedef typename meta::option<S,tag::lead_padding_  >::type   lead_;

      BOOST_MPL_ASSERT_MSG
      ( (lead_::value != -1) && (boost::simd::meta::is_power_of_2<lead_>::value)
      , SETTINGS_MISMATCH_AUTOMATIC_STORAGE_WITH_INVALID_LEAD_PADDING_OPTIONS
      , (lead_)
      );

      //========================================================================
      // If you trigger this assertion, you specified a global padding value
      // which is either runtime-specified or not aligned on a power of 2.
      // Check your container settings.
      //========================================================================
      typedef typename meta::option<S,tag::global_padding_>::type   global_;

      BOOST_MPL_ASSERT_MSG
      ( (global_::value != -1) && (boost::simd::meta::is_power_of_2<global_>::value)
      , SETTINGS_MISMATCH_AUTOMATIC_STORAGE_WITH_INVALID_GLOBAL_PADDING_OPTIONS
      , (global_)
      );

      //========================================================================
      // Make me an array_buffer sandwich
      //========================================================================
      typedef typename meta::padded_size<size_,global_,lead_>::type dims_;
      typedef memory::array_buffer<T,dims_::value>                  type;
    };  
  };
}

#endif
