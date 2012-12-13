/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/pack/domain.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/proto/extends.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Here is the domain-specific expression wrapper
  ////////////////////////////////////////////////////////////////////////////
  template<class Expr, class ResultType>
  struct expression
  {
    BOOST_PROTO_BASIC_EXTENDS(Expr, expression, domain)

    // Assignment operators force evaluation
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression const& xpr)
    {
      boost::simd::evaluate(
        boost::simd::assign(*this, xpr)
      );
      return *this;
    }

    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    typename boost::disable_if< boost::is_base_of<expression, Xpr>
                              , expression&
                              >::type
    operator=(Xpr const& xpr)
    {
      boost::simd::evaluate(
        boost::simd::assign(*this, xpr)
      );
      return *this;
    }

    // Conversion operator forces evaluation
    BOOST_DISPATCH_FORCE_INLINE
    operator typename dispatch::meta::terminal_of<ResultType>::type() const
    {
      return boost::simd::evaluate(*this);
    }
  };
} }

#endif
