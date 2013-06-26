//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_ASSIGN_SWAP_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_ASSIGN_SWAP_HPP_INCLUDED

#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace container
{
  template<class T, long Arity = T::proto_arity_c>
  struct is_container_terminal
       : boost::mpl::false_
  {
  };

  template<class T>
  struct is_container_terminal<T, 0l>
       : meta::is_container<typename T::proto_child0>
  {
  };

  template<class A0, class A1>
  typename boost::enable_if<
    boost::mpl::and_< is_container_terminal<A0>
                    , is_container_terminal<A1>
                    >
  >::type
  assign_swap(A0& a0, A1& a1)
  {
    memory::swap(boost::proto::value(a0), boost::proto::value(a1));
  }

  template<class A0, class A1>
  typename boost::disable_if<
    boost::mpl::and_< is_container_terminal<A0>
                    , is_container_terminal<A1>
                    >
  >::type
  assign_swap(A0& a0, A1& a1)
  {
    a0 = a1;
  }
} }

#endif
