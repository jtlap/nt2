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
    
    //==========================================================================
    /**!
     *
     *
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

    buffer( buffer const& src )
          : parent_data(src.allocator())
    {
      parent_data::allocate( src.lower(), src.size() );
      std::copy(src.begin(),src.end(),begin());
    }

    //==========================================================================
    // Basic destructor - nothing fancy here \_/°>
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
        // Just restructuree and copy
        parent_data::restructure(src.size(),src.lower());
        std::copy(src.begin(),src.end(),begin());
      }
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::begin;
    using parent_data::end;
    
    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::size;

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////
    reference operator[](difference_type const& i)
    {                          
      BOOST_ASSERT_MSG(   (i >= parent_data::lower())
                      &&  (i <= parent_data::upper())
                      ,   "Position is out of buffer bounds"
                      );
                      
      return parent_data::begin_[i];
    }

    const_reference operator[](difference_type const& i) const
    {                          
      BOOST_ASSERT_MSG(   (i >= parent_data::lower())
                      &&  (i <= parent_data::upper())
                      ,   "Position is out of buffer bounds"
                      );
                      
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
    void rebase(difference_type const& bs)
    {
      parent_data::rebase( bs );
    }

    void resize(size_type const& sz)
    {
      parent_data::resize( sz );
    }

    void restructure( size_type const& s, difference_type const& b )
    {
      resize(s);
      rebase(b);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::allocator;
    using parent_data::lower;
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
