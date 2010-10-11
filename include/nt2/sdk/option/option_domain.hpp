//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_OPTION_OPTION_DOMAIN_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_DOMAIN_HPP_INCLUDED

#include <nt2/sdk/option/option_expr_fwd.hpp>
#include <boost/proto/core.hpp>

namespace nt2 { namespace details
{
  struct  option_domain
        : boost::proto::domain<boost::proto::pod_generator<option_expr> >
  {};
} }

#endif
