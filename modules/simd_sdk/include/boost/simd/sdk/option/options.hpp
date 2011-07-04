//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_SDK_OPTION_OPTIONS_HPP_INCLUDED
#define BOOST_SIMD_SDK_OPTION_OPTIONS_HPP_INCLUDED

#include <boost/simd/sdk/option/option_pack.hpp>
#include <boost/simd/sdk/option/option_expr.hpp>
#include <boost/simd/sdk/error/static_assert.hpp>

namespace boost { namespace simd {  namespace details
{
  struct options_
  {
    template<class Opts>
    Opts const& operator[](Opts const& opts) const
    {
      BOOST_SIMD_STATIC_ASSERT ( (boost::proto::matches<Opts, option_pack>::value)
                        , UNKNOWN_NAMED_OPTIONS
                        , "Trying to retrieve unknown named option."
                        );
      return opts;
    }
  };
} } }

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // options entry-point
  //////////////////////////////////////////////////////////////////////////////
    details::options_ const options = {};
} }

#define BOOST_SIMD_REGISTER_PARAMETERS(NAME)                               \
struct NAME ## _ {};                                                \
boost::simd::details::option_expr<                                          \
    boost::proto::terminal<boost::simd::details::option<NAME ## _> >::type  \
> const NAME = {};                                                  \
/**/

#endif

