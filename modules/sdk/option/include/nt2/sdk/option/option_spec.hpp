//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_OPTION_OPTION_SPEC_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_SPEC_HPP_INCLUDED

#include <nt2/sdk/option/option_term.hpp>
#include <boost/proto/matches.hpp>

namespace nt2 { namespace details
{
  struct option_spec
      : boost::proto::when<
          boost::proto::assign<
              option_term
            , boost::proto::terminal<boost::proto::_>
          >
        , boost::proto::_value(boost::proto::_right)
      >
  {};
} }

#endif
