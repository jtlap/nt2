/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DSL_BOOLEAN_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DSL_BOOLEAN_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Turn some digits consatnt into DSL terminals
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/proto.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/constant/category.hpp>

namespace nt2
{
  boost::proto::terminal< constant_<tag::true_ > >::type true_  = {{}};
  boost::proto::terminal< constant_<tag::false_> >::type false_ = {{}};
}

#endif
