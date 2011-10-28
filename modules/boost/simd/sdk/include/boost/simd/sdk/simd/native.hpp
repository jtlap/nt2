/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/details/native/meta.hpp>
#include <boost/simd/sdk/simd/details/native/fusion.hpp>
#include <boost/simd/sdk/simd/details/native/operators.hpp>
#include <boost/simd/sdk/memory/overload.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  /// Platform independant native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class Scalar,class Extension>
  struct BOOST_SIMD_MAY_ALIAS native
  {
    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> is a SIMD type encapsulation
    ////////////////////////////////////////////////////////////////////////////
    typedef Extension                                       extension_type;
    typedef typename meta::as_simd<Scalar, Extension>::type native_type;

    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> models RandomAccessRange and FusionRandomAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef BOOST_SIMD_MAY_ALIAS Scalar                     value_type;
    typedef value_type&                                     reference;
    typedef value_type const&                               const_reference;
    typedef std::size_t                                     size_type;
    typedef Scalar*                                         iterator;
    typedef Scalar const*                                   const_iterator;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum { static_size = meta::cardinal_of<native>::value };

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from same type (generates better code)
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from native vector type
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    native& operator=(native_type const& data)
    {
      data_ = data;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // Use operator() for explicit conversion.
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    operator native_type const& ()   const { return data_; }
    
    BOOST_DISPATCH_FORCE_INLINE
    native_type const& operator()()  const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    iterator       begin()       { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    iterator       end()         { return data() + static_size; };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator begin() const { return data(); };
    
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator end()   const { return data() + static_size; };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE std::size_t  size()  { return static_size; }
    static BOOST_DISPATCH_FORCE_INLINE bool         empty() { return false; }

    reference       operator[](std::size_t i)       { return data()[i]; }
    const_reference operator[](std::size_t i) const { return data()[i]; }
    
    native_type data_;
    
    BOOST_DISPATCH_FORCE_INLINE
    value_type* data() 
    { 
      return reinterpret_cast<value_type*>(&data_); 
    }

    BOOST_DISPATCH_FORCE_INLINE
    const value_type* data() const 
    { 
      return reinterpret_cast<value_type const*>(&data_); 
    }
  };
} }

#endif
