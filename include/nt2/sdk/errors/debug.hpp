/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_ERRORS_DEBUG_HPP_INCLUDED
#define NT2_SDK_ERRORS_DEBUG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Define/Undefine macros depending on compilation mode
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/errors/warning.hpp>

#if defined(NT2_DEBUG) && defined(NT2_RELEASE)
#undef NT2_DEBUG
NT2_WARNING(Compiling in both Debug and Release - Forcing Release Mode)
#endif

#if defined(NT2_DEBUG)
#undef NDEBUG
#undef NT2_DISABLE_ASSERTS
#undef BOOST_DISABLE_ASSERTS
NT2_WARNING(Compiling with Debug Informations)
#endif

#if defined(NT2_RELEASE)
#define NDEBUG
#define NT2_DISABLE_ASSERTS
#define BOOST_DISABLE_ASSERTS
NT2_WARNING(Compiling In Release Configuration)
#endif

#if defined(BOOST_DISABLE_ASSERTS) && !defined(NT2_DISABLE_ASSERTS)
#define NT2_DISABLE_ASSERTS
#endif

#if !defined(BOOST_DISABLE_ASSERTS) && defined(NT2_DISABLE_ASSERTS)
#define BOOST_DISABLE_ASSERTS
#endif

#endif
