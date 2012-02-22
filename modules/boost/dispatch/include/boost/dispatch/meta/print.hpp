//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PRINT_HPP_INCLUDED
#define BOOST_DISPATCH_META_PRINT_HPP_INCLUDED

#include <boost/config.hpp>

/*!
 * \file
 * \brief Defines and implements the \ref boost::dispatch::meta::print \metafunction
 */

#if defined(__GNUC__) && !defined(BOOST_CLANG) && !defined(BOOST_INTEL) && !defined(__CUDACC__)

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct print
  {
    typedef T type;
    unsigned : 80;
  };
} } }

#else

#include <boost/mpl/print.hpp>
namespace boost { namespace dispatch { namespace meta
{
  using boost::mpl::print;
} } }

#endif

#endif

