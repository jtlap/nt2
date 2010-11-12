/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_BUFFER_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Data buffer with NRC like interface
// Basically a std::vector that copes well with bool and use NRC like allocation
// interface and parametrization
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/error/assert.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/details/buffer_base.hpp>

namespace nt2 { namespace memory
{
  template<class Type, class Base, class Size, class Allocator>
  class buffer
      : public details::buffer_base<Type,Base,Size,Allocator>
  {
    public:
    ////////////////////////////////////////////////////////////////////////////
    // Public types
    // buffer<Type,Base,Size,Allocator> models:
    //  - RandomAccessContainer
    //  - RandomAccessRange
    ////////////////////////////////////////////////////////////////////////////
    typedef details::buffer_base<Type,Base,Size,Allocator>  parent;
    typedef Base                                            base_value_type;
    typedef Size                                            size_value_type;
    typedef typename parent::allocator_type                 allocator_type;
    typedef typename parent::value_type                     value_type;
    typedef typename parent::pointer                        pointer;
    typedef typename parent::const_pointer                  const_pointer;
    typedef typename parent::reference                      reference;
    typedef typename parent::const_reference                const_reference;
    typedef typename parent::size_type                      size_type;
    typedef typename parent::difference_type                difference_type;
    typedef typename parent::index_type                     index_type;
    typedef typename parent::has_static_base                has_static_base;
    typedef typename parent::has_static_size                has_static_size;
    typedef typename parent::is_static                      is_static;

    private:
    ////////////////////////////////////////////////////////////////////////////
    // Inherited data
    // We use a similar structure than the original std::vector to assess a
    // significant level of exception safety.
    ////////////////////////////////////////////////////////////////////////////
    using parent::impl;

    public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    buffer()                              : parent()  { parent::default_init(); }
    buffer( Allocator const& a )          : parent(a) { parent::default_init(); }
    buffer( Base const& b, Size const& s) : parent()  { parent::init(b,s);      }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator
    // TODO: 0x support for assigning from rvalue reference
    ////////////////////////////////////////////////////////////////////////////
    buffer& operator=( buffer const& src )
    {
      if(this != &src) parent::assign(src);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( buffer& src ) { parent::swap(src); }

    ////////////////////////////////////////////////////////////////////////////
    // Inherited size modifiers
    ////////////////////////////////////////////////////////////////////////////
    using parent::rebase;
    using parent::resize;
    using parent::restructure;

    ////////////////////////////////////////////////////////////////////////////
    // Inherited size accessors
    ////////////////////////////////////////////////////////////////////////////
    using parent::size;
    using parent::lower;
    using parent::upper;

    ////////////////////////////////////////////////////////////////////////////
    // Access to raw data
    ////////////////////////////////////////////////////////////////////////////
    const_pointer origin()  const { return impl.origin_;  }
          pointer origin()        { return impl.origin_;  }

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainner Interface
    ////////////////////////////////////////////////////////////////////////////
    reference operator[](difference_type const& i)
    {
      NT2_ASSERT( (i >= lower()) && (i <= upper()) );
      return impl.begin_[i];
    }

    const_reference operator[](difference_type const& i) const
    {
      NT2_ASSERT( (i >= lower()) && (i <= upper()) );
      return impl.begin_[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    const_pointer begin()   const { return impl.begin_;   }
          pointer begin()         { return impl.begin_;   }
    const_pointer end()     const { return impl.end_;     }
          pointer end()           { return impl.end_;     }
  };

  //////////////////////////////////////////////////////////////////////////////
  // ADL swap
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Base, class Size, class Allocator>
  void swap ( buffer<T,Base,Size,Allocator>& a
            , buffer<T,Base,Size,Allocator>& b
            )
  {
    a.swap(b);
  }
} }

#endif
