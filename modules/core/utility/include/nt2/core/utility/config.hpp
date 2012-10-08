//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_CONFIG_HPP_INCLUDED
#define NT2_CORE_UTILITY_CONFIG_HPP_INCLUDED

#include <boost/config.hpp>

#ifdef NT2_CORE_UTILITY_DYN_LINK
#  ifdef NT2_CORE_UTILITY_SOURCE
#    define NT2_CORE_UTILITY_DECL BOOST_SYMBOL_EXPORT
#  else
#    define NT2_CORE_UTILITY_DECL BOOST_SYMBOL_IMPORT
#  endif
#else
#  define NT2_CORE_UTILITY_DECL
#endif

#endif
