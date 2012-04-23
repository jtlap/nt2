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

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/domain.hpp>
#include <nt2/core/container/dsl/grammar.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/details/resize.hpp>
#include <nt2/core/container/dsl/details/expression.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/core/functions/function.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/toolbox/operator/functions/assign.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/extends.hpp>
#include <boost/mpl/assert.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#ifdef NT2_LOG_COPIES
#include <nt2/sdk/details/type_id.hpp>
#endif

namespace nt2 { namespace container
{
  //============================================================================
  // proto expression wrapper for nt2 containers
  //============================================================================
  template<class Expr, class Result>
  struct  expression
        : boost::proto::extends < Expr
                                , expression<Expr, Result>
                                , container::domain
                                >
  {
    //==========================================================================
    /*! Type of the parent expression                                         */
    //==========================================================================
    typedef boost::proto::extends < Expr
                                  , expression<Expr, Result>
                                  , container::domain
                                  >                                parent;

    //==========================================================================
    // Extract Container information from Result
    //==========================================================================
    typedef typename meta::value_type_<Result>::type        value_type;
    typedef typename meta::reference_<Result>::type         reference;
    typedef typename meta::const_reference_<Result>::type   const_reference;
    typedef typename meta::pointer_<Result>::type           pointer;
    typedef typename meta::const_pointer_<Result>::type     const_pointer;
    typedef typename meta::size_type_<Result>::type         size_type;

    typedef typename meta::settings_of<Result>::type        settings_type;
    typedef typename meta::
            option<settings_type,tag::index_>::type         index_type;
    typedef typename meta::
            option<settings_type,tag::storage_order_>::type storage_order_type;
    typedef typename meta::
            option<settings_type,tag::alignment_>::type     alignment_type;

    //==========================================================================
    // Compute storage type for size
    //==========================================================================
    typedef typename size_transform<domain>::
            template result<size_transform<domain>(Expr)>::type extent_type;

    typedef typename index_type::type                           indexes_type;

    //==========================================================================
    // Expression initialization called from generator
    //==========================================================================
    BOOST_FORCEINLINE
    expression() : size_(size_transform<domain>()(parent::proto_base())) {}

    BOOST_FORCEINLINE
    explicit  expression(Expr const& x)
            : parent(x), size_(size_transform<domain>()(parent::proto_base()))
    {}

    BOOST_FORCEINLINE
    expression( expression const& xpr )
              : parent(xpr.proto_base())
              , size_(size_transform<domain>()(parent::proto_base()))
    {
      #ifdef NT2_LOG_COPIES
      typedef typename boost::mpl::
              eval_if_c < boost::proto::arity_of<Expr>::value == 0
                        , boost::proto::result_of::value<Expr&>
                        , boost::mpl::identity<int&>
                        >::type                                     T;

      if(!boost::is_reference<T>::value)
      {
        std::cout << "copying ";
        nt2::display_type<Expr>();
      }
      #endif
    }

    //==========================================================================
    // Assignment operator force evaluation - LHS non-terminal version
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    expression const& operator=(Xpr const& xpr) const
    {
      process( xpr );
      return *this;
    }

    //==========================================================================
    // Assignment operator force evaluation - regular version
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE expression& operator=(Xpr const& xpr)
    {
      process( xpr );
      return *this;
    }

    BOOST_FORCEINLINE expression& operator=(expression const& xpr)
    {
      process( xpr );
      return *this;
    }

    //==========================================================================
    // Op-Assignment operators generate proper tree then evaluates
    //==========================================================================
    #define NT2_MAKE_ASSIGN_OP(OP)                                            \
    template<class Xpr>                                                       \
    BOOST_FORCEINLINE expression& operator BOOST_PP_CAT(OP,=)(Xpr const& xpr) \
    {                                                                         \
      return *this = *this OP xpr;                                            \
    }                                                                         \
    template<class Xpr>                                                       \
    BOOST_FORCEINLINE expression const&                                       \
    operator BOOST_PP_CAT(OP,=)(Xpr const& xpr) const                         \
    {                                                                         \
      return *this = *this OP xpr;                                            \
    }                                                                         \
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
    BOOST_FORCEINLINE operator Result() const
    {
      return nt2::evaluate(*this);
    }

    //==========================================================================
    // Expression indexing
    //==========================================================================
    #define M0(z,n,t)                                                 \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE       \
    typename meta::call                                               \
    < nt2::tag::function_                                             \
      ( expression const&                                             \
      , BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& BOOST_PP_INTERCEPT)   \
      )                                                               \
    >::type                                                           \
    operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& a) ) const    \
    {                                                                 \
      return nt2::function(*this, BOOST_PP_ENUM_PARAMS(n,a) );        \
    }                                                                 \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE       \
    typename meta::call                                               \
    < nt2::tag::function_                                             \
      ( expression&                                                   \
      , BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& BOOST_PP_INTERCEPT)   \
      )                                                               \
    >::type                                                           \
    operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& a) )          \
    {                                                                 \
      return nt2::function(*this, BOOST_PP_ENUM_PARAMS(n,a) );        \
    }                                                                 \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)
    #undef M0

    //==========================================================================
    // Idempotent operator() indexing
    //==========================================================================
    BOOST_FORCEINLINE expression&        operator()()        { return *this; }
    BOOST_FORCEINLINE expression const&  operator()() const  { return *this; }

    //==========================================================================
    // Return current expression extent
    //==========================================================================
    BOOST_FORCEINLINE extent_type extent() const { return size_; }

    //==========================================================================
    // Return current expression base indexes
    //==========================================================================
    BOOST_FORCEINLINE indexes_type indexes() const { return indexes_type(); }

    //==========================================================================
    // Return current expression leading_size
    //==========================================================================
    BOOST_FORCEINLINE size_type leading_size() const
    {
      typedef typename meta::strip<extent_type>::type sizes_t;
      typedef typename boost::mpl
                            ::apply < storage_order_type
                                    , boost::mpl::size_t<sizes_t::static_size>
                                    , boost::mpl::size_t<0U>
                                    >::type                     dim_t;
      return size_[dim_t::value];
    }

    //==========================================================================
    // Access to raw data
    //==========================================================================
    pointer       raw()
    {
      //========================================================================
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      // If this static assert triggers, the raw memory of a non terminal node
      // has been requested.
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                          , (Expr)
                          );

      return nt2::terminal(*this).raw();
    }

    const_pointer raw() const
    {
      //========================================================================
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      // If this static assert triggers, the raw memory of a non terminal node
      // has been requested.
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                          , (Expr)
                          );

      return nt2::terminal(*this).raw();
    }

    //==========================================================================
    // Destructive resize of expression
    //==========================================================================
    template<class Sz> BOOST_FORCEINLINE void resize(Sz const& sz)
    {
      ext::resize< typename boost::dispatch::meta::
                   hierarchy_of< typename boost::proto::tag_of<parent>::type >::type
                 , domain
                 , boost::proto::arity_of<parent>::type::value
                 , expression<Expr, Result>
                 >
      ()(*this, sz);
    }

    template<class Sz> BOOST_FORCEINLINE void resize(Sz const& sz) const
    {
      ext::resize< typename boost::dispatch::meta::
                   hierarchy_of< typename boost::proto::tag_of<parent>::type >::type
                 , domain
                 , boost::proto::arity_of<parent>::type::value
                 , expression<Expr, Result> const
                 >
      ()(*this, sz);
    }

    protected:
    //==========================================================================
    // For any given Xpr expression, if Xpr matches the current grammar, then
    // the assignment is evaluated. Otherwise, a static assertion is triggered
    // in a separate function to prevent error cascading.
    // process exists in non-const and const flavors to support the same const
    // and non-const variants of operator=
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE void process( Xpr const& xpr )
    {
      typedef typename boost::proto::result_of::as_expr<Xpr>::type lhs_type;
      process ( xpr
              , typename boost::proto::matches< lhs_type
                                              , container::grammar>::type()
              );
    }

    template<class Xpr> BOOST_FORCEINLINE void process( Xpr const& xpr ) const
    {
      typedef typename boost::proto::result_of::as_expr<Xpr>::type lhs_type;
      process ( xpr
              , typename boost::proto::matches< lhs_type
                                              , container::grammar>::type()
              );
    }

    //==========================================================================
    // Specialization for error cascading prevention
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    void process( Xpr const& xpr, boost::mpl::true_ const& )
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
    }

    template<class Xpr> BOOST_FORCEINLINE
    void process( Xpr const& xpr, boost::mpl::true_ const& ) const
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
    }

    template<class Xpr> BOOST_FORCEINLINE
    void process( Xpr const&, boost::mpl::false_ const& ) const
    {
      //========================================================================
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      // If this static assert triggers, an invalid expression was assigned to
      // a NT2 reference-like expression. Check your code for bad expression
      // construction.
      //                 ****NT2_EXPRESSION_GRAMMAR_MISMATCH****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (sizeof(Xpr) == 0)
                          , NT2_EXPRESSION_GRAMMAR_MISMATCH
                          , (Xpr)
                          );
    }

    private:
    extent_type size_;
  };
} }

#endif
