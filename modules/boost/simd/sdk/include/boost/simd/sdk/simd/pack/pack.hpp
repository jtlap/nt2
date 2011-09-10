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

#include <boost/proto/core.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/meta.hpp>
#include <boost/simd/sdk/simd/pack/evaluation.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/simd/include/functions/load.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal,class Dummy>
  struct  pack
  {
    typedef typename
    meta::vector_of<Type, boost::mpl::size_t<Cardinal>::value>::type data_type;
    typedef typename proto::terminal<data_type>::type expr_type;
    
    BOOST_PROTO_BASIC_EXTENDS_TPL( (expr_type)
                                 , (pack<Type,Cardinal>)
                                 , (domain)
                                 )

    //==========================================================================
    /*
     * SIMD pack instanciated with non-power of 2 Cardinal.
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (meta::is_power_of_2_c<Cardinal>::value)
    , INVALID_SIMD_PACK_CARDINAL
    , (boost::mpl::int_<Cardinal>)
    );

    ////////////////////////////////////////////////////////////////////////////
    // expression hierarchy of simd:::expression
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    dispatch::details::hierarchy_of_expr<pack>::type  dispatch_hierarchy_tag;
    typedef typename expr_type::result_type           dispatch_semantic_tag;

    // Assignment operators force evaluation
    BOOST_DISPATCH_FORCE_INLINE
    pack& operator=(pack const& src)
    {
      return boost::simd::evaluate(proto::make_expr<tag::assign_>(*this, xpr));
    }
    
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    pack& operator=(Xpr const& xpr)
    {
      return boost::simd::evaluate(proto::make_expr<tag::assign_>(*this, xpr));
    }

    #define BOOST_SIMD_MAKE_ASSIGN_OP(OP)                               \
    template<class X>                                                   \
    BOOST_DISPATCH_FORCE_INLINE                                         \
    pack& operator BOOST_PP_CAT(OP,=)(X const& xpr )                    \
    {                                                                   \
      return *this = *this OP expr;                                     \
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
    operator dispatch_semantic_tag()
    {
      return boost::simd::evaluate(*this);
    }
  };
} }

#endif
