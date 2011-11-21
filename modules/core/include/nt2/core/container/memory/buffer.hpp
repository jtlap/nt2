/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_MEMORY_BUFFER_HPP_INCLUDED 
#define NT2_CORE_CONTAINER_MEMORY_BUFFER_HPP_INCLUDED 

////////////////////////////////////////////////////////////////////////////////
// Data buffer with NRC like interface
// Basically a std::vector that copes well with bool and use NRC like allocation
// interface and parametrization
////////////////////////////////////////////////////////////////////////////////
#include <boost/assert.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/details/buffer_base.hpp>
#include <nt2/core/container/memory/adapted/buffer.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4996) // std::copy may be unsafe
#endif

namespace nt2 { namespace memory
{
  template<class Type,class Allocator = memory::allocator<Type> >
  class buffer
      : private
        details::buffer_data< typename Allocator::template rebind<Type>::other >
  {
    public:

    typedef typename Allocator::template rebind<Type>::other  parent_allocator;
    typedef details::buffer_data<parent_allocator>            parent_data;


    ////////////////////////////////////////////////////////////////////////////
    // Forwarded types
    ////////////////////////////////////////////////////////////////////////////
    typedef typename parent_data::value_type       value_type;
    typedef typename parent_data::pointer          pointer;
    typedef typename parent_data::const_pointer    const_pointer;
    typedef typename parent_data::pointer          iterator;
    typedef typename parent_data::const_pointer    const_iterator;
    typedef typename parent_data::reference        reference;
    typedef typename parent_data::const_reference  const_reference;
    typedef typename parent_data::size_type        size_type;
    typedef typename parent_data::difference_type  difference_type;
    typedef typename parent_data::difference_type  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor & destructor
    ////////////////////////////////////////////////////////////////////////////
    buffer( Allocator const& a = Allocator() )
          : parent_data(a)
    {
      parent_data::allocate(0,0);
    }

    template<class Base, class Size>
    buffer( Base const& b
          , Size const& s
          , Allocator const& a = Allocator()
          )
          : parent_data(a)
    {
      parent_data::allocate(b,s);
    }

    buffer( buffer const& src )
          : parent_data(src.allocator())
    {
      restructure(src.lower(),src.size());
      std::copy(src.begin(),src.end(),begin());
    }

    ~buffer() { parent_data::deallocate(); }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator - SG version
    ////////////////////////////////////////////////////////////////////////////
    buffer& operator=(buffer const& src)
    {
      // we want to have a Strong Garantee and yet be performant
      // so we check if we need some resizing
      if(src.size() > this->size())
      {
        // If we do, use the SG copy+swap method
        buffer that(src);
        swap(that);
      }
      else
      {
        // If not we just need to resize/rebase and copy which is SG here
        restructure(src.lower(),src.size());
        std::copy(src.begin(),src.end(),begin());
      }
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::begin;
    using parent_data::end;
    using parent_data::first;
    using parent_data::last;

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::lower;
    using parent_data::upper;
    using parent_data::size;

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////
    typename parent_data::reference
    operator[](typename parent_data::difference_type const& i)
    {
      BOOST_ASSERT( (i >= lower()) && (i <= upper()) );
      return parent_data::begin_[i];
    }

    typename parent_data::const_reference
    operator[](typename parent_data::difference_type const& i) const
    {
      BOOST_ASSERT( (i >= lower()) && (i <= upper()) );
      return parent_data::begin_[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( buffer& src )
    {
      parent_data::swap(src);
      boost::swap(allocator(),src.allocator());
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::rebase;

    template<class Size>
    void resize(Size s) { parent_data::resize(s); }

    template<class Base,class Size>
    void restructure( Base const& b, Size const& s )
    {
      resize(s);
      rebase(b);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::allocator;
  };

  //////////////////////////////////////////////////////////////////////////////
  // ADL swap
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Allocator>
  void swap( buffer<T,Allocator>& a, buffer<T,Allocator>& b )
  {
    a.swap(b);
  }
} } 

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
