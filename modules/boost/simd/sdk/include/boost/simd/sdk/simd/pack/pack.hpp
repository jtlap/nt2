//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/pack/meta.hpp>
#include <boost/simd/sdk/simd/pack/fusion_iterator.hpp>
#include <boost/simd/sdk/simd/pack/fusion.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/assign.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/operators.hpp>
#include <boost/mpl/bool.hpp>

#define BOOST_SIMD_PACK_CONSTRUCTORS

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Cardinal, class Dummy>
  struct BOOST_SIMD_MAY_ALIAS pack
    : expression< typename
                  proto::terminal< typename
                                   meta::vector_of< Type
                                                  , boost::mpl::size_t<Cardinal>::value
                                                  >::type
                                 >::type
                 , typename
                   meta::vector_of< Type
                                  , boost::mpl::size_t<Cardinal>::value
                                  >::type&
                 >
  {
    typedef Type                   value_type;
    typedef value_type&             reference;
    typedef value_type const& const_reference;

    typedef typename
    meta::vector_of<Type, boost::mpl::size_t<Cardinal>::value>::type data_type;
    typedef typename proto::terminal<data_type>::type       expr_type;

    typedef typename data_type::iterator       iterator;
    typedef typename data_type::iterator const_iterator;

    typedef expression< typename
                        proto::terminal< typename
                                         meta::vector_of< Type
                                                        , boost::mpl::size_t<Cardinal>::value
                                                        >::type
                                       >::type
                      , typename
                        meta::vector_of< Type
                                       , boost::mpl::size_t<Cardinal>::value
                                       >::type&
                      > parent;


    pack() {}

    pack(pack const& p)
    {
      *this = boost::proto::value(p);
    }

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
        boost::simd::assign(*this, xpr)
      );
      return *this;
    }
    
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    pack& operator=(Xpr const& xpr)
    {
      boost::simd::evaluate(
        boost::simd::assign(*this, xpr)
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

    reference        operator[](std::size_t i)
    {
      return boost::proto::value(*this)[i];
    }

    const_reference  operator[](std::size_t i) const
    {
      return boost::proto::value(*this)[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FORCE_INLINE
    iterator       begin()       { return boost::proto::value(*this).begin(); }
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator begin() const { return boost::proto::value(*this).begin(); }
    BOOST_DISPATCH_FORCE_INLINE
    iterator       end()         { return boost::proto::value(*this).end();   }
    BOOST_DISPATCH_FORCE_INLINE
    const_iterator end()   const { return boost::proto::value(*this).end();   }

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_DISPATCH_FORCE_INLINE
    std::size_t size() { return data_type::size(); }

    static BOOST_DISPATCH_FORCE_INLINE
    bool empty() { return false; }

    ////////////////////////////////////////////////////////////////////////////
    // Fusion RandomAccessSequence interface
    ////////////////////////////////////////////////////////////////////////////
    typedef tag::pack_ fusion_tag;
  };
} }

#endif
