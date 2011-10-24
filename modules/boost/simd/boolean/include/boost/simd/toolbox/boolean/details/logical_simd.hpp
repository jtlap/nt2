//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_DETAILS_LOGICAL_SIMD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_DETAILS_LOGICAL_SIMD_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>

//==============================================================================
// Do something only if in SIMD mode
//==============================================================================
#if defined(BOOST_SIMD_DETECTED)

#if defined(BOOST_SIMD_LRB_FAMILY)
#include <boost/simd/sdk/simd/native.hpp>

//==============================================================================
// Larabee require full native<logical<T>> reimplementation
//==============================================================================
namespace boost { namespace simd
{
  template<class Scalar,class Extension> 
  union native<logical<Scalar>, tag::lrb_>
  {
    typedef tag::lrb_                                       extension_type;
    typedef __mmask                                         native_type;
    typedef logical<Scalar>                                 value_type;
    typedef logical<Scalar>                                 reference;
    typedef logical<Scalar>                                 const_reference;
    typedef std::size_t                                     size_type;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    enum { static_size = sizeof(__mmask) };

    BOOST_DISPATCH_FORCE_INLINE native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    BOOST_DISPATCH_FORCE_INLINE native& operator=(native_type const& data)
    {
      data_ = data;
      return *this;
    }

    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return static_size; }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }

    value_type operator[](std::size_t i) const { return data_ & (1 << i); }
    
    native_type data_;
  };
} }

#else

//==============================================================================
// Other extension just map logical<T> to SIMD vector of T
//==============================================================================
namespace boost { namespace simd { namespace details
{
  template<class T,class Extension>
  struct as_simd_impl< logical<T>, Extension > : meta::as_simd<T,Extension>
  {};
} } }

#endif

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X, class Origin>
  struct hierarchy_of< simd::native< simd::logical<T>, X>, Origin>
  {
    typedef simd::ext::simd_< simd::ext::logical_<Origin>, X> type;
  };
} }  }
    
#endif
#endif
