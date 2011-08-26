/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_GET_VENDOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_GET_VENDOR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Runtime function to get the Vendor Processor. 
////////////////////////////////////////////////////////////////////////////////
#define INTEL "GenuineIntel"
#define AMD   "AuthenticAMD"

namespace boost { namespace simd { namespace config{ namespace details {

  int get_vendor();

} } } } 

#endif
