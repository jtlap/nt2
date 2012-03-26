//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_DEBUG_HPP_INCLUDED
#define NT2_SDK_ERROR_DEBUG_HPP_INCLUDED

//==============================================================================
// NT2_RELEASE is triggerable by NDEBUG
//==============================================================================
#if defined(NDEBUG)
#define NT2_RELEASE
#define NT2_DISABLE_ASSERTS
#define BOOST_DISABLE_ASSERTS
#endif

//==============================================================================
// Ensure consistencies between assertion settings
//==============================================================================
#if defined(BOOST_DISABLE_ASSERTS) && !defined(NT2_DISABLE_ASSERTS)
#define NT2_DISABLE_ASSERTS
#endif

#if !defined(BOOST_DISABLE_ASSERTS) && defined(NT2_DISABLE_ASSERTS)
#define BOOST_DISABLE_ASSERTS
#endif

//==============================================================================
// NT2_DEBUG removes all NDEBUG influence
// Note that defining NT2_DEBUG overrride any Release mode settings
//==============================================================================
#if defined(NT2_DEBUG)
#undef NDEBUG
#undef NT2_DISABLE_ASSERTS
#undef BOOST_DISABLE_ASSERTS
#endif

#endif
