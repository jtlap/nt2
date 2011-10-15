//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/proto/extends.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/container/meta/container_traits.hpp>
#include <nt2/core/container/meta/settings_of.hpp>
#include <nt2/core/settings/size.hpp>

// Semantic of NT2 expression lies in its ResultType template parameter
namespace boost { namespace dispatch { namespace meta
{
  template<class Expr, class ResultType>
  struct semantic_of< nt2::container::expression<Expr, ResultType> >
  {
    typedef ResultType type;
  };
} } }

namespace nt2 { namespace container
{
  template<class Expr, class ResultType>
  struct  expression
        : boost::proto::extends < Expr
                                , expression<Expr, ResultType>
                                , container::domain
                                >
  {
    //==========================================================================
    /*! Type of the parent expression                                         */
    //==========================================================================
    typedef boost::proto::extends < Expr
                                  , expression<Expr, ResultType>
                                  , container::domain
                                  >                                parent;

    //==========================================================================
    /* Extract Container information from ResultType                          */
    //==========================================================================
    typedef typename meta::value_type_<ResultType>::type      value_type;
    typedef typename meta::reference_<ResultType>::type       reference;
    typedef typename meta::const_reference_<ResultType>::type const_reference;

    typedef typename meta::settings_of<ResultType>::type              settings_type;
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;
    typedef typename meta::option<settings_type, tag::index_>::type   index_type;

    //==========================================================================
    // expression initialization called from generator
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE
    expression() : size_(nt2::extent(parent::proto_base().child0)) 
    {

    }

    template<class Sz>
    BOOST_DISPATCH_FORCE_INLINE
    expression(Expr const& x, Sz const& sz) : parent(x), size_(sz) {}

    //==========================================================================
    // Assignment operator force evaluation - LHS non-terminal version
    //==========================================================================
    template<class Xpr,class Result> BOOST_DISPATCH_FORCE_INLINE
    expression const& operator=(expression<Xpr,Result> const& xpr) const
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    //==========================================================================
    // Assignment operator force evaluation - regular version
    //==========================================================================
    template<class Xpr,class Result> BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression<Xpr,Result> const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    //==========================================================================
    // Assignment operator from same expression type
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    //==========================================================================
    // Op-Assignment operators generate proper tree then evaluates
    //==========================================================================
    #define NT2_MAKE_ASSIGN_OP(OP)                                             \
    template<class Xpr,class Result>                                           \
    BOOST_DISPATCH_FORCE_INLINE expression&                                    \
    operator BOOST_PP_CAT(OP,=)(expression<Xpr,Result> const& xpr)             \
    {                                                                          \
      return *this = *this OP xpr;                                             \
    }                                                                          \
    template<class Xpr,class Result>                                           \
    BOOST_DISPATCH_FORCE_INLINE expression const&                              \
    operator BOOST_PP_CAT(OP,=)(expression<Xpr,Result> const& xpr) const       \
    {                                                                          \
      return *this = *this OP xpr;                                             \
    }                                                                          \
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

    //==========================================================================
    // Conversion operator forces evaluation - used for reduction operator
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE operator ResultType() const
    {
      // assert numel is 1
      return nt2::evaluate(*this);
    }

    extent_type const& extent() const
    {
      return size_;
    }

    private:
    extent_type const& size_;
  };
} }

#endif
