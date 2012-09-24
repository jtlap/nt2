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

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/pack/expression.hpp>

#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/pack/meta.hpp>
#include <boost/simd/sdk/simd/pack/fusion_iterator.hpp>
#include <boost/simd/sdk/simd/pack/fusion.hpp>

#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/details/operators.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>

#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/make.hpp>

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>

#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Cardinal>
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

    pack() {}

    pack(data_type const& p)
    {
      proto::value(*this) = p;
    }

    template<class ScalarIterator>
    pack( ScalarIterator i
        , typename enable_if< dispatch::meta::is_iterator<ScalarIterator> >::type* = 0)
    {
      typedef typename boost::pointee<ScalarIterator>::type value_type;
      BOOST_STATIC_ASSERT_MSG
      ( (boost::is_same<Type,value_type>::value)
      , "The constructor of pack<T,C> has been called on a iterator"
        "which value_type is different from T."
      );

      value_type* p = &(*i);

      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(p,sizeof(data_type))
      , "The constructor of pack<T,C> has been called on a iterator"
        "which alignment is not compatible with current SIMD extension."
      );

      proto::value(*this) = load< data_type >(p,0);
    }

    //==========================================================================
    // Constructor from scalar range
    //==========================================================================
    template<class ScalarIterator>
    pack( ScalarIterator b, ScalarIterator e
        , typename enable_if< dispatch::meta::is_iterator<ScalarIterator> >::type* = 0)
    {
      BOOST_ASSERT_MSG
      ( ((e-b)==Cardinal)
      , "The constructor of pack<T,C> has been called on a iterator"
        "which alignment is not compatible with current SIMD extension."
      );

      for(int i=0;b!=e;++b,++i)
        (*this)[i] = *b;
    }
    //template<class Expr> pack(Expr const& expr) : parent(expr) {}

    //==========================================================================
    // Constructor from unique scalar value -> splat the value
    //==========================================================================
    template<class T>
    pack(T const& t, typename enable_if< is_arithmetic<T> >::type* = 0)
    {
      proto::value(*this) = simd::splat<data_type>(t);
    }

    //==========================================================================
    // Create constructors for pack according to the extension specification.
    //==========================================================================
    #define M1(z, n, arg)                                                                          \
    template<class T>                                                                              \
    pack(BOOST_PP_ENUM_PARAMS(arg, T const& a), typename enable_if< is_arithmetic<T> >::type* = 0) \
    {                                                                                              \
      proto::value(*this) = make<data_type>(BOOST_PP_ENUM_PARAMS(arg, a));                         \
    }                                                                                              \
    /**/
    BOOST_PP_SEQ_FOR_EACH(M1, ~, BOOST_SIMD_CARDINALS)
    #undef M1

    using parent::operator=;

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
