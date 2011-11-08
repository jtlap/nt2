//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_VIEW_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_VIEW_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost { namespace simd
{
  template<class T>
  struct index_iterator
   : boost::iterator_facade< index_iterator<T>
                           , typename T::value_type
                           , random_access_traversal_tag
                           , typename T::reference
                           >
  {
    index_iterator(T& t_, std::size_t pos_) : t(t_), pos(pos_) {}
      
  private:
    friend class boost::iterator_core_access;
    
    void increment() { ++pos; }
    void decrement() { --pos; }
    void advance(std::size_t n) { pos += n; }
    typename T::reference dereference() const { return t[pos]; }
    std::size_t distance_to(index_iterator const& other)
    {
      return &other.t[other.pos] - &t[pos];
    }
    
    bool equal(index_iterator const& other) const
    {
      return &t[pos] == &t[other.pos];
    }
    
    T& t;
    std::size_t pos;
  };
    
  template<class Scalar, class Extension>
  struct native_view
  {
    typedef typename remove_const<Scalar>::type             value_type;
    typedef value_type&                                     reference;
    typedef reference                                       const_reference;
    typedef std::size_t                                     size_type;
    typedef index_iterator                                  iterator;
    typedef iterator                                        const_iterator;

    template<class U> struct rebind
    {
      typedef native_view<U, extension_type> type;
    };

    typedef Extension                                       extension_type;
    typedef typename meta::
            as_simd<value_type, Extension>::type            native_type;
    typedef native<value_type, Extension>                   sequence_type;
    typedef typename dispatch::meta::
            as_integer<sequence_type>::type                 index_type;

    static const std::size_t static_size = sequence_type::static_size;
    
    BOOST_FORCEINLINE
    native_view& operator=(native_view const& s)
    {
      base = s.base;
      indexes = s.indexes;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator from native vector type
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    native_view& operator=(native_type const& data)
    {
      sequence_type const that = { data };
      return *this = that;
    }
    
    BOOST_FORCEINLINE
    native_view& operator=(sequence_type const& data)
    {
      store(data, base, indexes);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Type casting operator for compatibility with intrinsic functions
    // Use operator() for explicit conversion.
    ////////////////////////////////////////////////////////////////////////////    
    BOOST_FORCEINLINE
    operator sequence_type() const { return (*this)(); }
    
    BOOST_FORCEINLINE
    sequence_type operator() const { return load<sequence_type>(base, indexes); }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    const_iterator       begin() const  { return iterator(*this, 0); };
    
    BOOST_FORCEINLINE
    const_iterator       end()   const  { return iterator(*this, static_size); };
    
    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_FORCEINLINE
    std::size_t size() { return static_size; }

    static BOOST_FORCEINLINE
    bool empty()       { return false; }

    BOOST_FORCEINLINE
    reference operator[](std::size_t i) const
    {
      return base[indexes[i]];
    }
    
    Scalar* base;
    index_type indexes;
  };
  
} }

#endif
