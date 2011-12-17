/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_BUFFER_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_BUFFER_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Data holding class for memory buffer
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <boost/swap.hpp>

namespace nt2 { namespace memory { namespace details
{
  template<class Allocator>
  struct buffer_data : private Allocator
  {
    ////////////////////////////////////////////////////////////////////////////
    // Forwarded types
    ////////////////////////////////////////////////////////////////////////////
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
    typedef typename Allocator::size_type         size_type;
    typedef typename Allocator::difference_type   difference_type;
    typedef typename Allocator::difference_type   index_type;

    buffer_data(Allocator const& a) : parent_allocator(a)
                                    , origin_(0), begin_(0), end_(0) {}

    template<class Size, class Diff>
    void allocate(Diff const& b, Size const& s)
    {
      if(s)
      {
        origin_ = parent_allocator::allocate(s);
        clamp(s, b);
      }
      else
      {
        origin_ = begin_ = end_ = 0;
      }
    }

    void deallocate()
    {
      if(origin_) parent_allocator::deallocate(origin_,end_ - begin_);
    }

    template<class Size,class Base>
    void restructure(Size const& s, Base const& b)
    {
      difference_type os = size();

      if(os < s )
      {
        deallocate();
        origin_ = parent_allocator::allocate(s);
      }
      
      clamp(s,b);
    }

    template<class Size> void resize(Size const& s)
    {
      restructure(s,lower());
    }

    template<class Diff> void rebase(Diff const& b) { clamp(size(), b); }

    template<class Size, class Diff>
    void clamp(Size const& size, Diff const& lower)
    {
      begin_  = origin_ - lower;
      end_    = begin_  + size;
    }

    size_type       size()  const { return end_    - begin_;      }
    difference_type lower() const { return origin_ - begin_;      }
    difference_type upper() const { return size()  - 1 + lower(); }

    pointer begin() { return origin_;           }
    pointer end()   { return origin_ + size();  }

    pointer const begin() const { return origin_;           }
    pointer const end()   const { return origin_ + size();  }

    void swap(buffer_data& src)
    {
      boost::swap(origin_, src.origin_ );
      boost::swap(begin_ , src.begin_  );
      boost::swap(end_   , src.end_    );
    }

    parent_allocator& allocator()
    {
      return static_cast<parent_allocator&>(*this);
    }

    parent_allocator const& allocator() const
    {
      return static_cast<parent_allocator const&>(*this);
    }

    pointer origin_, begin_, end_;
  };
} } }

#endif
