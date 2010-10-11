/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various macro for boilerplating call<> code writing
// Documentation: http://nt2.lri.fr/sdk/functor/macros/call.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <nt2/sdk/functor/meta/find_type.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// operator() result type
////////////////////////////////////////////////////////////////////////////////
#define NT2_RETURN_TYPE(N,C)                                                  \
std::tr1                                                                      \
   ::result_of<C(BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT))> \
/**/

////////////////////////////////////////////////////////////////////////////////
// operator() result type for call<Tag,Cat,Info>
////////////////////////////////////////////////////////////////////////////////
#define NT2_CALL_RETURN_TYPE(N) NT2_RETURN_TYPE(N,call)

////////////////////////////////////////////////////////////////////////////////
// Main functor entry point:
// Takes care of retrieving the function result, making it const and prepare
// the operator() prototype.
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR(N,C)                                        \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                \
typename NT2_RETURN_TYPE(N,C)::type                             \
operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) ) const  \
/**/

#define NT2_FUNCTOR_CALL(N) NT2_FUNCTOR(N,call)

////////////////////////////////////////////////////////////////////////////////
// Boilerplate macro to start an eval() overload with N parameters and
// dispatching for types belonging to Set
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_EVAL_IF(N,Set,C)              \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline  \
typename NT2_RETURN_TYPE(N,C)::type               \
eval( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a)  \
    , NT2_PP_STRIP(Set)* const&) const            \
/**/

#define NT2_FUNCTOR_CALL_EVAL_IF(N,Set) NT2_FUNCTOR_EVAL_IF(N,Set,call)

////////////////////////////////////////////////////////////////////////////////
// Default dispatch implementation. When a type don't trigger any regular
// overload, we trigger a static assertion;
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_DEFAULT(N,C)                                    \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                    \
typename NT2_RETURN_TYPE(N,C)::type                                 \
eval( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT )  \
    , nt2::functors::empty_* const&                                 \
    ) const                                                         \
{                                                                   \
  NT2_STATIC_ASSERT( (false)                                        \
                    , UNSUPPORTED_TYPE_FOR_FUNCTOR_CALL             \
                    , (BOOST_PP_ENUM_PARAMS(N,A))                   \
                    );                                              \
  return typename NT2_RETURN_TYPE(N,C)::type();                     \
}                                                                   \
/**/

#define NT2_FUNCTOR_CALL_DEFAULT(N) NT2_FUNCTOR_DEFAULT(N,call)

#define NT2_FUNCTOR_SETS(z,n,t) NT2_PP_STRIP( BOOST_PP_ARRAY_ELEM(n,t) )

////////////////////////////////////////////////////////////////////////////////
// Main functor entry point which performs type matching and forwarding to the
// proper overload. Also takes care of unsupported types.
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_DISPATCH(N,Type,Sets,C)                                   \
NT2_FUNCTOR(N,C)                                                              \
{                                                                             \
  typedef typename NT2_RETURN_TYPE(N,C)::type return_type;                    \
  typedef typename meta::find_type< NT2_PP_STRIP(Type)                        \
                                  , BOOST_PP_ENUM ( BOOST_PP_ARRAY_SIZE(Sets) \
                                                  , NT2_FUNCTOR_SETS          \
                                                  , Sets                      \
                                                  )                           \
                                  , functors::empty_>::type* fnd_;            \
  return eval( BOOST_PP_ENUM_PARAMS(N,a),fnd_(0));                            \
}                                                                             \
private:                                                                      \
NT2_FUNCTOR_DEFAULT(N,C)                                                      \
public:                                                                       \
/**/

#define NT2_FUNCTOR_CALL_DISPATCH(N,Type,Sets)  \
NT2_FUNCTOR_DISPATCH(N,Type,Sets,call)          \
/**/

#endif
