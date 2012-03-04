//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_BUFFER_HPP_INCLUDED

//==============================================================================
/**!
 * @file
 * Defines the nt2::memory::buffer class and related interface
 **/
//==============================================================================
#include <iterator>
#include <boost/assert.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <nt2/sdk/memory/adapted/buffer.hpp>
#include <nt2/sdk/memory/details/buffer_base.hpp>
#include <boost/detail/workaround.hpp>

namespace nt2 {  namespace memory
{
  //============================================================================
  /**!
   *
   *
   **/
  //============================================================================
  template<class Type, std::ptrdiff_t BaseIndex, class Allocator>
  struct buffer
      : private
        details::buffer_data< BaseIndex
                            , typename Allocator::template rebind<Type>::other
                            >
  {
    public:
    //==========================================================================
    // Inheritance type definition
    //==========================================================================
    typedef typename Allocator::template rebind<Type>::other  allocator_type;
    typedef details::buffer_data<BaseIndex,allocator_type>    parent_data;

    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef typename parent_data::value_type              value_type;
    typedef typename parent_data::iterator                iterator;
    typedef typename parent_data::const_iterator          const_iterator;
    typedef typename parent_data::reverse_iterator        reverse_iterator;
    typedef typename parent_data::const_reverse_iterator  const_reverse_iterator;
    typedef typename parent_data::reference               reference;
    typedef typename parent_data::const_reference         const_reference;
    typedef typename parent_data::pointer                 pointer;
    typedef typename parent_data::const_pointer           const_pointer;
    typedef typename parent_data::size_type               size_type;
    typedef typename parent_data::difference_type         difference_type;

    //==========================================================================
    /**!
     * Default constructor for buffer.
     **/
    //==========================================================================
    buffer( Allocator const& a = Allocator() ) : parent_data(a) {}

    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================
    buffer( size_type sz, allocator_type const& alloc = allocator_type() )
    : parent_data(alloc)
    {
      parent_data::allocate( sz );
    }

    //==========================================================================
    /**!
     * Copy constructor for buffer.
     *
     * \param src pointer_buffer to copy
     **/
    //==========================================================================
    buffer( buffer const& src ) : parent_data(src.allocator())
    {
      parent_data::allocate(src.size());
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
      stdext::unchecked_copy(src.begin(),src.end(),begin());
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
      std::copy(src.begin(),src.end(),stdext::make_unchecked_array_iterator(begin()));
#else
      std::copy(src.begin(),src.end(),begin());
#endif
    }

    //==========================================================================
    /**!
     * \c buffer destructor
     **/
    //==========================================================================
    ~buffer() { parent_data::deallocate(); }

    //==========================================================================
    /**!
     * Assign a buffer to the current buffer using a copy scheme with Strong
     * Garantee with respect to exception handling
     *
     * \param src buffer to assign
     * \return The now updated buffer so that *this == src
     **/
    //==========================================================================
    buffer& operator=(buffer const& src)
    {
      // check if we need some resizing
      if(src.size() > this->size())
      {
        // Use the SG copy+swap method
        buffer that(src);
        swap(that);
      }
      else
      {
        parent_data::resize(src.size());

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
        stdext::unchecked_copy(src.begin(),src.end(),parent_data::begin());
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)
        std::copy(src.begin(),src.end(),stdext::make_unchecked_array_iterator(parent_data::begin()));
#else
        std::copy(src.begin(),src.end(),parent_data::begin());
#endif
      }
      return *this;
    }

    const_pointer raw() const { return parent_data::begin(); }

    //==========================================================================
    /**!
     * Return a (const) pointer to the biased beginning of the buffer data
     **/
    //==========================================================================
    using parent_data::origin;

    //==========================================================================
    /**!
     * Return a (const) iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    using parent_data::begin;

    //==========================================================================
    /**!
     * Return a (const) iterator to the end of the buffer data.
     **/
    //==========================================================================
    using parent_data::end;

    //==========================================================================
    /**!
     * Return the number of elements accessible through the buffer.
     **/
    //==========================================================================
    using parent_data::size;
    using parent_data::inner_size;
    using parent_data::outer_size;

    //==========================================================================
    /**!
     * Return \c true if the buffer contains no elements
     **/
    //==========================================================================
    bool empty()  const { return size() == 0u; }

    //==========================================================================
    /**!
     * Return the lowest valid index for accessing a buffer element
     **/
    //==========================================================================
    using parent_data::lower;
    using parent_data::inner_lower;
    using parent_data::outer_lower;

    //==========================================================================
    /**!
     * Return the highest valid index for accessing a buffer element
     **/
    //==========================================================================
    using parent_data::upper;
    using parent_data::inner_upper;
    using parent_data::outer_upper;

    //==========================================================================
    /**!
     * Return the ith element of the buffer.
     *
     * \param pos 1D Index of the element to retrieve passed either as an
     * integral value or as a Fusion RandomAccessSequence of size 1.
     * Note that \c pos should be no lesser than lower() nor bigger than upper()
     * to be valid.
     **/
    //==========================================================================
    BOOST_FORCEINLINE reference operator()(difference_type i)
    {
      return parent_data::origin_[i];
    }

    BOOST_FORCEINLINE const_reference operator()(difference_type i) const
    {
      return parent_data::origin_[i];
    }

    //==========================================================================
    /**!
     * Return the ith element of the buffer.
     *
     * \param pos 1D Index of the element to retrieve passed either as an
     * integral value or as a Fusion RandomAccessSequence of size 1.
     **/
    //==========================================================================
    BOOST_FORCEINLINE reference operator()(difference_type i, difference_type )
    {
      return parent_data::origin_[i];
    }

    BOOST_FORCEINLINE const_reference
    operator()(difference_type i, difference_type ) const
    {
      return parent_data::origin_[i];
    }

    //==========================================================================
    /**!
     * Return a pointer to the ith element of the buffer.
     *
     * \param  pos 1D Index of the element to point
     **/
    //==========================================================================
    BOOST_FORCEINLINE pointer
    get(difference_type i)
    {
      return &parent_data::origin_[i];
    }

    BOOST_FORCEINLINE const_pointer
    get(difference_type i) const
    {
      return &parent_data::origin_[i];
    }

    //==========================================================================
    /**!
     * Swap the contents of the buffer with another one.
     *
     * \param src buffer to swap with
     **/
    //==========================================================================
    void swap( buffer&src )
    {
      parent_data::swap( src );
      boost::swap(allocator(),src.allocator());
    }

    //==========================================================================
    /**!
     * Change the size of the buffer. This operation is done in constant
     * time and don't trigger any reallocation.
     *
     * \param s A Boost.Fusion \c RandomAccessSequence containing the new size.
     **/
    //==========================================================================
    size_type resize(size_type sz) { return parent_data::resize( sz ); }

    protected:
    using parent_data::allocator;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   **/
  //============================================================================
  template<class T, std::ptrdiff_t B1, std::ptrdiff_t B2, class A>
  void swap( buffer<T,B1,A>& a, buffer<T,B2,A>& b )
  {
    a.swap(b);
  }
} }

#endif
