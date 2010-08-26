/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_OPTIONS_OPTION_TERM_HPP_INCLUDED
#define NT2_SDK_OPTIONS_OPTION_TERM_HPP_INCLUDED

#include <nt2/sdk/options/option.hpp>
#include <boost/proto/core.hpp>

namespace nt2 { namespace details
{
  struct option_term
      : boost::proto::terminal< option< boost::proto::_ > >
  {};
} }

#endif
