//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_MAKE_BLOCK_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_MAKE_BLOCK_HPP_INCLUDED

#include <boost/dispatch/meta/value_of.hpp>
#include <boost/array.hpp>

template<class T>
struct block
{
    block() : data(new T[4096]) {}
    ~block() { delete[] data; }

  T* data;
};

namespace nt2 { namespace container
{
template<class T, class S>
struct make_block
{
  typedef ::block<T> type;
};
} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< ::block<T> >
  {
    typedef T type;
  };
} } }

#endif
