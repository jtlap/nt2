/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DSL_DIGITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DSL_DIGITS_HPP_INCLUDED
#if 0

////////////////////////////////////////////////////////////////////////////////
// Turn some digits consatnt into DSL terminals
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/sdk/constant/category.hpp>

namespace boost { namespace simd
{
  boost::proto::terminal< constant_<tag::Digit< -10 > > >::type mten_    = {{}};
  boost::proto::terminal< constant_<tag::Digit< -9 > > >::type mnine_    = {{}};
  boost::proto::terminal< constant_<tag::Digit< -8 > > >::type meight_   = {{}};
  boost::proto::terminal< constant_<tag::Digit< -7 > > >::type mseven_   = {{}};
  boost::proto::terminal< constant_<tag::Digit< -6 > > >::type msix_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< -5 > > >::type mfive_    = {{}};
  boost::proto::terminal< constant_<tag::Digit< -4 > > >::type mfour_    = {{}};
  boost::proto::terminal< constant_<tag::Digit< -3 > > >::type mthree_   = {{}};
  boost::proto::terminal< constant_<tag::Digit< -2 > > >::type mtwo_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< -1 > > >::type mone_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< 0 > > >::type zero_      = {{}};
  boost::proto::terminal< constant_<tag::Digit< 1 > > >::type one_       = {{}};
  boost::proto::terminal< constant_<tag::Digit< 2 > > >::type two_       = {{}};
  boost::proto::terminal< constant_<tag::Digit< 3 > > >::type three_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< 4 > > >::type four_      = {{}};
  boost::proto::terminal< constant_<tag::Digit< 5 > > >::type five_      = {{}};
  boost::proto::terminal< constant_<tag::Digit< 6 > > >::type six_       = {{}};
  boost::proto::terminal< constant_<tag::Digit< 7 > > >::type seven_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< 8 > > >::type eight_     = {{}};
  boost::proto::terminal< constant_<tag::Digit< 9 > > >::type nine_      = {{}};
  boost::proto::terminal< constant_<tag::Digit< 10 > > >::type ten_      = {{}};
  boost::proto::terminal< constant_<tag::Digit< 20 > > >::type twenty_   = {{}};
  boost::proto::terminal< constant_<tag::Digit< 100> > >::type hundred_  = {{}};
  boost::proto::terminal< constant_<tag::Digit<1000> > >::type thousand_ = {{}};

  boost::proto::terminal< constant_<tag::Digit< 45 > > >::type fortyfive_        = {{}};
  boost::proto::terminal< constant_<tag::Digit< 90 > > >::type ninety_           = {{}};
  boost::proto::terminal< constant_<tag::Digit< 180> > >::type onehundredeighty_ = {{}};
} }

#endif
#endif
