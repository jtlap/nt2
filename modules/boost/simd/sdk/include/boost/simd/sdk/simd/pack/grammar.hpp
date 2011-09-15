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
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/proto/matches.hpp>

namespace boost { namespace simd
{
  struct  grammar
    : boost::proto::
      or_< boost::proto::
           and_< boost::proto::
                 nary_expr < boost::proto::_
                           , boost::proto::vararg< grammar >
                           >
               , boost::proto::
                 not_< boost::proto::or_ < boost::proto::
                                           address_of< grammar >
                                         , boost::proto::
                                           dereference< grammar >
                                         , boost::proto::
                                           comma < grammar
                                                 , grammar
                                                 >
                                         , meta::assignment_operators
                                         >
                     >
               >
         , boost::proto::terminal< native<boost::proto::_, boost::proto::_> >
         , boost::proto::
           and_< boost::proto::terminal<boost::proto::_>
               , boost::proto::if_ < boost::dispatch::details::
                                     is_array<boost::proto::_value>()
                                   >
               >
         , boost::proto::
           and_< boost::proto::terminal<boost::proto::_>
               , boost::proto::if_ < boost::
                                     is_arithmetic<boost::proto::_value>()
                                   >
               >
         >
  {
  };
} }

#endif
