/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DSL_DIGITS_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DSL_DIGITS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Turn some digits consatnt into DSL terminals
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/category.hpp>

namespace nt2
{
  boost::proto::terminal< constant_<tag::digit_< -10 > > >::type mten_    = {{}};
  boost::proto::terminal< constant_<tag::digit_< -9 > > >::type mnine_    = {{}};
  boost::proto::terminal< constant_<tag::digit_< -8 > > >::type meight_   = {{}};
  boost::proto::terminal< constant_<tag::digit_< -7 > > >::type mseven_   = {{}};
  boost::proto::terminal< constant_<tag::digit_< -6 > > >::type msix_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< -5 > > >::type mfive_    = {{}};
  boost::proto::terminal< constant_<tag::digit_< -4 > > >::type mfour_    = {{}};
  boost::proto::terminal< constant_<tag::digit_< -3 > > >::type mthree_   = {{}};
  boost::proto::terminal< constant_<tag::digit_< -2 > > >::type mtwo_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< -1 > > >::type mone_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< 0 > > >::type zero_      = {{}};
  boost::proto::terminal< constant_<tag::digit_< 1 > > >::type one_       = {{}};
  boost::proto::terminal< constant_<tag::digit_< 2 > > >::type two_       = {{}};
  boost::proto::terminal< constant_<tag::digit_< 3 > > >::type three_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< 4 > > >::type four_      = {{}};
  boost::proto::terminal< constant_<tag::digit_< 5 > > >::type five_      = {{}};
  boost::proto::terminal< constant_<tag::digit_< 6 > > >::type six_       = {{}};
  boost::proto::terminal< constant_<tag::digit_< 7 > > >::type seven_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< 8 > > >::type eight_     = {{}};
  boost::proto::terminal< constant_<tag::digit_< 9 > > >::type nine_      = {{}};
  boost::proto::terminal< constant_<tag::digit_< 10 > > >::type ten_      = {{}};
  boost::proto::terminal< constant_<tag::digit_< 20 > > >::type twenty_   = {{}};
  boost::proto::terminal< constant_<tag::digit_< 100> > >::type hundred_  = {{}};
  boost::proto::terminal< constant_<tag::digit_<1000> > >::type thousand_ = {{}};

  boost::proto::terminal< constant_<tag::digit_< 45 > > >::type fortyfive_        = {{}};
  boost::proto::terminal< constant_<tag::digit_< 90 > > >::type ninety_           = {{}};
  boost::proto::terminal< constant_<tag::digit_< 180> > >::type onehundredeighty_ = {{}};
}

#endif
