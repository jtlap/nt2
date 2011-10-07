//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_IS_BLOCK_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_IS_BLOCK_HPP_INCLUDED

#include <boost/type_traits/is_arithmetic.hpp>

namespace nt2 { namespace details
{
  template<class T, class Enable = void>
  struct is_block
    : boost::is_arithmetic<T>
  {
  };
}

namespace container
{
  template<class T>
  struct is_block
    : details::is_block<T>
  {
  };
  
  template<class T>
  struct is_block<T&> : is_block<T> {};
  
  template<class T>
  struct is_block<T const> : is_block<T> {};
    
} }

#endif
