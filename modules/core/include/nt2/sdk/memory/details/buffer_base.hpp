/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Data holding class for memory buffer
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <boost/swap.hpp>

namespace nt2 { namespace memory { namespace details
{
  template<std::ptrdiff_t BaseIndex,class Allocator>
  struct buffer_data : private Allocator
  {
    typedef Allocator                             parent_allocator;
    typedef typename Allocator::value_type        value_type;
    typedef typename Allocator::pointer           pointer;
    typedef typename Allocator::const_pointer     const_pointer;
    typedef typename Allocator::pointer           iterator;
    typedef typename Allocator::const_pointer     const_iterator;
    typedef typename Allocator::pointer           reverse_iterator;
    typedef typename Allocator::const_pointer     const_reverse_iterator;
    typedef typename Allocator::reference         reference;
    typedef typename Allocator::const_reference   const_reference;
    typedef typename Allocator::difference_type   size_type;
    typedef typename Allocator::difference_type   difference_type;
    typedef typename Allocator::difference_type   index_type;
    typedef boost::mpl::integral_c<std::ptrdiff_t,BaseIndex>  base_index_type;

    buffer_data ( Allocator const& a )
                : parent_allocator(a), origin_(0), up_(BaseIndex-1) {}

    template<class Size> void allocate(Size const& s)
    {
      if(s)
      {
        origin_ = parent_allocator::allocate(s) - BaseIndex;
      }
      else
      {
        origin_ = 0;
      }

      up_ = BaseIndex + s - 1;
    }

    void deallocate()
    {
      if(origin_) parent_allocator::deallocate(origin_ + BaseIndex, size());
    }

    template<class Size> void resize(Size const& s)
    {
      realloc(s);
      clamp(s);
    }

    template<class Size> void clamp(Size const& s)
    {
      up_  = BaseIndex + s - 1;
    }
    
    template<class Size> void realloc(Size const& s)
    {
      if(size() < s )
      {
        deallocate();
        origin_ = parent_allocator::allocate(s) - BaseIndex;
      }
    }
    
    size_type       size()  const { return up_ - BaseIndex + 1; }
    difference_type lower() const { return BaseIndex;           }
    difference_type upper() const { return up_;                 }

    pointer origin()  { return origin_;             }
    pointer begin()   { return origin_ + BaseIndex; }
    pointer end()     { return origin_ + up_ + 1;   }

    const_pointer origin()  const { return origin_;             }
    const_pointer begin()   const { return origin_ + BaseIndex; }
    const_pointer end()     const { return origin_ + up_ + 1;   }

    template<std::ptrdiff_t B2>
    void swap(buffer_data<B2,Allocator>& src)
    {
      pointer tmp     = origin_;
      size_type tmps  = size();
      
      origin_     = src.origin_ + B2        - BaseIndex;
      clamp(src.size());

      src.origin_ = tmp         + BaseIndex - B2;  
      src.clamp(tmps);
    }

    parent_allocator& allocator()
    {
      return static_cast<parent_allocator&>(*this);
    }

    parent_allocator const& allocator() const
    {
      return static_cast<parent_allocator const&>(*this);
    }

    pointer         origin_;
    difference_type up_;    
  };
} } }

#endif
