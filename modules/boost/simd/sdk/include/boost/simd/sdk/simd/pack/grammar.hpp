/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GRAMMAR_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/dsl/is_assignment_expression.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/dispatch/meta/lambda_terminal.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/proto/matches.hpp>

namespace boost { namespace simd
{
  struct  grammar
    : proto::or_< 
        proto::and_ < proto::nary_expr< proto::_, proto::vararg<grammar> >
                    , proto::not_< proto::or_ < proto::address_of<grammar>
                                              , proto::dereference<grammar>
                                              , proto::comma<grammar,grammar>
                                              , proto::nary_expr<proto::tag::function, proto::vararg<grammar> >
                                              , meta::assignment_operators
                                              >
                                  >
                    >
         , proto::terminal< native<proto::_, proto::_> >
         , dispatch::lambda_terminal<dispatch::details::is_array<proto::_value> >
         , dispatch::lambda_terminal<is_arithmetic<proto::_value> >
         , proto::terminal< dispatch::meta::as_< native<proto::_, proto::_> > >
                >
  {
  };
} }

#endif
