//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_MAKE_ALIGNED_ALLOCATOR_HPP_INCLUDED
#define NT2_SDK_META_MAKE_ALIGNED_ALLOCATOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/simd/sdk/memory/allocator_adaptor.hpp>
#include <nt2/sdk/meta/perform_aligned_allocation.hpp>

namespace nt2 {  namespace details
{
  template< class Allocator
          , bool Enable = meta::perform_aligned_allocation<Allocator>::value
          >
  struct make_aligned_allocator
  {
    typedef Allocator type;
  };

  template< class Allocator>
  struct make_aligned_allocator<Allocator,false>
  {
    typedef typename Allocator::value_type value_type;
    typedef boost::simd::memory::allocator_adaptor<value_type,Allocator> type;
  };
} }

namespace nt2 {  namespace meta
{
  template<class Allocator>
  struct make_aligned_allocator : details::make_aligned_allocator<Allocator>
  {};
} }

#endif
