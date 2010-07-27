/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED

#include <string>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <boost/algorithm/string/replace.hpp>

////////////////////////////////////////////////////////////////////////////////
// strip function name cruft
////////////////////////////////////////////////////////////////////////////////
template<class T> inline std::string function_name()
{
  std::string that(nt2::type_id<T>().c_str());
  boost::replace_all(that,"nt2::functors::","");
  boost::replace_all(that,"nt2::simd::","");
  boost::replace_all(that,", void","");
  boost::replace_all(that,"boost::proto::tag::","");
  boost::replace_all(that,"()","");
  return that;
}

////////////////////////////////////////////////////////////////////////////////
// roll a random number (will be nt2::rand afterward)
////////////////////////////////////////////////////////////////////////////////
template<class T,class X, class Y> inline T roll(X mn, Y mx)
{
  double r = ((double)rand()/RAND_MAX)*(mx-mn) + mn;
  T that  = nt2::splat<T>(r);
  return that;
}

#endif
