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
#include <boost/mpl/size.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <nt2/core/container/memory/adapted/buffer.hpp>
#include <nt2/core/container/memory/details/buffer_base.hpp>

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
  template<class Type, class Allocator>
  class buffer
      : private
        details::buffer_data<typename Allocator::template rebind<Type>::other>
  {
    public:
    //==========================================================================
    // Inheritance type definition
    //==========================================================================
    typedef typename Allocator::template rebind<Type>::other  allocator_type;
    typedef details::buffer_data<allocator_type>              parent_data;

    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef typename parent_data::value_type              value_type;
    typedef typename parent_data::pointer                 pointer;
    typedef typename parent_data::const_pointer           const_pointer;
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
    template<typename Sizes, typename Bases>
    buffer( Sizes           const& sz
          , Bases           const& bs
          , allocator_type  const& alloc = allocator_type()
          , typename  boost::enable_if<
                      boost::fusion::traits::is_sequence<Sizes>
                      >::type* = 0
          , typename  boost::enable_if<
                      boost::fusion::traits::is_sequence<Bases>
                      >::type* = 0
          )
    : parent_data(alloc)          
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      parent_data::allocate ( boost::fusion::at_c<0>(bs)
                            , boost::fusion::at_c<0>(sz)
                            );
    }

    //==========================================================================
    /**!
     * Constructs a buffer from an other buffer of type \c Type, a dimension set
     * and a base index sets.
     *
     * \param src A buffer of \c Type value.
     * \param sz  A Boost.Fusion \c RandomAccessSequence containing the number
     * of elements of the buffer.
     * \param bs  A Boost.Fusion \c RandomAccessSequence containing the base
     * index of the buffer.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    buffer( buffer          const& src
          , Sizes           const& sz
          , Bases           const& bs
          , allocator_type  const& alloc = allocator_type()
          , typename  boost::enable_if<
                      boost::fusion::traits::is_sequence<Sizes>
                      >::type* = 0
          , typename  boost::enable_if<
                      boost::fusion::traits::is_sequence<Bases>
                      >::type* = 0
          )
    : parent_data(alloc) 
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      this->copy(src, boost::fusion::at_c<0>(bs), boost::fusion::at_c<0>(sz));
    }
    //==========================================================================
    /**!
     * Copy constructor for buffer. 
     *
     * \param src pointer_buffer to copy
     **/
    //==========================================================================
    buffer( buffer const& src )
          : parent_data(src.allocator())
    {
      this->copy( src, src.size(),src.lower());
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
        this->copy( src, src.size(),src.lower());
      }
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
    using parent_data::end;
    
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
     * \param i Index of the element to retrieve. Note that \c i should be no
     * lesser than lower() nor bigger than upper() to be valid.
     **/    
    //==========================================================================
    reference operator[](difference_type const& i)
    {
      BOOST_ASSERT_MSG( (i >= parent_data::lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= parent_data::upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return parent_data::begin_[i];
    }

    const_reference operator[](difference_type const& i) const
    {                          
      BOOST_ASSERT_MSG( (i >= parent_data::lower())
                      , "Position is below buffer bounds"
                      );
                      
      BOOST_ASSERT_MSG( (i <= parent_data::upper())
                      , "Position is out of buffer bounds"
                      );
                      
      return parent_data::begin_[i];                      
    }
    
    //==========================================================================
    /**!
     * Swap the contents of the buffer with another one.
     *
     * \param src buffer to swap with
     **/
    //==========================================================================
    void swap( buffer& src )
    {
      parent_data::swap(src);
      boost::swap(allocator(),src.allocator());
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
    template<class Bases>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
    rebase(Bases const& bs)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_REBASE
      , (Bases)
      );

      parent_data::rebase( boost::fusion::at_c<0>(bs) );
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
    resize(Sizes const& sz)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_RESIZE
      , (Sizes)
      );
      
      parent_data::resize( boost::fusion::at_c<0>(sz) );
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
    restructure(Sizes const& sz, Bases const& bs)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_RESTRUCTURE
      , (Bases)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_RESTRUCTURE
      , (Sizes)
      );

      parent_data::restructure(sz,bs);
    }

    protected:

    using parent_data::allocator;

    void copy( buffer const& src, size_type const& s, difference_type const& b )
    {
      parent_data::restructure(s,b);
      std::copy(src.begin(),src.end(),begin());
    }
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   **/
  //============================================================================
  template<class T, class A>
  void swap( buffer<T,A>& a, buffer<T,A>& b )
  {
    a.swap(b);
  }
} } 

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
