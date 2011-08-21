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
    BOOST_PROTO_BASIC_EXTENDS_TPL( (typename boost::proto::
                                    terminal< typename meta::
                                                       vector_of< Type
                                                                , boost::mpl::
                                                                         size_t<Cardinal>::value
                                                                >::type
                                            >::type)
                                 , (pack<Type,Cardinal>)
                                 , (domain<Type,boost::mpl::size_t<Cardinal> >))

    ////////////////////////////////////////////////////////////////////////////
    // Pack must be sized with a power of 2
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_STATIC_ASSERT ( (meta::is_power_of_2_c<Cardinal>::value)
                      , INVALID_SIMD_PACK_CARDINAL
                      , "SIMD pack instanciated with non-power of 2 Cardinal."
                      );

    ////////////////////////////////////////////////////////////////////////////
    // Data holder of pack terminals
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    meta::vector_of<Type, boost::mpl::size_t<Cardinal>::value>::type data_type;

    ////////////////////////////////////////////////////////////////////////////
    // expression hierarchy of simd:::expression
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    dispatch::details::hierarchy_of_expr<pack>::type  dispatch_hierarchy_tag;
    typedef data_type                                 dispatch_semantic_tag;

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    typedef typename data_type::value_type      value_type;
    typedef typename data_type::reference       reference;
    typedef typename data_type::const_reference const_reference;
    typedef typename data_type::size_type       size_type;
    typedef typename data_type::iterator        iterator;
    typedef typename data_type::const_iterator  const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // Array interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT(size_type, static_size = data_type::static_size);

    ////////////////////////////////////////////////////////////////////////////
    // Assignments
    ////////////////////////////////////////////////////////////////////////////
    pack& operator=(pack const& src)
    {
      boost::proto::value(*this) = boost::proto::value(src);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Array Interface
    ////////////////////////////////////////////////////////////////////////////
    reference  operator[](int i)
    {
      return boost::proto::value(*this)[i];
    }

    const_reference  operator[](int i) const
    {
      return boost::proto::value(*this)[i];
    }

    void fill(Type const& a0)
    {
      fill(a0, typename meta::is_native<data_type>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    iterator        begin()         { return boost::proto::value(*this).begin(); }
    iterator        end()           { return boost::proto::value(*this).end();   }
    const_iterator  begin()  const  { return boost::proto::value(*this).begin(); }
    const_iterator  end()    const  { return boost::proto::value(*this).end();   }

    ////////////////////////////////////////////////////////////////////////////
    // Immutable access to underlying value
    ////////////////////////////////////////////////////////////////////////////
    data_type const& value() const { return boost::proto::value(*this); }

    template<class X> void evaluate(X const& xpr)
    {
      boost::simd::evaluate(boost::proto::value(*this), xpr);
    }

    ////////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as pack in assignment context
    // TODO: fix to use obliviosu AST evaluation
    ////////////////////////////////////////////////////////////////////////////
    template<class X> pack& operator=(X const& xpr )
    {
      evaluate(xpr);
      return *this;
    }

    #define BOOST_SIMD_MAKE_ASSIGN_OP(OP)                               \
    template<class X> pack& operator BOOST_PP_CAT(OP,=)(X const& xpr )  \
    {                                                                   \
      evaluate(*this OP xpr);                                           \
      return *this;                                                     \
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

    private :

    void fill(Type const& a0, boost::mpl::true_ const&)
    {
      boost::proto::value(*this) = splat<data_type>(a0);
    }

    void fill(Type const& a0, boost::mpl::false_ const&)
    {
      boost::proto::value(*this).fill(a0);
    }
  };
} }

#endif
