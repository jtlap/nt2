//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_IS_STATICALLY_SIZED_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_IS_STATICALLY_SIZED_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/core/functions/size.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check if a given Expression type has a size known at compile time
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Expression>
  struct is_statically_sized
   : boost::mpl::bool_< boost::dispatch::meta::
                        call<tag::extent_(Expression)>::type::static_status
                      >
  {};
} }

#endif
