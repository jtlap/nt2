/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_ARCH_HPP_INCLUDED
#define NT2_SDK_CONFIG_ARCH_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Architecture configuration headers
// Defines architecture symbols for architecture related variation point.
// Documentation: http://nt2.lri.fr/sdk/config/architecture.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/config/details/boost.hpp>

////////////////////////////////////////////////////////////////////////////////
// Include custom specific architectures from extensions folders
////////////////////////////////////////////////////////////////////////////////
#include <nt2/extension/sdk/config/arch.hpp>
#include <nt2/sdk/config/arch/powerpc.hpp>
#include <nt2/sdk/config/arch/x86.hpp>
#include <nt2/sdk/config/arch/ia64.hpp>
#include <nt2/sdk/config/arch/none.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some other architecture specific informations
////////////////////////////////////////////////////////////////////////////////
//#include <nt2/support/config/arch/spec.hpp>
//#include <nt2/support/config/arch/endian.hpp>

#endif
