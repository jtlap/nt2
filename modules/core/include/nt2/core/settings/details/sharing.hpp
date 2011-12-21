//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_SHARING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_SHARING_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/alignment.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <nt2/core/container/memory/fixed_allocator.hpp>

namespace nt2 
{
  //============================================================================
  // When memory is shared by the container, the index buffer is dependent on
  // the storage_duration passed as a setting while the data buffer is forced
  // to be a dynamic_ buffer with a (potentially adapted) fixed_allocator
  //============================================================================
  struct shared_
  {
    struct index
    {
      template<class T, class S> struct apply
      {
        typedef typename meta::option<S,tag::storage_duration_>::type sd_t;
        typedef typename sd_t::template apply<T*,S>::type             type;
      };
    };

    struct data
    {
      template<class T, class S> struct apply
      {
        typedef allocator_< memory::fixed_allocator<T> >              alloc_t;
        typedef typename dynamic_::template apply<T,S,alloc_t>::type  type;
      };
    };
  }; 

  //============================================================================
  // When memory is owned by the container, both index and data buffers are
  // dependent on the storage_duration passed as a setting.
  //============================================================================
  struct owned_
  {
    struct index
    {
      template<class T, class S> struct apply
      {
        typedef typename meta::option<S,tag::storage_duration_>::type sd_t;
        typedef typename sd_t::template apply<T*,S>::type             type;
      };
    };

    struct data
    {
      template<class T, class S> struct apply
      {
        typedef typename meta::option<S,tag::storage_duration_>::type sd_t;
        typedef typename sd_t::template apply<T,S>::type              type;
      };
    };
  };
}

#endif
