//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_LINEAR_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_LINEAR_BUFFER_HPP

//==============================================================================
/**
  * \file 
  * \brief Defines and implements the \c nt2::memory::linear_buffer class
  **/
//==============================================================================
#include <nt2/sdk/memory/slice.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Linearly allocated memory buffer.
    *
    * linear_buffer models the NT2 Buffer concept by handling a segment of memory
    * defined by a set of base indices, sizes and padding strategy. This segment
    * is then accessible through the Buffer interface.
    *
    * linear_buffer uses a classical linear allocation scheme and its accesses 
    * are access through a polynomial indexing.
    *
    * \tparam Dimensions  Number of dimensions stored in this Buffer
    * \tparam Type        Type of values stored in this Buffer
    * \tparam Padding     Padding strategy for this Buffer
    * \tparam Allocator   Memory allocator used by this Buffer
   **/
  //============================================================================
  template< unsigned Dimensions
          , typename Type, typename Padding, typename Allocator          
          >
  struct linear_buffer
  {  
    typedef typename Allocator::template rebind<Type>::other  allocator;

    //==========================================================================
    /** Type of the value stored in current buffer                            */
    //==========================================================================
    typedef typename allocator::value_type                    value_type;

    //==========================================================================
    /** Type of the pointer giving access to the stored values                */
    //==========================================================================
    typedef typename allocator::pointer                       pointer;

    //==========================================================================
    /** Type of the pointer giving access to the stored values as constants   */
    //==========================================================================
    typedef typename allocator::const_pointer                 const_pointer;

    //==========================================================================
    /** Type of reference to a value                                          */
    //==========================================================================
    typedef typename allocator::reference                     reference;

    //==========================================================================
    /** Type of reference to a constant value                                 */
    //==========================================================================
    typedef typename allocator::const_reference               const_reference;

    //==========================================================================
    /** Type representing an amount of values                                 */
    //==========================================================================
    typedef typename allocator::size_type                     size_type;

    //==========================================================================
    /** Type representing an offset between values                            */
    //==========================================================================
    typedef typename allocator::difference_type               difference_type;

    //==========================================================================
    /** Type of the pointer to buffer storage area                            */
    //==========================================================================
    typedef value_type*                                       data_type;  

    //==========================================================================
    /**
      * Constructs a linear buffer by allocating memory for its own ownership.
      *
      * \param szs FusionRandomAccessSequence containing the dimensions of the
      *            buffer 
      * \param bss FusionRandomAccessSequence containing the base indices of the
      *            buffer
      * \param p   Padding strategy of the buffer
      * \param a   Allocator instance used by the buffer
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    linear_buffer ( Sizes const&      szs
                  , Bases const&      /*bss*/
                  , Padding const&    p
                  , Allocator const&  a = Allocator() 
                  )
    : alloc_(a), begin_(0), shared_(false)
    {
      size_type numel = slice<1>(szs,p);
      if(numel != 0) begin_ = alloc_.allocate( numel );
      end_ = begin_ + numel;
    }
    
    //==========================================================================
    /**
      * Constructs a linear buffer from an existing data block without any transfer
      * of ownership. On destruction, said data are not desallocated.
      *
      * \param szs FusionRandomAccessSequence containing the dimensions of the
      *            buffer 
      * \param bss FusionRandomAccessSequence containing the base indices of the
      *            buffer
      * \param p   Padding strategy of the buffer
      * \param shared Memory block to share
      * \param a   Allocator instance used by the buffer
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    linear_buffer ( Sizes const&      szs
                  , Bases const&      /* bss */
                  , Padding const&    p
                  , value_type*       shared
                  , Allocator const&  a = Allocator() 
                  )
    : begin_(shared), end_(0), shared_(true), alloc_(a)
    {
      if(begin_) end_ = begin_ + slice<1>(szs,p);
    }    
    
    //==========================================================================
    /**
      * Destructs a linear_buffer by deallocating its data segment if it actually
      * owns it.
     **/
    //==========================================================================
    ~linear_buffer() 
    { 
      data_type ptr = begin();
      if(!shared_ && ptr) alloc_.deallocate(ptr, end_ - begin_ ); 
    }

    //==========================================================================
    /**
      * Give access to the beginning of the values stored in the buffer.
      * begin() and end() are both returning un-biased pointer, making them
      * suitable for a classical, STL like treatment.
      *
      * \return A pointer pointing to the beginning of the buffer segment
      * holding values.
     **/
    //==========================================================================
    pointer       begin()       { return begin_; }
    const_pointer begin() const { return begin_; }
    
    //==========================================================================
    /**
      * Give access to the end of the values stored in the buffer.
      * begin() and end() are both returning un-biased pointer, making them
      * suitable for a classical, STL like treatment.
      *
      * \return A pointer pointing past the last element of the buffer segment
      * holding values.
     **/
    //==========================================================================
    pointer       end()         { return end_; }
    const_pointer end() const   { return end_; }

    private:
    data_type begin_, end_;
    bool      shared_;
    Allocator alloc_;
  };
} }

#endif 
