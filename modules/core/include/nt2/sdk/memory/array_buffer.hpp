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
#include <boost/mpl/integral_c.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/adapted/array_buffer.hpp>

namespace nt2 {  namespace memory
{
  template<class T, std::size_t N, std::ptrdiff_t BaseIndex>
  struct array_buffer
  {
    public:
    //============================================================================
    // Some fake allocator_type to satisfy Sequence requirement
    //============================================================================
    struct no_allocator {};
    
    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef no_allocator                                      allocator_type;
    typedef T                                                 value_type;
    typedef T*                                                iterator;
    typedef const T*                                          const_iterator;
    typedef std::reverse_iterator<iterator>                   reverse_iterator;
    typedef std::reverse_iterator<const_iterator>             const_reverse_iterator;
    typedef T&                                                reference;
    typedef const T&                                          const_reference;
    typedef std::size_t                                       size_type;
    typedef std::ptrdiff_t                                    difference_type;
    typedef std::ptrdiff_t                                    index_type;
    typedef boost::mpl::integral_c<std::ptrdiff_t,BaseIndex>  base_index_type;

    //==========================================================================
    /**!
     * Default constructor for pointer_buffer. 
     **/
    //==========================================================================
    array_buffer(allocator_type const& = allocator_type())
                : up_(BaseIndex-1)
    {}

    template<typename Sizes>
    array_buffer( Sizes const& sz, allocator_type const& = allocator_type() )
    {
      resize(sz);
    }

    //==========================================================================
    /**!
     * Return a (const) iterator to the biased beginning of the buffer data.
     **/
    //==========================================================================
    const_iterator  origin() const  { return &storage_[0] - BaseIndex; }
    iterator        origin()        { return &storage_[0] - BaseIndex; }

    //==========================================================================
    /**!
     * Return a (const) iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    iterator        begin()       { return storage_; }
    const_iterator  begin() const { return storage_; }

    //==========================================================================
    /**!
     * Return a (const) iterator to the end of the buffer data.
     **/
    //==========================================================================
    iterator        end()       { return storage_ + size(); }
    const_iterator  end() const { return storage_ + size(); }

    //==========================================================================
    /**!
     * Return a (const) reverse_iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    reverse_iterator rbegin()
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
    reverse_iterator rend()
    {
      return reverse_iterator(begin());
    }
    
    const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }
    
    //==========================================================================
    /**!
     * Return the number of elements accessible through the buffer.
     **/
    //==========================================================================
    difference_type size() const { return up_ - BaseIndex + 1; }

    //==========================================================================
    /**!
     * Return \c true if the buffer contains no elements
     **/
    //==========================================================================
    bool empty() const { return size() == 0u; }

    //==========================================================================
    /**!
     * Return the lowest valid index for accessing a buffer element
     **/
    //==========================================================================
    difference_type lower() const { return BaseIndex; }

    //==========================================================================
    /**!
     * Return the highest valid index for accessing a buffer element
     **/
    //==========================================================================
    difference_type upper() const { return up_;  }

    //==========================================================================
    /**!
     * Return the ith element of the buffer.
     *
     * \param  pos 1D Index of the element to retrieve passed either as an
     * integral value or as a Fusion RandomAccessSequence of size 1.
     * Note that \c pos should be no lesser than lower() nor bigger than upper()
     * to be valid.
     **/    
    //==========================================================================
    template<class Position> BOOST_FORCEINLINE
    reference operator[](Position const& pos)
    {
      difference_type i = boost::fusion::at_c<0>(meta::as_sequence(pos));
      
      BOOST_ASSERT_MSG( (i >= BaseIndex)
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return storage_[i-BaseIndex];
    }
    
    template<class Position> BOOST_FORCEINLINE
    const_reference operator[](Position const& pos) const
    {
      difference_type i = boost::fusion::at_c<0>(meta::as_sequence(pos));
      
      BOOST_ASSERT_MSG( (i >= BaseIndex)
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return storage_[i-BaseIndex];
    }
    
    //==========================================================================
    /**!
     * Swap the contents of the buffer with another one.
     *
     * \param src buffer to swap with
     **/
    //==========================================================================
    template<std::ptrdiff_t B2>
    void swap( array_buffer<T,N,B2>& src )
    {
      size_type sz = src.size();
      src.resize(size());
      resize(sz);
      
      for(size_type i = 0; i < N; ++i)
        boost::swap(storage_[i],src.storage_[i]);
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

      up_ = boost::fusion::at_c<0>(meta::as_sequence(s)) + BaseIndex -1;
    }

    BOOST_SIMD_ALIGNED_TYPE(value_type) storage_[N];
    difference_type                     up_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param a First \c pointer_buffer to swap
   * \param b Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, std::size_t N, std::ptrdiff_t B1, std::ptrdiff_t B2>
  void swap( array_buffer<T,N,B1>& a, array_buffer<T,N,B2>& b )
  {
    a.swap(b);
  }
} } 

#endif
