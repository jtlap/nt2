/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_PARAMETERS_HPP_INCLUDED

#if defined(NT2_CONFIG_ALIGNMENT) && !defined(BOOST_SIMD_CONFIG_ALIGNMENT)
#define BOOST_SIMD_CONFIG_ALIGNMENT NT2_CONFIG_ALIGNMENT
#endif
#ifdef NT2_CONFIG_ALIGNMENT
#undef NT2_CONFIG_ALIGNMENT
#endif

#include <boost/simd/sdk/memory/parameters.hpp>
#define NT2_CONFIG_ALIGNMENT BOOST_SIMD_CONFIG_ALIGNMENT

#endif
