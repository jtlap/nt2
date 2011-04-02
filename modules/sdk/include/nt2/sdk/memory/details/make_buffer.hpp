/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_MAKE_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_MAKE_BUFFER_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Build a buffer type suitable for NRC like array
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/at.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Build a buffer class from a block specs.
  // Note that Storage has been already applied to Bases/Sizes before call.
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , std::size_t Dimensions, class Bases, class Sizes, class Padding
          , class Allocator
          >
  struct make_buffer
  {
    ////////////////////////////////////////////////////////////////////////////
    // Reuse the make_buffer of one less Dimensions to compute current types
    ////////////////////////////////////////////////////////////////////////////
    typedef make_buffer<Type,Dimensions-1,Bases,Sizes,Padding,Allocator>  prev;

    ////////////////////////////////////////////////////////////////////////////
    // Add one pointer to the previous value_type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename  boost
                    ::add_pointer<typename prev::value_type>::type  value_type;

    ////////////////////////////////////////////////////////////////////////////
    // Rebind Allocator to current value_type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename  Allocator
        ::template rebind<value_type>::other        allocator_type;

    ////////////////////////////////////////////////////////////////////////////
    // Extract current Base and Size types
    ////////////////////////////////////////////////////////////////////////////
    typedef typename boost::mpl::at_c<Bases,Dimensions-1>::type      base_type;

    ////////////////////////////////////////////////////////////////////////////
    // Extract current Size type and apply potential static padding
    ////////////////////////////////////////////////////////////////////////////
    struct size_type_helper
    {
      static Sizes& s; static Padding& p;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, slice<Dimensions>(s,p))
      typedef typename nested::type         type;
    };

    typedef typename size_type_helper::type size_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build final buffer type
    ////////////////////////////////////////////////////////////////////////////
    typedef memory::buffer<value_type,base_type,size_type,allocator_type> type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a buffer class from a block specs of Dimensions 1
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , class Bases, class Sizes, class Padding
          , class Allocator
          >
  struct make_buffer<Type,1,Bases,Sizes,Padding,Allocator>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Type is the value_type
    ////////////////////////////////////////////////////////////////////////////
    typedef Type                                              value_type;

    ////////////////////////////////////////////////////////////////////////////
    // Rebind Allocator to current value_type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename  Allocator
        ::template rebind<value_type>::other      allocator_type;

    ////////////////////////////////////////////////////////////////////////////
    // Extract current Base type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename boost::mpl::at_c<Bases,0>::type          base_type;

    ////////////////////////////////////////////////////////////////////////////
    // Extract current Size type and apply potential static padding
    ////////////////////////////////////////////////////////////////////////////
    struct size_type_helper
    {
      static Sizes& s; static Padding& p;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, slice<1>(s,p))
      typedef typename nested::type         type;
    };

    typedef typename size_type_helper::type size_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build final buffer type
    ////////////////////////////////////////////////////////////////////////////
    typedef memory::buffer<value_type,base_type,size_type,allocator_type>  type;
  };
} }

namespace nt2 { namespace meta
{
  template< class Type
          , std::size_t Dimensions, class Bases, class Sizes, class Padding
          , class Allocator
          >
  struct make_buffers
  {
    ////////////////////////////////////////////////////////////////////////////
    // Build current buffer type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename details
    ::make_buffer < Type,Dimensions,Bases
      , Sizes,Padding,Allocator
      >::type                    buffer_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build previous buffer types sequence
    ////////////////////////////////////////////////////////////////////////////
    typedef typename make_buffers < Type,Dimensions-1,Bases
          , Sizes,Padding,Allocator
          >::type          prev_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build the updated buffer types sequence
    ////////////////////////////////////////////////////////////////////////////
    typedef typename boost::mpl::push_back<prev_type,buffer_type>::type type;
  };

  template< class Type
          , class Bases, class Sizes, class Padding
          , class Allocator
          >
  struct  make_buffers<Type,1,Bases,Sizes,Padding,Allocator>
  {
    typedef typename details
    ::make_buffer<Type,1,Bases,Sizes,Padding,Allocator>::type buffer_type;

    typedef boost::fusion::vector<buffer_type> type;
  };
} }
#endif
