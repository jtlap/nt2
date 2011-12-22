//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_PERFORM_ALIGNED_ALLOCATION_HPP_INCLUDED
#define NT2_SDK_META_PERFORM_ALIGNED_ALLOCATION_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace boost { namespace simd {  namespace memory
{
  template<class T>                   struct allocator;
  template<class T, class Allocator>  struct allocator_adaptor;
} } }

namespace nt2 {  namespace memory
{
  template<typename A> struct padded_allocator;
  template<typename T> struct fixed_allocator;
} }

namespace nt2 {  namespace meta
{
  template<class Allocator>
  struct perform_aligned_allocation : boost::mpl::false_
  {};

  template<typename A>
  struct  perform_aligned_allocation< memory::padded_allocator<A> >
        : perform_aligned_allocation<A>
  {};

  template<typename T>
  struct  perform_aligned_allocation< memory::fixed_allocator<T> >
        : boost::mpl::true_
  {};

  template<class T>
  struct  perform_aligned_allocation< boost::simd::memory::allocator<T> >
        : boost::mpl::true_
  {};

  template<class T, class A>
  struct  perform_aligned_allocation<boost::simd::memory::allocator_adaptor<T,A> >
        : boost::mpl::true_
  {};
} }

#endif
