/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Settings tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct padding {}; } }

#include <nt2/sdk/memory/details/no_padding.hpp>
#include <nt2/sdk/memory/details/lead_padding.hpp>
#include <nt2/sdk/memory/details/global_padding.hpp>

#endif
