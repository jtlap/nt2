//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for registering a functor overload
 */

#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define NT2_DISPATCH_TYPE_TPL(z,n,t) NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define NT2_DISPATCH_TYPE(z,n,t) class NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define NT2_DISPATCH_ARG(z,n,t) nt2::meta::NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t)) const&
#define NT2_DISPATCH_TAG(z,n,t) typename nt2::meta::NT2_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))::type

//==============================================================================
/*!
 * Register an overload for function Tag on Site when called on types belonging
 * to the hierarchies specified by (Types,Seq). Once defined, such an overload
 * has to be implemented.
 *
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define NT2_REGISTER_DISPATCH(Tag,Site,Types,Seq)                           \
namespace nt2 { namespace meta {                                            \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE,Types)>   \
nt2::ext::                                                                  \
call< NT2_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)              \
                                      , NT2_DISPATCH_TAG,Seq))              \
    , Site                                                                  \
    >                                                                       \
dispatching( Tag const&, Site const&                                        \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)        \
        , adl_helper = adl_helper()                                         \
        );                                                                  \
} }                                                                         \
/**/

//==============================================================================
/*!
 * Register an overload for function Tag on Site when called on types belonging
 * to the hierarchies specified by (Types,Seq) where Seq can contain non-type
 * hierarchy template parameters. Once defined, such an overload has to be
 * implemented.
 *
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template parameters used in the hierarchy
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
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

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq) ad dif the compile
 * time condition \c Cond is verified. Once defined, such an overload
 * has to be implemented using the prorotype specified by \c Ret.
 *
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
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

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters and if the compile
 * time condition \c Cond is verified. Once defined, such an overload
 * has to be implemented using the prorotype specified by \c Ret.
 *
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
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

#endif
