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

#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/memory/overload.hpp>
#include <boost/dispatch/error/static_assert.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/simd/sdk/simd/details/native/iterator.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  /// Platform independant native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class Scalar,class Extension> union native
  {
    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> is a SIMD type encapsulation
    ////////////////////////////////////////////////////////////////////////////
    typedef Extension                                       extension_type;
    typedef native<Scalar,Extension>                        this_type;
    typedef typename meta::as_simd<Scalar,Extension>::type  native_type;

    ////////////////////////////////////////////////////////////////////////////
    // native<S,E> models FusionRandomAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef Scalar                                          value_type;
    typedef value_type&                                     reference;
    typedef value_type const&                               const_reference;
    typedef std::size_t                                     size_type;
    typedef details::native_iterator<native>                iterator;
    typedef details::native_iterator<native>                const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // native cast to another type
    ////////////////////////////////////////////////////////////////////////////
    template<class U> struct cast { typedef native<U,extension_type> type; };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    enum { static_size = sizeof(native_type)/sizeof(value_type)
                       ? sizeof(native_type)/sizeof(value_type) : 1}; 

    ////////////////////////////////////////////////////////////////////////////
    // SIMD register value
    ////////////////////////////////////////////////////////////////////////////
    native_type data_;
    value_type  array[static_size];

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from same native types
    ////////////////////////////////////////////////////////////////////////////
    this_type& operator=(this_type const& s)
    {
      data_ = s.data_;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from compatible types
    ////////////////////////////////////////////////////////////////////////////
    template<class S2>
    this_type& operator=(native<S2, extension_type> const& s)
    {
      data_ = native_type(s.data_);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from raw SIMD vector types
    ////////////////////////////////////////////////////////////////////////////
    this_type& operator=(native_type const& s) { data_ = s; return *this;}

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from convertible SIMD vector types
    ////////////////////////////////////////////////////////////////////////////
    template<class V2>
    typename boost::enable_if_c< meta::is_simd_specific<V2,extension_type>::value
                               , this_type&
                               >::type
    operator=(V2 const& s) { data_ = native_type(s); return *this;}

    ////////////////////////////////////////////////////////////////////////////
    // Const-array like interface
    ////////////////////////////////////////////////////////////////////////////
    static std::size_t size() { return static_size; }

    reference        operator[](int i)
    {
      return array[i];
    }

    const_reference  operator[](int i) const
    {
      return array[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // The operator() version is here for some variation of Altivec which fails
    // to perform the proper automatic type-casting on intrinsic calls.
    ////////////////////////////////////////////////////////////////////////////
    operator native_type()    const { return data_; }
    native_type operator()()  const { return data_; }

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(this_type)

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    const_iterator begin() const { return const_iterator(*this,0);      };
    const_iterator end()   const { return const_iterator(*this,size()); };

    ////////////////////////////////////////////////////////////////////////////
    // self-operator methods
    ////////////////////////////////////////////////////////////////////////////
    this_type const& operator+() const { return *this; }
    this_type operator!() const
    {
      boost::dispatch::functor<boost::proto::tag::logical_not> callee;
      return callee(*this);
    }

    this_type operator-() const
    {
      boost::dispatch::functor<boost::proto::tag::negate> callee;
      return callee(*this);
    }

    this_type operator~()  const
    {
      boost::dispatch::functor<boost::proto::tag::complement> callee;
      return callee(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // assignment-operator methods
    ////////////////////////////////////////////////////////////////////////////
    this_type& operator+=(this_type const& src)
    {
      *this = *this + src;
      return *this;
    }

    this_type& operator-=(this_type const& src)
    {
      *this = *this - src;
      return *this;
    }

    this_type& operator*=(this_type const& src)
    {
      *this = *this * src;
      return *this;
    }

    this_type& operator/=(this_type const& src)
    {
      *this = *this / src;
      return *this;
    }

    this_type& operator&=(this_type const& src)
    {
      *this = *this & src;
      return *this;
    }

    this_type& operator|=(this_type const& src)
    {
      *this = *this | src;
      return *this;
    }

    this_type& operator^=(this_type const& src)
    {
      *this = *this ^ src;
      return *this;
    }

    this_type& operator>>=(this_type const& src)
    {
      *this = *this >> src;
      return *this;
    }

    this_type& operator<<=(this_type const& src)
    {
      *this = *this << src;
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Pre/Post Increment/Decrement
    ////////////////////////////////////////////////////////////////////////////
    inline this_type& operator++();
    inline this_type& operator--();
    
    this_type  operator++ (int)
    {
      this_type that = *this;
      this_type::operator++();
      return that;
    }

    this_type  operator-- (int)
    {
      this_type that = *this;
      this_type::operator--();
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Related components
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/details/native/meta.hpp>
#include <boost/simd/sdk/simd/details/native/fusion.hpp>
#include <boost/simd/sdk/simd/details/native/operators.hpp>
#include <boost/simd/sdk/simd/details/native/comparisons.hpp>

#endif
