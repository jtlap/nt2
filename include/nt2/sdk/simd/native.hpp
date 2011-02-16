/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_HPP_INCLUDED

#include <nt2/sdk/meta/fusion.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/memory/overload.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/simd/meta/is_vectorizable.hpp>
#include <nt2/sdk/simd/details/native/iterator.hpp>

namespace nt2 { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  /// Platform independant native SIMD type
  //////////////////////////////////////////////////////////////////////////////
  template<class Scalar,class Extension> struct native
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
    typedef value_type                                      reference;
    typedef value_type                                      const_reference;
    typedef std::size_t                                     size_type;
    typedef details::native_iterator<native>                iterator;
    typedef details::native_iterator<native>                const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // hierarchy tag for native
    ////////////////////////////////////////////////////////////////////////////
    typedef meta::simd_ < typename meta::hierarchy_of<Scalar>::type
                        , Extension
                        >                                   nt2_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // native cast to another type
    ////////////////////////////////////////////////////////////////////////////
    template<class U> struct cast { typedef native<U,extension_type> type; };

    ////////////////////////////////////////////////////////////////////////////
    // vector size
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT ( size_type
                          , static_size = sizeof(native_type)/sizeof(value_type)
                                        ? sizeof(native_type)/sizeof(value_type)
                                        : 1
                          );

    ////////////////////////////////////////////////////////////////////////////
    // union based type for value extraction
    ////////////////////////////////////////////////////////////////////////////
    union extraction_type { native_type v; value_type s[static_size]; };

    ////////////////////////////////////////////////////////////////////////////
    // SIDM register value
    ////////////////////////////////////////////////////////////////////////////
    native_type data_;

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from compatible types
    ////////////////////////////////////////////////////////////////////////////
    template<class S2>
    this_type& operator=(native<S2, extension_type> const& s)
    {
      data_ = native_type(s.data_);
      return *this;
    }

    this_type& operator=(native_type const& s) { data_ = s; return *this;}

    template<class V2>
    typename boost::enable_if_c< meta::is_simd_specific<V2,extension_type>::value
                               , this_type&
                               >::type
    operator=(V2 const& s) { data_ = native_type(s); return *this;}

    ////////////////////////////////////////////////////////////////////////////
    // Const-array like interface
    ////////////////////////////////////////////////////////////////////////////
    static std::size_t size() { return static_size; }

    const_reference  operator[](int i) const
    {
      // we need to return in memory as using reinterpret_cast is an UB here
      extraction_type const that = {data_};
      return that.s[i];
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
    NT2_MEMORY_OVERLOAD_NEW_DELETE(this_type)

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
      functor<tag::logical_not_> callee;
      return callee(*this);
    }

    this_type operator-() const
    {
      functor<tag::unary_minus_> callee;
      return callee(*this);
    }

    this_type operator~()  const
    {
      functor<tag::complement_> callee;
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
    this_type& operator++() { *this += One<this_type>();  return *this; }
    this_type& operator--() { *this -= One<this_type>();  return *this; }

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
#include <nt2/sdk/simd/details/native/meta.hpp>
#include <nt2/sdk/simd/details/native/fusion.hpp>
#include <nt2/sdk/simd/details/native/constants.hpp>
#include <nt2/sdk/simd/details/native/functions.hpp>
#include <nt2/sdk/simd/details/native/operators.hpp>
#include <nt2/sdk/simd/details/native/comparisons.hpp>

#endif
