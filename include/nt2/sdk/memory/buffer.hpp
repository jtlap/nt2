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
#include <nt2/sdk/memory/details/block_base.hpp>

namespace nt2 { namespace memory
{
  template< class Type, class Lower, class Upper
          , class Allocator = allocator<Type>
          >
  class buffer
      : public details::buffer_base<Type,Lower,Upper,Allocator>
  {
    public:
    ////////////////////////////////////////////////////////////////////////////
    // Public types
    ////////////////////////////////////////////////////////////////////////////
    typedef details::buffer_base< Type,Lower,Upper,Allocator> parent;
    typedef typename parent::allocator_type                   allocator_type;
    typedef typename parent::value_type                       value_type;
    typedef typename parent::pointer                          pointer;
    typedef typename parent::const_pointer                    const_pointer;
    typedef typename parent::reference                        reference;
    typedef typename parent::const_reference                  const_reference;
    typedef typename parent::size_type                        size_type;
    typedef typename parent::difference_type                  difference_type;

    ////////////////////////////////////////////////////////////////////////////
    // Inherited data
    ////////////////////////////////////////////////////////////////////////////
    using parent::impl;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    buffer()  : parent()                      { parent::default_init(); }
    buffer( Allocator const& a )  : parent(a) { parent::default_init(); }

    buffer( Lower const& l, Upper const& u) : parent()
    {
      NT2_ASSERT(l <= u);
      parent::init(l,u);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assign by resize/copy
    ////////////////////////////////////////////////////////////////////////////
    buffer&  operator=( buffer const& src )
    {
      if(this != &src) parent::assign(src);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Inherited accessor
    ////////////////////////////////////////////////////////////////////////////
    using parent::size;
    using parent::capacity;
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
    pointer begin()   const { return impl.origin_; }
  };

  //////////////////////////////////////////////////////////////////////////////
  // swap for ADL
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class L, class U, class A>
  void swap(buffer<T,L,U,A>& a, buffer<T,L,U,A>& b)
  {
    a.swap(b);
  }
} }

#endif
