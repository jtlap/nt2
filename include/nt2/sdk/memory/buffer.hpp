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
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/errors/assert.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/details/is_assignment_compatible.hpp>
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
    ////////////////////////////////////////////////////////////////////////////
    using parent::impl;

    public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    buffer()  : parent()                      { parent::default_init(); }
    buffer( Allocator const& a )  : parent(a) { parent::default_init(); }

    buffer( Base const& b, Size const& s) : parent()
    {
      parent::init(b,s);
    }

    template<class Src>
    buffer( Src const& src
          , typename boost::enable_if_c<
                        details::is_assignment_compatible<buffer,Src>::value
                                      >::type* = 0
          )
    {
      parent::assign((typename Src::parent const&)(src));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assign by resize/copy if same type
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
    // Assign by resize/copy if compatible size
    ////////////////////////////////////////////////////////////////////////////
    template<class Src>
    typename boost::enable_if_c < details
                                ::is_assignment_compatible<buffer,Src>::value
                                , buffer&
                                >::type
    operator=( Src const& src )
    {
      NT2_ASSERT((details::is_assignment_compatible<buffer,Src>()(*this,src)));
      parent::assign((typename Src::parent const&)(src));
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assign data by copy
    ////////////////////////////////////////////////////////////////////////////
    template<class Src> void fill( Src const& src )
    {
      parent::fill((typename Src::parent const&)(src));
    }

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
    // Random Acces through operator[]
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
    // Access to raw data
    ////////////////////////////////////////////////////////////////////////////
    pointer origin()  const { return impl.origin_;  }
    pointer begin()   const { return impl.begin_;   }
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
