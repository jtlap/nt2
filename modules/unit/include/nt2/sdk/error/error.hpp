//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ERROR_HPP_INCLUDED
#define NT2_SDK_ERROR_ERROR_HPP_INCLUDED

#include <nt2/sdk/error/details/error.hpp>
#include <boost/config.hpp>

#if defined(NT2_DISABLE_ERROR) || defined(BOOST_NO_EXCEPTIONS)
#define NT2_NO_EXCEPTIONS
#endif

#if !defined(NT2_NO_EXCEPTIONS)
#include <nt2/sdk/error/details/exception.hpp>
#endif

#endif
