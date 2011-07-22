//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for registering a functor overload
 */

#include <boost/dispatch/extension/parameters.hpp>
#include <boost/dispatch/details/preprocessor.hpp>
#include <boost/simd/sdk/config/attributes.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define BOOST_DISPATCH_DISPATCH_TYPE_TPL(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_DISPATCH_TYPE(z,n,t) class BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_DISPATCH_ARG(z,n,t) boost::dispatch::meta::BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t)) const&
#define BOOST_DISPATCH_DISPATCH_TAG(z,n,t) boost::dispatch::meta::BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))

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
#define BOOST_DISPATCH_REGISTER_DISPATCH(Tag,Site,Types,Seq)                         \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types)> \
BOOST_SIMD_FORCE_INLINE boost::dispatch::meta::                                      \
implement< BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)       \
                                      , BOOST_DISPATCH_DISPATCH_TAG,Seq))            \
    , Site                                                                \
    >                                                                     \
dispatching( Tag const&, Site const&                                      \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)      \
        , adl_helper = adl_helper()                                       \
        )                                                                 \
{                                                                         \
  boost::dispatch::meta::                                                            \
  implement< BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)     \
                                        , BOOST_DISPATCH_DISPATCH_TAG,Seq)           \
                                        )                                 \
    , Site                                                                \
    > that;                                                               \
  return that;                                                            \
}                                                                         \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_TPL(Tag,Site,Types,Seq)                         \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE_TPL,Types)> \
BOOST_SIMD_FORCE_INLINE                                                                  \
boost::dispatch::meta::                                                                  \
implement < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq)            \
          , BOOST_DISPATCH_DISPATCH_TAG,Seq))                                            \
          , Site                                                              \
          >                                                                   \
dispatching( BOOST_DISPATCH_PP_STRIP(Tag) const&, Site const&                            \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)          \
        , adl_helper = adl_helper()                                           \
        )                                                                     \
{                                                                             \
  boost::dispatch::meta::                                                                \
  implement < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq)          \
            , BOOST_DISPATCH_DISPATCH_TAG,Seq))                                          \
            , Site                                                            \
            >  that;                                                          \
  return that;                                                                \
}                                                                             \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_IF(Tag,Site,Types,Cond,Ret,Seq)               \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types)>   \
BOOST_SIMD_FORCE_INLINE                                                            \
typename boost::enable_if < BOOST_DISPATCH_PP_STRIP(Cond)                              \
                          , boost::dispatch::meta::implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>    \
                          >::type                                           \
dispatching( Tag const&, Site const&                                        \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)        \
        , adl_helper = adl_helper()                                         \
        )                                                                   \
{                                                                           \
  boost::dispatch::meta::implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>  that;                       \
  return that;                                                              \
}                                                                           \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_IF_TPL(Tag,Site,Types,Cond,Ret,Seq)             \
namespace boost { namespace dispatch { namespace meta {                                              \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE_TPL,Types)> \
BOOST_SIMD_FORCE_INLINE                                                              \
typename boost::enable_if < BOOST_DISPATCH_PP_STRIP(Cond)                                \
                          , boost::dispatch::meta::implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>      \
                          >::type                                             \
dispatching ( Tag const&, Site const&                                         \
            , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)      \
            , adl_helper = adl_helper()                                       \
            )                                                                 \
{                                                                             \
  boost::dispatch::meta::implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>  that;                         \
  return that;                                                                \
}                                                                             \
} } }                                                                           \
/**/

#endif
