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
#include <nt2/sdk/memory/adapted/array_buffer.hpp>

namespace nt2 {  namespace memory
{
  template<class Type, std::size_t N>
  class array_buffer: private boost::array<Type, N>
  {
    public:
    typedef boost::array<Type,N>                          parent_data;

    struct no_allocator {};
    
    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef no_allocator                                    allocator_type;
    typedef typename parent_data::value_type                value_type;
    typedef typename parent_data::iterator                  iterator;
    typedef typename parent_data::const_iterator            const_iterator;
    typedef typename parent_data::reverse_iterator          reverse_iterator;
    typedef typename parent_data::const_reverse_iterator    const_reverse_iterator;
    typedef typename parent_data::reference                 reference;
    typedef typename parent_data::const_reference           const_reference;
    typedef typename parent_data::size_type                 size_type;
    typedef typename parent_data::difference_type           difference_type;
    typedef typename parent_data::difference_type           index_type;

    //==========================================================================
    /**!
     * Default constructor for pointer_buffer. 
     **/
    //==========================================================================
    array_buffer(allocator_type const& = allocator_type())
                : origin_(0), low_(0), up_(-1)
    {}

    template<typename Sizes, typename Bases>
    array_buffer( Sizes const& sz, Bases const& bs
                , allocator_type const& = allocator_type()
                )
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
     * Return a (const) iterator to the biased beginning of the buffer data.
     **/
    //==========================================================================
    const_iterator  origin() const  { return origin_; }
    iterator        origin()        { return origin_; }

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
    iterator        end()       { return begin() + size(); }
    const_iterator  end() const { return begin() + size(); }

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
    difference_type size() const { return up_ - low_ + 1; }

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
    difference_type lower() const { return low_; }

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
      
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return origin_[i];
    }
    
    template<class Position> BOOST_FORCEINLINE
    const_reference operator[](Position const& pos) const
    {
      difference_type i = boost::fusion::at_c<0>(meta::as_sequence(pos));
      
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return origin_[i];
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
      boost::swap(origin_ , src.origin_);
      boost::swap(low_    , src.low_);
      boost::swap(up_     , src.up_);
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

      up_ = boost::fusion::at_c<0>(meta::as_sequence(s)) + low_ -1;
      origin_ = &parent_data::operator[](0) - low_;
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
      low_    = boost::fusion::at_c<0>(meta::as_sequence(bs));
      origin_ = &parent_data::operator[](0) - low_;
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
      low_    = boost::fusion::at_c<0>(meta::as_sequence(bs));
      up_     = boost::fusion::at_c<0>(meta::as_sequence(sz)) + low_ -1;
      origin_ = &parent_data::operator[](0) - low_;
    }

    protected:
    value_type*     origin_;
    difference_type low_, up_;
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
