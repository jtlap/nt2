/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_MASKS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Here is the registration of the cpuid masks coming from extensions headers.
// All SIMD extension detections go down to file.
// When a new SIMD extension needs to be detected at runtime, you can register
// this extension by specializing cpuid_mask on the extension's tag and the 
// vendor. You just need to provide a member function that describes how to 
// detect the extension at runtime and return a boolean.
// You need to follow the same way to add a new vendor detection at runtime. 
////////////////////////////////////////////////////////////////////////////////

#include <boost/simd/sdk/config/details/masks/forward.hpp>
#include <boost/simd/sdk/config/details/masks/vendor.hpp>
#include <boost/simd/sdk/config/details/masks/sse.hpp>
#include <boost/simd/sdk/config/details/masks/altivec.hpp>

#endif
