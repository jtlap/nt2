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
#include <boost/mpl/integral_c.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/adapted/array_buffer.hpp>

namespace nt2 {  namespace memory
{
  template<class T, std::ptrdiff_t N, std::ptrdiff_t BaseIndex>
  struct array_buffer
  {
    public:
    //============================================================================
    // Some fake allocator_type to satisfy Sequence requirement
    //============================================================================
    struct no_allocator
    {
      typedef T*        pointer;
      typedef T const*  const_pointer;
    };

    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef no_allocator                              allocator_type;
    typedef T                                         value_type;
    typedef T*                                        iterator;
    typedef T const*                                  const_iterator;
    typedef T&                                        reference;
    typedef const T&                                  const_reference;
    typedef T*                                        pointer;
    typedef T const*                                  const_pointer;
    typedef std::ptrdiff_t                            size_type;
    typedef std::ptrdiff_t                            difference_type;

    //==========================================================================
    // Default constructor
    //==========================================================================
    array_buffer(allocator_type const& = allocator_type()) {}

    //==========================================================================
    // Constructor from Size. Size information is discarded but checked if
    // comaptible with static storage size
    //==========================================================================
    array_buffer( size_type s, allocator_type const& = allocator_type() ) {}

    const_iterator  raw() const  { return &storage_[0]; }

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
    iterator        end()       { return storage_ + N; }
    const_iterator  end() const { return storage_ + N; }

    //==========================================================================
    /**!
     * Return the number of elements accessible through the buffer.
     **/
    //==========================================================================
    static BOOST_FORCEINLINE size_type size()        { return N; }
    static BOOST_FORCEINLINE size_type inner_size()  { return N; }
    static BOOST_FORCEINLINE size_type outer_size()  { return 1; }

    //==========================================================================
    /**!
     * Return \c true if the buffer contains no elements
     **/
    //==========================================================================
    static BOOST_FORCEINLINE bool empty() { return size() == 0u; }

    //==========================================================================
    /**!
     * Return the lowest valid index for accessing a buffer element
     **/
    //==========================================================================
    static BOOST_FORCEINLINE difference_type lower()       { return BaseIndex; }
    static BOOST_FORCEINLINE difference_type inner_lower() { return BaseIndex; }
    static BOOST_FORCEINLINE difference_type outer_lower() { return 1;         }

    //==========================================================================
    /**!
     * Return the highest valid index for accessing a buffer element
     **/
    //==========================================================================
    static BOOST_FORCEINLINE difference_type upper()       { return N - 1 + BaseIndex; }
    static BOOST_FORCEINLINE difference_type inner_upper() { return upper();           }
    static BOOST_FORCEINLINE difference_type outer_upper() { return 1;                 }

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
    BOOST_FORCEINLINE reference operator()(difference_type i)
    {
      return storage_[i-BaseIndex];
    }

    BOOST_FORCEINLINE const_reference operator()(difference_type i) const
    {
      return storage_[i-BaseIndex];
    }

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
    BOOST_FORCEINLINE reference operator()(difference_type i,difference_type)
    {
      return storage_[i-BaseIndex];
    }

    BOOST_FORCEINLINE const_reference
    operator()(difference_type i,difference_type) const
    {
      return storage_[i-BaseIndex];
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
      return &storage_[i-BaseIndex];
    }

    BOOST_FORCEINLINE const_pointer
    get(difference_type i) const
    {
      return &storage_[i-BaseIndex];
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
      for(size_type i = 0; i < N; ++i) boost::swap(storage_[i],src.storage_[i]);
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
    size_type resize(size_type s) { return N; }

    protected:
    BOOST_SIMD_ALIGNED_TYPE(value_type) storage_[N];
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param a First \c pointer_buffer to swap
   * \param b Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T, std::ptrdiff_t N, std::ptrdiff_t B>
  void swap( array_buffer<T,N,B>& a, array_buffer<T,N,B>& b )
  {
    a.swap(b);
  }
} }

#endif
