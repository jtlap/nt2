/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DSL_REAL_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DSL_REAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Turn some digits consatnt into DSL terminals
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/category.hpp>

namespace nt2
{
  boost::proto::terminal< constant_<tag::pi_ > >::type          pi_         = {{}};
  boost::proto::terminal< constant_<tag::nan_> >::type          nan_        = {{}};
  boost::proto::terminal< constant_<tag::sqrt_2_o_2_> >::type   sqrt_2_o_2_ = {{}};
  boost::proto::terminal< constant_<tag::sqrt_2_> >::type       sqrt_2_     = {{}};
  boost::proto::terminal< constant_<tag::gold_> >::type         gold_       = {{}};
  boost::proto::terminal< constant_<tag::c_gold_> >::type       cgold_      = {{}};
  boost::proto::terminal< constant_<tag::m_half_> >::type       mhalf_      = {{}};
  boost::proto::terminal< constant_<tag::m_zero_> >::type       mzero_      = {{}};
  boost::proto::terminal< constant_<tag::half_> >::type         half_       = {{}};
  boost::proto::terminal< constant_<tag::third_> >::type        third_      = {{}};
  boost::proto::terminal< constant_<tag::quarter_> >::type      quarter_    = {{}};
}

#endif
