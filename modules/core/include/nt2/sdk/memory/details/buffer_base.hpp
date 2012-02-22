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
    typedef typename Allocator::pointer           iterator;
    typedef typename Allocator::const_pointer     const_iterator;
    typedef typename Allocator::pointer           reverse_iterator;
    typedef typename Allocator::const_pointer     const_reverse_iterator;
    typedef typename Allocator::reference         reference;
    typedef typename Allocator::const_reference   const_reference;
    typedef typename Allocator::difference_type   size_type;
    typedef typename Allocator::difference_type   difference_type;

    buffer_data ( Allocator const& a )
                : parent_allocator(a), origin_(0), up_(BaseIndex-1) {}

    void allocate(size_type const& s)
    {
      if(s) origin_ = parent_allocator::allocate(s) - BaseIndex;
      else  origin_ = 0;
      clamp(s);
    }

    void deallocate()
    {
      if(origin_) parent_allocator::deallocate(origin_ + BaseIndex, size());
    }

    size_type resize(size_type const& s)
    {
      size_type nsz = realloc(s);
      clamp(s);
      return nsz;
    }

    void clamp(size_type const& s)
    {
      up_  = BaseIndex + s - 1;
    }

    size_type realloc(size_type const& s)
    {
      if(size() < s )
      {
        deallocate();
        origin_ = parent_allocator::allocate(s) - BaseIndex;
      }
      return s;
    }

    size_type       size()        const { return up_ - BaseIndex + 1; }
    size_type       inner_size()  const { return size();              }
    size_type       outer_size()  const { return 1;                   }

    difference_type lower()       const { return BaseIndex; }
    difference_type inner_lower() const { return BaseIndex; }
    difference_type outer_lower() const { return 1;         }

    difference_type upper()       const { return up_; }
    difference_type inner_upper() const { return up_; }
    difference_type outer_upper() const { return 1;   }

    iterator origin()  { return origin_;             }
    iterator begin()   { return origin_ + BaseIndex; }
    iterator end()     { return origin_ + up_ + 1;   }

    const_iterator origin()  const { return origin_;             }
    const_iterator begin()   const { return origin_ + BaseIndex; }
    const_iterator end()     const { return origin_ + up_ + 1;   }

    void swap(buffer_data& src)
    {
      boost::swap(origin_ , src.origin_ );
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

    iterator        origin_;
    difference_type up_;
  };
} } }

#endif
