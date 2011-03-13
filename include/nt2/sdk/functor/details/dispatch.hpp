/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/details/decltype.hpp>
#include <nt2/sdk/meta/hierarchy.hpp>
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// Local macro to generate the fall-through dispatch overload
// What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
// it is mandated by the standard so ADL kicks in on resolving calls to
// dispatching without having to order them BEFORE the actual dispatch_call
// class definitions. Without it, the whole system brittles.
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) meta::unknown_<BOOST_PP_CAT(A,n)> const&
#define M1(z,n,t) typename meta::hierarchy_of<BOOST_PP_CAT(A,n)>::type

#define NT2_DEFAULT_UNKNOWN_DISPATCH(z,n,t)                                     \
template<class Tag, class Site, BOOST_PP_ENUM_PARAMS(n,class A)>                \
nt2::ext::call<Tag(tag::unknown_),Site,tag::error_with(BOOST_PP_ENUM(n,M1,~))>  \
dispatching ( Tag const&, Site const&, BOOST_PP_ENUM(n,M0,~)                    \
            , adl_helper = adl_helper()                                         \
            );                                                                  \
/**/

#define NT2_DISPATCH_TYPE_TPL(z,n,t) NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define NT2_DISPATCH_TYPE(z,n,t) class NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define NT2_DISPATCH_ARG(z,n,t) nt2::meta::NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t)) const&
#define NT2_DISPATCH_TAG(z,n,t) typename nt2::meta::NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))::type

////////////////////////////////////////////////////////////////////////////////
// User macro to register an accepted overload for function Tag on Site
// for a list of hierarchy specified by (Types,Seq)
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_DISPATCH(Tag,Site,Types,Seq)                           \
namespace nt2 { namespace meta {                                            \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE,Types)>   \
nt2::ext::                                                                  \
call<NT2_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_TAG,Seq)),Site>  \
dispatching( Tag const&, Site const&                                        \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)        \
        , adl_helper = adl_helper()                                         \
        );                                                                  \
} }                                                                         \
/**/

////////////////////////////////////////////////////////////////////////////////
// User macro to register an accepted overload for function Tag on Site
// for a list of hierarchy specified by (Types,Seq) where Types is a fully
// qualified tempalte parameter (like class A0 instead of A0). This is mainly
// used for non type tempalte parameters appearing in some tag or site.
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_DISPATCH_TPL(Tag,Site,Types,Seq)                         \
namespace nt2 { namespace meta {                                              \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE_TPL,Types)> \
nt2::ext::                                                                    \
call<NT2_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_TAG,Seq)),Site>    \
dispatching( NT2_PP_STRIP(Tag) const&, Site const&                                          \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)          \
        , adl_helper = adl_helper()                                           \
        );                                                                    \
} }                                                                           \
/**/

////////////////////////////////////////////////////////////////////////////////
// User macro to register an accepted overload for function Tag on Site
// for a list of hierarchy specified by (Types,Seq) under the static condition
// Cond. If COnd is satisfied, then Ret will be used as a dispatching strategy
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_DISPATCH_IF(Tag,Site,Types,Cond,Ret,Seq)               \
namespace nt2 { namespace meta {                                            \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE,Types)>   \
typename boost::enable_if < NT2_PP_STRIP(Cond)                              \
                          , nt2::ext::call<NT2_PP_STRIP(Ret),Site>          \
                          >::type                                           \
dispatching( Tag const&, Site const&                                        \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)        \
        , adl_helper = adl_helper()                                         \
        );                                                                  \
} }                                                                         \
/**/

////////////////////////////////////////////////////////////////////////////////
// User macro to register an accepted overload for function Tag on Site
// for a list of hierarchy specified by (Types,Seq) where Types is a list of
// fully qualified tempalte parameters under the static condition
// Cond. If COnd is satisfied, then Ret will be used as a dispatching strategy
////////////////////////////////////////////////////////////////////////////////
#define NT2_REGISTER_DISPATCH_IF_TPL(Tag,Site,Types,Cond,Ret,Seq)             \
namespace nt2 { namespace meta {                                              \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE_TPL,Types)> \
typename boost::enable_if < NT2_PP_STRIP(Cond)                                \
                          , nt2::ext::call<NT2_PP_STRIP(Ret),Site>            \
                          >::type                                             \
dispatching ( Tag const&, Site const&                                         \
            , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)      \
            , adl_helper = adl_helper()                                       \
            );                                                                \
} }                                                                           \
/**/
namespace nt2 { namespace meta
{
  struct adl_helper {};

  //////////////////////////////////////////////////////////////////////////////
  // Default dispatch overload set for catching calls to unsupported functor
  // overload or unregistered types.
  //////////////////////////////////////////////////////////////////////////////
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),NT2_DEFAULT_UNKNOWN_DISPATCH,~)
} }

#undef M0
#undef M1
#undef NT2_DEFAULT_UNKNOWN_DISPATCH

////////////////////////////////////////////////////////////////////////////////
// Local macro to generate the dispatch selector
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) BOOST_PP_CAT(elem,n)()
/**/

#define NT2_DISPATCH_TYPES(z,n,t)                                               \
typedef typename strip<BOOST_PP_CAT(A,n)>::type BOOST_PP_CAT(arg,n);            \
typedef typename hierarchy_of<BOOST_PP_CAT(arg,n)>::type  BOOST_PP_CAT(elem,n); \
/**/

#define NT2_DISPATCH_CALL(z,n,t)                                        \
template<class Tag, BOOST_PP_ENUM_PARAMS(n,class A), class Site>        \
struct dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)), Site>              \
{                                                                       \
  BOOST_PP_REPEAT(n,NT2_DISPATCH_TYPES,~)                               \
  NT2_DECLTYPE( dispatching ( Tag(), Site()                             \
                            , BOOST_PP_ENUM(n,M0,~)                     \
                            , adl_helper()                              \
                            )                                           \
              , type );                                                 \
};                                                                      \
/**/

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //////////////////////////////////////////////////////////////////////////////
  template<class Sig, class Site> struct dispatch_call;
  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),NT2_DISPATCH_CALL,~)
} }

#undef M0
#undef NT2_DISPATCH_TYPES_TPL
#undef NT2_DISPATCH_TYPES
#undef NT2_DISPATCH_CALL

#endif
