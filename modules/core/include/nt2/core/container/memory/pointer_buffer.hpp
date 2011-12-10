//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED

#include <iterator>
#include <boost/swap.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/core/container/memory/adapted/pointer_buffer.hpp>

namespace nt2 { namespace memory
{
  template<class Type> class pointer_buffer
  {
    public:
    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef typename boost::simd::memory::allocator<Type> allocator_type;
    typedef Type                                          value_type;
    typedef Type*                                         pointer;
    typedef const Type*                                   const_pointer;
    typedef Type*                                         iterator;
    typedef const Type*                                   const_iterator;
    typedef std::reverse_iterator<iterator>               reverse_iterator;      
    typedef std::reverse_iterator<const_iterator>         const_reverse_iterator;
    typedef Type&                                         reference;
    typedef const Type&                                   const_reference;
    typedef std::size_t                                   size_type;
    typedef std::ptrdiff_t                                difference_type;
    typedef std::ptrdiff_t                                index_type;

    //==========================================================================
    /**!
     * Default constructor for pointer_buffer. 
     **/
    //==========================================================================
    pointer_buffer(allocator_type const& = allocator_type()) 
    {
      base_ = 0;
      begin_ = end_ = 0;
    }

    //==========================================================================
    /**!
     * Constructs a pointer_buffer from a pointer to \c Type, a dimension set
     * and a base index sets.
     *
     * \param src A pointer to \c Type value.
     * \param sz  A Boost.Fusion \c RandomAccessSequence containing the number
     * of elements of the buffer.
     * \param bs  A Boost.Fusion \c RandomAccessSequence containing the base
     * index of the buffer.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    pointer_buffer( Type*           const& src
                  , Sizes           const& sz
                  , Bases           const& bs
                  , allocator_type const& = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    : base_(0), begin_(src), end_(src)
    {
      // If you trigger this assertion, your size sequence is missized
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      // If you trigger this assertion, your index sequence is missized
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );
      
      if(begin_) restructure(sz,bs);
    }

    //==========================================================================
    /**!
     * Copy constructor for pointer_buffer. When copied, a pointer_buffer shares
     * the pointer it refers too.
     *
     * \param src pointer_buffer to copy
     **/
    //==========================================================================
    pointer_buffer( pointer_buffer const& src )
      : base_(src.base_), begin_(src.begin_), end_(src.end_)
    {}

    //==========================================================================
    /**!
     * \c pointer_buffer destructor leave memory management to the actual
     * pointer's owner.
     **/
    //==========================================================================
    ~pointer_buffer() {}

    //==========================================================================
    /**!
     * Assign a buffer to the current buffer 
     *
     * \param src buffer to assign
     * \return The updated \c pointer_buffer pointing to the same pointer and 
     * with corresponding size and base
     **/
    //==========================================================================
    pointer_buffer& operator=(pointer_buffer const& src)
    {
      begin_ = src.begin_;
      end_   = src.end_;
      base_  = src.base_;

      return *this;
    }

    //==========================================================================
    /**!
     * Return a (const) iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    iterator        begin()       { return begin_ + base_; }
    const_iterator  begin() const { return begin_ + base_; }

    //==========================================================================
    /**!
     * Return a (const) iterator to the end of the buffer data.
     **/
    //==========================================================================
    iterator        end()       { return end_  + base_; }
    const_iterator  end() const { return end_  + base_; }

    //==========================================================================
    /**!
     * Return a (const) reverse_iterator to the beginning of the buffer data.
     **/
    //==========================================================================
    reverse_iterator        rbegin()       { return reverse_iterator(end());          }
    const_reverse_iterator  rbegin() const { return const_reverse_iterator(end());    }

    //==========================================================================
    /**!
     * Return a (const) reverse_iterator to the end of the buffer data.
     **/
    //==========================================================================
    reverse_iterator        rend()         { return reverse_iterator(begin());        }
    const_reverse_iterator  rend()   const { return const_reverse_iterator(begin());  }

    //==========================================================================
    /**!
     * Return the number of elements accessible through the buffer.
     **/
    //==========================================================================
    size_type size()  const { return end_ - begin_; }

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
    reference operator[](difference_type const& i)
    {
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return begin_[i];
    }

    const_reference operator[](difference_type const& i) const
    {
      BOOST_ASSERT_MSG( (i >= lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= upper())
                      , "Position is out of buffer bounds"
                      );

      return begin_[i];
    }

    //==========================================================================
    /**!
     * Swap the contents of the buffer with another one.
     *
     * \param src buffer to swap with
     **/
    //==========================================================================
    void swap( pointer_buffer& src )
    {
      boost::swap(src.base_,base_);
      boost::swap(src.begin_,begin_);
      boost::swap(src.end_,end_);
    }

    //==========================================================================
    /**!
     * Change th ebase index of the buffer. This operation is doen in constant
     * time and don't trigger any reallocation.
     *
     * \param b A Boost.Fusion \c RandomAccessSequence containing the new base
     * index.
     **/
    //==========================================================================
    template<class Bases>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
    rebase(Bases const & b) { 

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_REBASE
      , (Bases)
      );

      begin_ += base_;
      base_ = boost::fusion::at_c<0>(b);
      begin_  -= base_;
      end_    -= base_;
    }

    //==========================================================================
    /**!
     * Change the size of the buffer. This operation is done in constant
     * time and don't trigger any reallocation.
     *
     * \param s A Boost.Fusion \c RandomAccessSequence containing the new size.
     **/
    //==========================================================================
    template<class Sizes>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Sizes> >::type
    resize(Sizes const& s) {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESIZE
      , (Sizes)
      );

      end_ = begin_+ boost::fusion::at_c<0>(s);
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
    template<class Bases,class Sizes>
    typename boost::enable_if_c < boost::fusion::traits::is_sequence<Sizes>::value
                                  &&
                                  boost::fusion::traits::is_sequence<Bases>::value
                                >::type
    restructure( Sizes const& s, Bases const& b)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Bases)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Sizes)
      );

      resize(s);
      rebase(b);
    }

    protected:
    difference_type base_;
    Type *begin_, *end_;
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   * \param a First \c pointer_buffer to swap
   * \param b Second \c pointer_buffer to swap
   **/
  //============================================================================
  template<class T>
  void swap( pointer_buffer<T>& a, pointer_buffer<T>& b )
  {
    a.swap(b);
  }  
} }
  
#endif
