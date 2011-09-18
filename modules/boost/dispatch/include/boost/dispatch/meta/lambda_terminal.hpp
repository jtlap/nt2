//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DSL_LAMBDA_TERMINAL_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_LAMBDA_TERMINAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Defines a terminal fitting a lambda function
////////////////////////////////////////////////////////////////////////////////
#include <boost/proto/transform.hpp>

namespace boost { namespace dispatch
{
  template<class Lambda>
  struct  lambda_terminal
        : boost::proto::
           and_< boost::proto::terminal<boost::proto::_>
               , boost::proto::if_ < Lambda() >
               >
  {};
} }

#endif
