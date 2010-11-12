/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_BUFFER_IMPL_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_BUFFER_IMPL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Raw structure to handle exception safe buffer allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/swap.hpp>
#include <nt2/sdk/memory/align_on.hpp>

namespace nt2 { namespace details
{
  ////////////////////////////////////////////////////////////////////////////
  // Implementation structure
  ////////////////////////////////////////////////////////////////////////////
  template<class Type, class Allocator>
  struct buffer_impl : Allocator
  {
    typedef Allocator                       base;
    typedef typename base::pointer          pointer;
    typedef typename base::difference_type  difference_type;
    typedef typename base::size_type        size_type;

    pointer origin_, begin_, end_;

    buffer_impl(base const& a)  : base(a)
    {
      origin_ = begin_ = end_ = 0;
    }

    void allocate(difference_type b, size_type s)
    {
      origin_       = base::allocate(s);
      as_base(s, b);
    }

    void resize(size_type s)
    {
      difference_type b = origin_ - begin_;
      size_type osz     = end_    - begin_;
      origin_           = base::resize(origin_,s,osz);
      as_base(s, b);
    }

    void rebase(difference_type b)
    {
      as_base(end_ - begin_, b);
    }

    void as_base(size_type size, difference_type lower)
    {
      begin_  = origin_ - lower;
      end_    = begin_  + size;
    }

    void swap(buffer_impl& src)
    {
      boost::swap(origin_     , src.origin_     );
      boost::swap(begin_      , src.begin_      );
      boost::swap(end_        , src.end_        );
      boost::swap(allocator() , src.allocator() );
    }

    base& allocator() { return static_cast<base&>(*this); }
  };
} }

#endif
