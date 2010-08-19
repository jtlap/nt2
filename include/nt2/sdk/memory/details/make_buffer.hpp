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
// Build a buffer suitable for NRC like array
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/at.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace nt2 { namespace details
{
  template<int N, class T, class B, class S, class P, class A>
  struct make_buffer
  {
    typedef make_buffer<N-1,T,B,S,P,A>                                   prev;
    typedef typename  boost
                    ::add_pointer<typename prev::value_type>::type value_type;
    typedef typename A::template rebind<value_type>::other     allocator_type;
    typedef typename boost::mpl::at_c<B,N-1>::type                   base_type;
    typedef typename boost::mpl::at_c<S,N-1>::type                   size_type;
    typedef memory::buffer<value_type,base_type,size_type,allocator_type> type;
  };

  template<class T, class B, class S, class P, class A>
  struct make_buffer<1,T,B,S,P,A>
  {
    typedef T                                                     value_type;
    typedef typename boost::mpl::at_c<B,0>::type                  base_type;
    typedef typename boost::result_of<typename P::size(S)>::type  size_type;
    typedef memory::buffer<value_type,base_type,size_type,A>      type;
  };
} }

#endif
