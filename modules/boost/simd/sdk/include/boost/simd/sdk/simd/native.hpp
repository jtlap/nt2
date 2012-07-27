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
#include <boost/simd/sdk/meta/zero_initialize.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/details/native/meta.hpp>
#include <boost/simd/sdk/simd/details/native/operators.hpp>
#include <boost/simd/sdk/memory/overload.hpp>
#include <boost/fusion/adapted/boost_array.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  /// Platform independant native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class Scalar,class Extension,class Enable>
  struct BOOST_SIMD_MAY_ALIAS native
  {
    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> is a SIMD type encapsulation
    ////////////////////////////////////////////////////////////////////////////
    typedef Extension                                       extension_type;
    typedef typename meta::as_simd<Scalar, Extension>::type    native_type;

    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> models RandomAccessRange and FusionRandomAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef Scalar                                              value_type;
    typedef typename meta::may_alias<Scalar>::type&              reference;
    typedef typename meta::may_alias<Scalar>::type const&  const_reference;
    typedef std::size_t                                          size_type;
    typedef typename meta::may_alias<Scalar>::type*               iterator;
    typedef typename meta::may_alias<Scalar>::type const*   const_iterator;
    typedef boost::fusion::boost_array_tag                      fusion_tag;

    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum v_size { static_size = sizeof(native_type)/sizeof(value_type)
                       ? sizeof(native_type)/sizeof(value_type) : 1};

    BOOST_FORCEINLINE native() {}
    BOOST_FORCEINLINE native(native_type data) : data_(data) {}
#ifdef BOOST_MSVC
    BOOST_FORCEINLINE native(native const& other) : data_(other.data_) {}
#endif

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from same type (generates better code than default-generated one)
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    native& operator=(native const& s)
    {
      data_ = s.data_;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from native vector type
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    native& operator=(native_type data)
    {
      data_ = data;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // Use operator() for explicit conversion.
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE operator native_type &           ()             { return data_; }
    BOOST_FORCEINLINE          native_type & operator()()             { return data_; }
    
    BOOST_FORCEINLINE operator native_type const&           ()  const { return data_; }
    BOOST_FORCEINLINE          native_type const& operator()()  const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(native)

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    iterator       begin()       { return data(); };
    
    BOOST_FORCEINLINE
    iterator       end()         { return data() + static_size; };
    
    BOOST_FORCEINLINE
    const_iterator begin() const { return data(); };
    
    BOOST_FORCEINLINE
    const_iterator end()   const { return data() + static_size; };

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_FORCEINLINE std::size_t  size()  { return static_size; }
    static BOOST_FORCEINLINE bool         empty() { return false; }

    reference       operator[](std::size_t i)       { return data()[i]; }
    const_reference operator[](std::size_t i) const { return data()[i]; }
    
    native_type data_;
    
    BOOST_FORCEINLINE
    iterator data()
    {
      return reinterpret_cast<iterator>(&data_);
    }

    BOOST_FORCEINLINE
    const_iterator data() const
    {
      return const_cast<native&>(*this).data();
    }
  };
} }

namespace boost { namespace simd { namespace meta
{
  template<class T, class X>
  struct zero_initialize< native<T, X> >
  {
    static BOOST_FORCEINLINE native<T, X> call()
    {
      typename native<T, X>::native_type n = {};
      return native<T, X>(n);
    }
  };
} } }

#endif
