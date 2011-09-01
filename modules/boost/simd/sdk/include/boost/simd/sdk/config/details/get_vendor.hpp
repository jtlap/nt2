//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_GET_VENDOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_GET_VENDOR_HPP_INCLUDED

/*!
 *\file get_vendor.hpp
 *\brief Runtime function to get the Vendor Processor. 
*/

namespace boost { namespace simd { namespace config{ namespace details {

  enum{intel, amd, ibm};
  int get_vendor();

} } } } 

#endif
