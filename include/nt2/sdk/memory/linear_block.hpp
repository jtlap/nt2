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
    // Data related Type derived from Allocator
    ////////////////////////////////////////////////////////////////////////////
    typedef typename Allocator::template rebind<Type>::other  allocator_type;
    typedef typename allocator_type::value_type               value_type;
    typedef typename allocator_type::reference                reference;
    typedef typename allocator_type::const_reference          const_reference;
    typedef typename allocator_type::size_type                size_type;
    typedef typename allocator_type::difference_type          difference_type;

    ////////////////////////////////////////////////////////////////////////////
    // Type related to internal buffer
    // A linear_block holds a single [0,slice<1>(size)[ buffer
    ////////////////////////////////////////////////////////////////////////////
    typedef BOOST_TYPEOF_TPL(( slice<Padding,1>(Sizes()) )) size_value_type;
    typedef boost::mpl::int_<0>                             base_value_type;


    typedef buffer<Type, boost::mpl::int_<0>, sizes_type, Allocator> data_type;

    private:
    Bases                                                     bases_;
    Sizes                                                     sizes_;
    buffer<Type, boost::mpl::int_<0>, sizes_type, Allocator>  data_;
  };
} }

#endif
