//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ARRAY_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ARRAY_BUFFER_HPP_INCLUDED

#include <boost/swap.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <nt2/core/container/memory/adapted/array_buffer.hpp>

namespace nt2 {  namespace memory
{
  template<class Type, std::size_t N>
  class array_buffer: private boost::array<Type, N>
  {
    public:
    typedef boost::array<Type,N>                          parent_data;

    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef typename parent_data::value_type               value_type;
    typedef typename parent_data::iterator                 iterator;
    typedef typename parent_data::const_iterator           const_iterator;
    typedef typename parent_data::reverse_iterator         reverse_iterator;
    typedef typename parent_data::const_reverse_iterator   const_reverse_iterator;
    typedef typename parent_data::reference                reference;
    typedef typename parent_data::const_reference          const_reference;
    typedef typename parent_data::size_type                size_type;
    typedef typename parent_data::difference_type          difference_type;
    typedef typename parent_data::difference_type          index_type;

    //==========================================================================
    /**!
     * Default constructor for pointer_buffer. 
     **/
    //==========================================================================
    array_buffer() : base_(0), size_(0) {}

    template<typename Sizes, typename Bases>
    array_buffer( Sizes const& sz, Bases const& bs )
    {
      restructure(sz,bs);
    }

    //==========================================================================
    /**!
     * Constructs a array_buffer from a boost::array of \c Type, a dimension set
     * and a base index sets.
     *
     * \param src A boost::array of \c Type value.
     * \param sz  A single elment Boost.Fusion \c RandomAccessSequence
     * or an integral value containing the number of elements of the buffer.
     * \param bs  A single elment Boost.Fusion \c RandomAccessSequence
     * or an integral value containing the base index of the buffer.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    array_buffer( parent_data const& src, Sizes const& sz, Bases const& bs )
      : parent_data(src)
    {      
      restructure(sz,bs);
    }

    //==========================================================================
    /**!
     * Copy constructor for array_buffer.
     *
     * \param src array_buffer to copy
     **/
    //==========================================================================
    array_buffer( array_buffer const& src )
    : parent_data(src), base_(src.base_), size_(src.size_)
    {}

    //==========================================================================
    /**!
     * Assign a buffer to the current buffer with Strong Garantee
     *
     * \param src buffer to assign
     * \return The updated \c array_buffer pointing to the same boost::array and 
     * with corresponding size and base
     **/
    //==========================================================================
    array_buffer& operator=(array_buffer const& src)
    {
      parent_data::operator=(src);
      base_ = src.base_;
      size_ = src.size_;
      return *this;
    }

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
    iterator        end()       { return begin() + size_; }
    const_iterator  end() const { return begin() + size_; }

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
    difference_type size() const { return size_; }

    //==========================================================================
    /**!
     * Return \c true if the buffer contains no elements
     **/
    //==========================================================================
    bool empty() const { return size_ == 0u; }

    //==========================================================================
    /**!
     * Return the lowest valid index for accessing a buffer element
     **/
    //==========================================================================
    difference_type lower() const { return base_; }

    //==========================================================================
    /**!
     * Return the highest valid index for accessing a buffer element
     **/
    //==========================================================================
    difference_type upper() const { return size() - 1 + base_;  }

    //==========================================================================
    /**!
     * Return the ith element of the buffer.
     *
     * \param i Index of the element to retrieve. Note that \c i should be no
     * lesser than lower() nor bigger than upper() to be valid.
     **/    
    //==========================================================================
    reference
    operator[](difference_type const& i)
    {
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
      return parent_data::operator[](i - base_);
    }

    const_reference
    operator[](difference_type const& i) const
    {
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
      return parent_data::operator[](i - base_);
    }

    //==========================================================================
    /**!
     * Swap the contents of the buffer with another one.
     *
     * \param src buffer to swap with
     **/
    //==========================================================================
    void swap( array_buffer& src )
    {
      boost::swap(base_, src.base_);
      boost::swap(size_, src.size_);
      parent_data::swap(src);
    }

    //==========================================================================
    /**!
     * Change the size of the buffer. This operation is done in constant
     * time and don't trigger any reallocation.
     *
     * \param b A Boost.Fusion \c RandomAccessSequence containing the new base
     * index.
     **/
    //==========================================================================
    template<class Sizes> void resize(Sizes const& s)
    {
      BOOST_ASSERT_MSG( (boost::fusion::at_c<0>(meta::as_sequence(s)) <= N)
                      , "Allocation request too much memory"
                      );      
      size_ = boost::fusion::at_c<0>(meta::as_sequence(s)); 
    }
    
    //==========================================================================
    /**!
     * Change the base index of the buffer. This operation is done in constant
     * time and don't trigger any reallocation.
     *
     * \param b A Boost.Fusion \c RandomAccessSequence containing the new base
     * index.
     **/
    //==========================================================================
    template<class Bases> void rebase(Bases const& bs)
    { 
      base_ = boost::fusion::at_c<0>(meta::as_sequence(bs)); 
    }

    //==========================================================================
    /**!
     * Change the size and base index of the buffer. This operation is done by
     * calling resize and rebase.
     *
     * \param s A Boost.Fusion \c RandomAccessSequence containing the new size.
     * \param b A Boost.Fusion \c RandomAccessSequence containing the new base
     * index.
     **/
    //==========================================================================
    template<class Bases, class Sizes>
    void restructure( Sizes const& sz, Bases const& bs )
    {
      resize(sz);
      rebase(bs);
    }

    protected:
    difference_type base_;
    size_type       size_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param a First \c pointer_buffer to swap
   * \param b Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, std::size_t N>
  void swap( array_buffer<T,N>& a, array_buffer<T,N>& b )
  {
    a.swap(b);
  }
} } 

#endif
