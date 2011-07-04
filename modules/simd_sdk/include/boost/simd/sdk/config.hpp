/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main config header
// Documentation: http://nt2.lri.fr/sdk/config.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD configuration files
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/os.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config/attributes.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>

////////////////////////////////////////////////////////////////////////////////
// External BOOST_SIMD configuration files
////////////////////////////////////////////////////////////////////////////////
//#include <boost/simd/extensions/sdk/config.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build a nt2 versioning symbol for binary conformance
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/config/version.hpp>

#endif
