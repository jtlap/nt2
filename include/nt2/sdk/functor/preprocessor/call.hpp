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
#include <nt2/sdk/errors/static_assert.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/array/data.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <nt2/sdk/functor/meta/find_type.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// call::operator() result type
////////////////////////////////////////////////////////////////////////////////
#define NT2_CALL_RETURN_TYPE(N)                   \
boost::result_of<call(BOOST_PP_ENUM_PARAMS(N,A))> \
/**/

////////////////////////////////////////////////////////////////////////////////
// Main functor entry point:
// Takes care of retrieving the function result, making it const and prepare
// the operator() prototype.
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_CALL(N)                                     \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                \
typename NT2_CALL_RETURN_TYPE(N)::type                          \
operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) ) const  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Boilerplate macro to start an eval() overload with N parameters and
// dispatching for types belonging to Set
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_CALL_EVAL_IF(N,Set)                               \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                      \
typename NT2_CALL_RETURN_TYPE(N)::type                                \
eval( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a), Set* const&) const  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Default dispatch implementation. When a type don't trigger any regular
// overload, we trigger a static assertion;
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_CALL_DEFAULT(N)                                 \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                    \
typename NT2_CALL_RETURN_TYPE(N)::type                              \
eval( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT )  \
    , nt2::functors::empty_* const&                                 \
    ) const                                                         \
{                                                                   \
  NT2_STATIC_ASSERT( (false)                                        \
                    , UNSUPPORTED_TYPE_FOR_FUNCTOR_CALL             \
                    , (BOOST_PP_ENUM_PARAMS(N,A))                   \
                    );                                              \
  return typename NT2_CALL_RETURN_TYPE(N)::type();                  \
}                                                                   \
/**/

////////////////////////////////////////////////////////////////////////////////
// Main functor entry point which performs type matching and forwarding to the
// proper overload. Also takes care of unsupported types.
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTOR_CALL_DISPATCH(N,Type,Sets)                    \
NT2_FUNCTOR_CALL(N)                                               \
{                                                                 \
  typedef typename NT2_CALL_RETURN_TYPE(N)::type return_type;     \
  typedef typename meta::find_type< Type                          \
                                  , BOOST_PP_TUPLE_REM_CTOR (     \
                                        BOOST_PP_ARRAY_SIZE(Sets) \
                                      , BOOST_PP_ARRAY_DATA(Sets) \
                                                            )     \
                                  , empty_>::type* fnd_;          \
  return eval( BOOST_PP_ENUM_PARAMS(N,a),fnd_(0));                \
}                                                                 \
private:                                                          \
NT2_FUNCTOR_CALL_DEFAULT(N)                                       \
public:                                                           \
/**/

#endif
