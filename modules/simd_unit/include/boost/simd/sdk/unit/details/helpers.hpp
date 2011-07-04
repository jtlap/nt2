/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED

#include <string>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/details/type_id.hpp>
#include <boost/algorithm/string/replace.hpp>

////////////////////////////////////////////////////////////////////////////////
// strip function name cruft
////////////////////////////////////////////////////////////////////////////////
template<class T> inline std::string function_name()
{
  std::string that(boost::simd::type_id<T>().c_str());
  boost::replace_all(that,"boost::simd::functors::","");
  boost::replace_all(that,"boost::simd::","");
  boost::replace_all(that,", void","");
  boost::replace_all(that,"boost::proto::tag::","");
  boost::replace_all(that,"()","");
  return that;
}

////////////////////////////////////////////////////////////////////////////////
// roll a random number (will be boost::simd::rand afterward)
////////////////////////////////////////////////////////////////////////////////
template<class T,class X, class Y> inline T roll(X mn, Y mx)
{
  double r = ((double)rand()/RAND_MAX)*(mx-mn) + mn;
  T that  = boost::simd::splat<T>(r);
  return that;
}

#endif
