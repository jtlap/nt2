/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/meta.hpp>
#include <boost/simd/sdk/simd/pack/evaluate.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Cardinal, class Dummy>
  struct  pack
  {
    typedef typename
    meta::vector_of<Type, boost::mpl::size_t<Cardinal>::value>::type data_type;
    typedef typename proto::terminal<data_type>::type expr_type;
    
    BOOST_PROTO_BASIC_EXTENDS(expr_type, pack, domain)

    //==========================================================================
    /*
     * SIMD pack instanciated with non-power of 2 Cardinal or a Cardinal of 1.
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (meta::is_power_of_2_c<Cardinal>::value && Cardinal != 1)
    , INVALID_SIMD_PACK_CARDINAL
    , (boost::mpl::int_<Cardinal>)
    );

    // Assignment operators force evaluation
    BOOST_DISPATCH_FORCE_INLINE
    pack& operator=(pack const& xpr)
    {
      boost::simd::evaluate(
        assign(*this, xpr)
      );
      return *this;
    }
    
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    pack& operator=(Xpr const& xpr)
    {
      boost::simd::evaluate(
        assign(*this, xpr)
      );
      return *this;
    }

    #define BOOST_SIMD_MAKE_ASSIGN_OP(OP)                               \
    template<class X>                                                   \
    BOOST_DISPATCH_FORCE_INLINE                                         \
    pack& operator BOOST_PP_CAT(OP,=)(X const& xpr)                     \
    {                                                                   \
      return *this = *this OP xpr;                                      \
    }                                                                   \
    /**/

    BOOST_SIMD_MAKE_ASSIGN_OP(+)
    BOOST_SIMD_MAKE_ASSIGN_OP(-)
    BOOST_SIMD_MAKE_ASSIGN_OP(*)
    BOOST_SIMD_MAKE_ASSIGN_OP(/)
    BOOST_SIMD_MAKE_ASSIGN_OP(%)
    BOOST_SIMD_MAKE_ASSIGN_OP(^)
    BOOST_SIMD_MAKE_ASSIGN_OP(&)
    BOOST_SIMD_MAKE_ASSIGN_OP(|)
    BOOST_SIMD_MAKE_ASSIGN_OP(>>)
    BOOST_SIMD_MAKE_ASSIGN_OP(<<)

    #undef BOOST_SIMD_MAKE_ASSIGN_OP

    // Conversion operator forces evaluation
    BOOST_DISPATCH_FORCE_INLINE
    operator data_type() const
    {
      return boost::simd::evaluate(*this);
    }
  };
} }

#endif
