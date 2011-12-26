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
#include <boost/assert.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <nt2/sdk/memory/adapted/buffer.hpp>
#include <nt2/sdk/memory/details/buffer_base.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4996) // std::copy may be unsafe
#endif

namespace nt2 {  namespace memory
{
  //============================================================================
  /**!
   *
   *
   **/
  //============================================================================
  template<class Type, std::ptrdiff_t BaseIndex, class Allocator>
  class buffer
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
    typedef typename parent_data::size_type               size_type;
    typedef typename parent_data::difference_type         difference_type;
    typedef typename parent_data::difference_type         index_type;
    
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
    template<typename Sizes>
    buffer( Sizes const& sz, allocator_type const& alloc = allocator_type() )
    : parent_data(alloc)          
    {      
      parent_data::allocate( boost::fusion::at_c<0>(meta::as_sequence(sz)) );
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
      this->copy( src, src.size() );
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
        this->copy(src, src.size());
      }
      return *this;
    }

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
     * Return a (const) reverse_iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    reverse_iterator        rbegin()
    {
      return reverse_iterator(end());
    }
    
    const_reverse_iterator  rbegin() const
    {
      return const_reverse_iterator(end());
    }

    //==========================================================================
    /**!
     * Return a (const) reverse_iterator to the end of the buffer data.
     **/
    //==========================================================================
    reverse_iterator        rend()
    {
      return reverse_iterator(begin());
    }
    
    const_reverse_iterator  rend()   const
    {
      return const_reverse_iterator(begin());
    }

    //==========================================================================
    /**!
     * Return the number of elements accessible through the buffer.
     **/
    //==========================================================================
    using parent_data::size;

    //==========================================================================
    /**!
     * Return \c true if the buffer contains no elements
     **/
    //==========================================================================
    bool empty()  const { return size() != 0u; }

    //==========================================================================
    /**!
     * Return the lowest valid index for accessing a buffer element
     **/
    //==========================================================================
    using parent_data::lower;

    //==========================================================================
    /**!
     * Return the highest valid index for accessing a buffer element
     **/
    //==========================================================================
    using parent_data::upper;

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
    template<class Position>
    BOOST_FORCEINLINE reference operator[](Position const& pos)
    {
      difference_type i = boost::fusion::at_c<0>(meta::as_sequence(pos));
      
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return parent_data::origin_[i];
    }
    
    template<class Position>
    BOOST_FORCEINLINE const_reference operator[](Position const& pos) const
    {
      difference_type i = boost::fusion::at_c<0>(meta::as_sequence(pos));
      
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return parent_data::origin_[i];
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
    template<class Sizes> void resize(Sizes const& sz)
    {
      parent_data::resize( boost::fusion::at_c<0>(meta::as_sequence(sz)) );
    }

    protected:

    using parent_data::allocator;

    void copy( buffer const& src, size_type const& s )
    {
      parent_data::resize(s);
      std::copy(src.begin(),src.end(),begin());
    }
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

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
