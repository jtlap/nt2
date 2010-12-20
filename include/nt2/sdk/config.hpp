/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_HPP_INCLUDED
#define NT2_SDK_CONFIG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main config header
// Documentation: http://nt2.lri.fr/sdk/config.html
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NT2 configuration files
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/os.hpp>
#include <nt2/sdk/config/arch.hpp>
#include <nt2/sdk/config/compiler.hpp>
#include <nt2/sdk/config/attributes.hpp>
#include <nt2/sdk/config/type_lists.hpp>

////////////////////////////////////////////////////////////////////////////////
// External NT2 configuration files
////////////////////////////////////////////////////////////////////////////////
//#include <nt2/extensions/sdk/config.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build a nt2 versioning symbol for binary conformance
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/version.hpp>

#endif
