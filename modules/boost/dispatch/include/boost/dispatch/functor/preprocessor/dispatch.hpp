//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
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

#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define BOOST_DISPATCH_DISPATCH_TYPE_TPL(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_DISPATCH_TYPE(z,n,t) class BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_DISPATCH_ARG(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t)) const
#define BOOST_DISPATCH_DISPATCH_TAG(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))

#define BOOST_DISPATCH_NS_(s,data,elem) elem ::
#define BOOST_DISPATCH_NS(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_NS_, ~, seq)

#define BOOST_DISPATCH_CLOSE_(s,data,elem) }
#define BOOST_DISPATCH_CLOSE(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_CLOSE_, ~, seq)

#define BOOST_DISPATCH_REOPEN_(s,data,elem) namespace elem {
#define BOOST_DISPATCH_REOPEN(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_REOPEN_, ~, seq)

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
#define BOOST_DISPATCH_REGISTER_DISPATCH(NS,Tag,Site,Types,Seq)                      \
BOOST_DISPATCH_CLOSE(NS)                                                             \
namespace boost { namespace dispatch { namespace meta {                              \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types)> \
BOOST_DISPATCH_FORCE_INLINE BOOST_DISPATCH_NS(NS)                                    \
implement< BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)       \
                                      , BOOST_DISPATCH_DISPATCH_TAG,Seq))            \
    , Site                                                                \
    >                                                                     \
dispatching( Tag, Site                                      \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)      \
        , adl_helper = adl_helper()                                       \
        )                                                                 \
{                                                                         \
  BOOST_DISPATCH_NS(NS)                                                              \
  implement< BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)     \
                                        , BOOST_DISPATCH_DISPATCH_TAG,Seq)           \
                                        )                                 \
    , Site                                                                \
    > that;                                                               \
  return that;                                                            \
}                                                                         \
} } }                                                                     \
BOOST_DISPATCH_REOPEN(NS)                                                 \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_TPL(NS,Tag,Site,Types,Seq)                      \
BOOST_DISPATCH_CLOSE(NS)                                                                 \
namespace boost { namespace dispatch { namespace meta {                                  \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE_TPL,Types)> \
BOOST_DISPATCH_FORCE_INLINE                                                              \
BOOST_DISPATCH_NS(NS)                                                                    \
implement < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq)            \
          , BOOST_DISPATCH_DISPATCH_TAG,Seq))                                            \
          , Site                                                              \
          >                                                                   \
dispatching( BOOST_DISPATCH_PP_STRIP(Tag), Site                            \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)          \
        , adl_helper = adl_helper()                                           \
        )                                                                     \
{                                                                             \
  BOOST_DISPATCH_NS(NS)                                                                  \
  implement < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq)          \
            , BOOST_DISPATCH_DISPATCH_TAG,Seq))                                          \
            , Site                                                            \
            >  that;                                                          \
  return that;                                                                \
}                                                                             \
} } }                                                                         \
BOOST_DISPATCH_REOPEN(NS)                                                     \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_IF(NS,Tag,Site,Types,Cond,Ret,Seq)            \
BOOST_DISPATCH_CLOSE(NS)                                                               \
namespace boost { namespace dispatch { namespace meta {                                \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types)>   \
BOOST_DISPATCH_FORCE_INLINE                                                            \
typename boost::enable_if < BOOST_DISPATCH_PP_STRIP(Cond)                              \
                          , BOOST_DISPATCH_NS(NS) implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>    \
                          >::type                                           \
dispatching( Tag, Site                                        \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)        \
        , adl_helper = adl_helper()                                         \
        )                                                                   \
{                                                                           \
  BOOST_DISPATCH_NS(NS) implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>  that; \
  return that;                                                              \
}                                                                           \
} } }                                                                       \
BOOST_DISPATCH_REOPEN(NS)                                                   \
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
#define BOOST_DISPATCH_REGISTER_DISPATCH_IF_TPL(NS,Tag,Site,Types,Cond,Ret,Seq)          \
BOOST_DISPATCH_CLOSE(NS)                                                                 \
namespace boost { namespace dispatch { namespace meta {                                  \
template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE_TPL,Types)> \
BOOST_DISPATCH_FORCE_INLINE                                                              \
typename boost::enable_if < BOOST_DISPATCH_PP_STRIP(Cond)                                \
                          , boost::dispatch::meta::implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>      \
                          >::type                                             \
dispatching ( Tag, Site                                         \
            , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),BOOST_DISPATCH_DISPATCH_ARG,Seq)      \
            , adl_helper = adl_helper()                                       \
            )                                                                 \
{                                                                             \
  BOOST_DISPATCH_NS(NS) implement<BOOST_DISPATCH_PP_STRIP(Ret),Site>  that;   \
  return that;                                                                \
}                                                                             \
} } }                                                                         \
BOOST_DISPATCH_REOPEN(NS)                                                     \
/**/

#endif
