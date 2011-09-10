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

#include <boost/proto/matches.hpp>
#include <boost/simd/sdk/dsl/is_assignment_expression.hpp>

namespace boost { namespace simd
{
  struct  grammar
        : boost::proto::
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
              > {};
} }

#endif
