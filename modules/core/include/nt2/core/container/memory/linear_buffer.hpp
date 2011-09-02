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

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
   * \brief Linearly allocated memory buffer
   **/
  //============================================================================
  template< unsigned Dimensions
          , typename Type
          , typename Padding
          , typename Allocator          
          >
  struct linear_buffer
  {  
    typedef typename Allocator::template rebind<Type>::other  allocator;
    typedef typename allocator::value_type                    value_type;
    typedef typename allocator::pointer                       pointer;
    typedef typename allocator::const_pointer                 const_pointer;
    typedef typename allocator::reference                     reference;
    typedef typename allocator::const_reference               const_reference;
    typedef typename allocator::size_type                     size_type;
    typedef typename allocator::difference_type               difference_type;
    typedef value_type*                                       data_type;  

    //==========================================================================
    /**
     * Constructe a linear buffer from a set of dimensions, a padding strategy
     * and an allocator.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    linear_buffer ( Sizes const&      szs
                  , Bases const&      // bases are not needed in linear mode
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
     * Constructs a linear buffer from a set of dimensions, a padding strategy
     * , an allocator and an existing data block that will be shared. The original
     * data block ownership is not transfered.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> 
    linear_buffer ( Sizes const&      szs
                  , Bases const&      // bases are not needed in linear mode
                  , Padding const&    p
                  , value_type*       shared
                  , Allocator const&  a = Allocator() 
                  )
    : alloc_(a), begin_(shared), shared_(true)
    {
      size_type numel = slice<1>(szs,p);
      end_ = begin_ + numel;
    }    
    
    ~linear_buffer() 
    { 
      if(!shared_ && begin_) alloc_.deallocate(begin_,end_ - begin_); 
    }

    data_type     data() const  { return begin_; }
    
    pointer       begin()       { return begin_; }
    const_pointer begin() const { return begin_; }
    
    pointer       end()         { return end_; }
    const_pointer end() const   { return end_; }

    private:
    Allocator   alloc_;
    data_type   begin_, end_;
    bool        shared_;
  };
} }

#endif 
