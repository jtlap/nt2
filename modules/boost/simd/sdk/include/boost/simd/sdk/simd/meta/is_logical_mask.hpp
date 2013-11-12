//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/bool.hpp>

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct is_logical_mask
       : mpl::false_
  {
  };

  template<class T, class X>
  struct is_logical_mask< native< logical<T>, X > >
       : mpl::equal_to< mpl::sizeof_< native< logical<T>, X > >
                      , mpl::sizeof_< native<T, X> >
                      >
  {
  };
} } }

#endif
