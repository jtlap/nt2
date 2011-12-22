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
  template<class Allocator> struct buffer_data : private Allocator
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

    buffer_data(Allocator const& a) : parent_allocator(a)
                                    , origin_(0), low_(0), up_(-1) {}

    template<class Size, class Diff>
    void allocate(Diff const& b, Size const& s)
    {
      if(s)
      {
        low_  = b;
        origin_ = parent_allocator::allocate(s) - low_;
      }
      else
      {
        origin_ = 0;
        low_    = 0;
      }

      up_ = low_ + s - 1;
    }

    void deallocate()
    {
      if(origin_) parent_allocator::deallocate(origin_ + low_, size());
    }

    template<class Size,class Base>
    void restructure(Size const& s, Base const& b)
    {
      realloc(s);
      clamp(b,s);
    }

    template<class Size> void resize(Size const& s)
    {
      realloc(s);
      up_  = low_ + s - 1;
    }

    template<class Diff> void rebase(Diff const& b)
    {
      clamp(b,size());
    }

    template<class Size> void realloc(Size const& s)
    {
      if(size() < s )
      {
        deallocate();
        origin_ = parent_allocator::allocate(s) - low_;
      }
    }
    
    template<class Diff,class Size>
    void clamp(Diff const& b,Size const& s)
    {
      up_     = s - 1;
      origin_ = origin_ + low_ - b;
      low_    = b;
      up_    += low_;
    }
    
    size_type       size()  const { return up_ - low_ + 1;  }
    difference_type lower() const { return low_;            }
    difference_type upper() const { return up_;             }

    pointer origin()  { return origin_;           }
    pointer begin()   { return origin_ + low_;    }
    pointer end()     { return origin_ + up_ + 1; }

    const_pointer origin()  const { return origin_;           }
    const_pointer begin()   const { return origin_ + low_;    }
    const_pointer end()     const { return origin_ + up_ + 1; }

    void swap(buffer_data& src)
    {
      boost::swap(origin_ , src.origin_ );
      boost::swap(low_    , src.low_    );
      boost::swap(up_     , src.up_     );
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
    difference_type low_, up_;    
  };
} } }

#endif
