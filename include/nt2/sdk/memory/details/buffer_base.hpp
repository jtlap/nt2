/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Data holding class for memory buffer
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <boost/swap.hpp>

namespace nt2 { namespace details
{
  template<class Pointer> class buffer_data
  {
    public:
    buffer_data() : origin_(0), begin_(0), end_(0) {}

    template<class Size, class Diff, class Allocator>
    void allocate(Diff b, Size s, Allocator& alloc)
    {
      if(s)
      {
        origin_ = alloc.allocate(s);
        clamp(s, b);
      }
      else
      {
        origin_ = begin_ = end_ = 0;
      }
    }

    template<class Allocator> void deallocate(Allocator& alloc)
    {
      if(origin_) alloc.deallocate(origin_,end_ - begin_);
    }

    template<class Size, class Allocator>
    void resize(Size s, Allocator& alloc)
    {
      if(!origin_)
      {
        origin_ = alloc.allocate(s);
        clamp(s, 0);
      }
      else
      {
        origin_ = alloc.resize(origin_,s,end_ - begin_);
        clamp(s, origin_ - begin_);
      }
    }

    template<class Diff> void rebase(Diff b) { clamp(size(), b); }

    template<class Size, class Diff> void clamp(Size size, Diff lower)
    {
      begin_  = origin_ - lower;
      end_    = begin_  + size;
    }

    size_t    size()  const { return end_    - begin_;      }
    ptrdiff_t lower() const { return origin_ - begin_;      }
    ptrdiff_t upper() const { return size()  - 1 + lower(); }

    Pointer begin() { return origin_;           }
    Pointer end()   { return origin_ + size();  }

    Pointer first() { return begin_;           }
    Pointer last()  { return begin_ + size();  }

    Pointer const begin() const { return origin_;           }
    Pointer const end()   const { return origin_ + size();  }

    Pointer const first() const { return begin_;           }
    Pointer const last()  const { return begin_ + size();  }

    void swap(buffer_data& src)
    {
      boost::swap(origin_, src.origin_ );
      boost::swap(begin_ , src.begin_  );
      boost::swap(end_   , src.end_    );
    }

    Pointer origin_, begin_, end_;
  };
} }

#endif
