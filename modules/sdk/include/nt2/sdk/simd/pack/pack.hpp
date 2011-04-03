/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_PACK_HPP_INCLUDED

#include <boost/proto/core.hpp>
#include <nt2/sdk/dsl/call.hpp>
#include <nt2/sdk/simd/pack/meta.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type,std::size_t Cardinal,class BP>
  struct  pack
  {
    ////////////////////////////////////////////////////////////////////////////
    // Pack must be sized with a power of 2
    ////////////////////////////////////////////////////////////////////////////
    NT2_STATIC_ASSERT ( (meta::is_power_of_2_c<Cardinal>::value)
                      , INVALID_SIMD_PACK_CARDINAL
                      , "SIMD pack instanciated with non-power of 2 Cardinal."
                      );

    ////////////////////////////////////////////////////////////////////////////
    // Data holder of pack terminals
    ////////////////////////////////////////////////////////////////////////////
    typedef data<Type,boost::mpl::size_t<Cardinal> >            data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Make pack a POD proto expression
    ////////////////////////////////////////////////////////////////////////////
    BOOST_PROTO_BASIC_EXTENDS_TPL
    ( typename boost::proto::terminal<data_type>::type
    , (pack<Type,Cardinal>)
    , (simd::domain<Type, boost::mpl::size_t<Cardinal> >)
    )

    ////////////////////////////////////////////////////////////////////////////
    // Semantic of terminal is the actual data type
    ////////////////////////////////////////////////////////////////////////////
    typedef data_type semantic_type;

    ////////////////////////////////////////////////////////////////////////////
    // expression hierarchy of simd:::expression
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    details::hierarchy_of_expr<pack>::type nt2_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    typedef typename data_type::parent          base_type;
    typedef typename data_type::value_type      value_type;
    typedef typename data_type::reference       reference;
    typedef typename data_type::const_reference const_reference;
    typedef typename data_type::size_type       size_type;
    typedef typename data_type::iterator        iterator;
    typedef typename data_type::const_iterator  const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // Array interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT(size_type, static_size = base_type::static_size);

    ////////////////////////////////////////////////////////////////////////////
    // Default Constructor
    ////////////////////////////////////////////////////////////////////////////
    pack() {}

    ////////////////////////////////////////////////////////////////////////////
    // Copy Constructor
    ////////////////////////////////////////////////////////////////////////////
    pack(pack const& src)
    {
      boost::proto::value(*this) = boost::proto::value(src);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Constructor from native udnerlying type
    ////////////////////////////////////////////////////////////////////////////
    pack(base_type const& a0)
    {
      boost::proto::value(*this) = a0;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Construct from Iterator + offset
    ////////////////////////////////////////////////////////////////////////////
    template<class Iterator>
    pack( Iterator it, std::ptrdiff_t offset
        , typename boost::enable_if< meta::is_iterator<Iterator> >::type* = 0
        )
    {
      boost::proto::value(*this) = load<base_type>(it,offset);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Construct from Iterator + offset + suboffset
    ////////////////////////////////////////////////////////////////////////////
    template<class Iterator, class Suboffset>
    pack( Iterator it
        , std::ptrdiff_t offset
        , Suboffset const&
        , typename
          boost::enable_if_c<   meta::is_iterator<Iterator>::value
                            &&  details::is_mpl_integral<Suboffset>::value
                            >::type* = 0
        )
    {
      boost::proto::value(*this) = load<base_type,Suboffset::value>(it,offset);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Construct from Range ?
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Construct from explicit list of values - requires PP ?
    ////////////////////////////////////////////////////////////////////////////

    // to be removed
    explicit pack(Type const& a0)
    {
      boost::proto::value(*this).fill(a0);
    }

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
      boost::proto::value(*this).fill(a0);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    iterator        begin()         { return boost::proto::value(*this).begin(); }
    iterator        end()           { return boost::proto::value(*this).end();   }
    const_iterator  begin()  const  { return boost::proto::value(*this).begin(); }
    const_iterator  end()    const  { return boost::proto::value(*this).end();   }

    ////////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as pack
    ////////////////////////////////////////////////////////////////////////////
    template<class X>
    pack( X const& xpr
        , typename boost::disable_if< boost::is_convertible<X,Type> >::type* = 0
        )
    {
      // TODO: check that X can be put in a pack via evaluation
      boost::proto::value(*this).evaluate(xpr);
    }

    ////////////////////////////////////////////////////////////////////////////
    // SIMD expression evaluates as pack in assignment context
    // TODO: fix to use obliviosu AST evaluation
    ////////////////////////////////////////////////////////////////////////////
    template<class X> pack& operator=(X const& xpr )
    {
      boost::proto::value(*this).evaluate(xpr);
      return *this;
    }

    #define NT2_MAKE_ASSIGN_OP(OP)                                      \
    template<class X> pack& operator BOOST_PP_CAT(OP,=)(X const& xpr )  \
    {                                                                   \
      boost::proto::value(*this).evaluate(*this OP xpr);                \
      return *this;                                                     \
    }                                                                   \
    /**/

    NT2_MAKE_ASSIGN_OP(+)
    NT2_MAKE_ASSIGN_OP(-)
    NT2_MAKE_ASSIGN_OP(*)
    NT2_MAKE_ASSIGN_OP(/)
    NT2_MAKE_ASSIGN_OP(%)
    NT2_MAKE_ASSIGN_OP(^)
    NT2_MAKE_ASSIGN_OP(&)
    NT2_MAKE_ASSIGN_OP(|)
    NT2_MAKE_ASSIGN_OP(>>)
    NT2_MAKE_ASSIGN_OP(<<)

    #undef NT2_MAKE_ASSIGN_OP
  };
} }

#endif
