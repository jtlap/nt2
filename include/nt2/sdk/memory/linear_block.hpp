/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED
#define NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Linear allocation memory block
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/buffer.hpp>

namespace nt2 { namespace memory
{
  template< int Dims
          , class Type
          , class Bases, class Sizes
          , class Padding
          , class Allocator
          >
  class linear_block
  {
    public:

    ////////////////////////////////////////////////////////////////////////////
    // A linear block allocate everything as a single buffer of proper size
    ////////////////////////////////////////////////////////////////////////////
    typedef BOOST_TYPEOF_TPL(( slice<Padding,1>(Sizes()) )) sizes_type;

    private:
    Bases                                                     bases_;
    Sizes                                                     sizes_;
    buffer<Type, boost::mpl::int_<0>, sizes_type, Allocator>  data_;
  };
} }

#endif
