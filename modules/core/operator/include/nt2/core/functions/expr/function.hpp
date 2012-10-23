//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/include/functions/aggregate.hpp>
#include <nt2/include/functions/globalfind.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/colon/category.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <boost/simd/sdk/meta/is_logical.hpp>
#include <boost/utility/enable_if.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_
                            , (A0)(I0)
                            , ((ast_<A0, nt2::container::domain>))(colon_<I0>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0& a0, I0 const& i0),
      nt2::colvect(a0)
    )
  };

  template<class A0, class T, class Dummy = void>
  struct function_find
  {
    typedef T const& type;
    static type call(A0&, T const& t)
    {
      return t;
    }
  };

  template<class A0, class T>
  struct function_find<A0, T, typename boost::enable_if< boost::simd::meta::is_logical<typename T::value_type> >::type>
  {
    typedef typename A0::value_type stype;
    typedef typename meta::as_index<stype>::type itype;
    typedef typename meta::call<tag::globalfind_(T const&, meta::as_<itype>)>::type type;
    static type call(A0&, T const& t)
    {
      return nt2::globalfind(t, meta::as_<itype>());
    }
  };

#define M1(z,n,t) (I##n)
#define M2(z,n,t) (unspecified_<I##n>)
#define M3(z,n,t) typename function_find<A0, I##n>::type
#define M4(z,n,t) function_find<A0, I##n>::call(a0, i##n)

#define M0(z,n,t)                                                             \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_                    \
                          , (A0)BOOST_PP_REPEAT(n,M1,~)                       \
                          , ((ast_<A0, nt2::container::domain>))BOOST_PP_REPEAT(n,M2,~)                 \
                          )                                                   \
{                                                                             \
  typedef typename meta::                                                     \
          call< tag::aggregate_(BOOST_PP_ENUM(n, M3, ~))                      \
              >::type                                             indices;    \
  typedef typename nt2::make_size<n>::type                      size_type;    \
                                                                              \
  typedef typename  boost::proto::result_of::                                 \
                    make_expr < nt2::tag::function_                           \
                              , container::domain                             \
                              , A0&                                           \
                              , indices                                       \
                              , box<size_type>                                \
                              >::type                           result_type;  \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(A0& a0, BOOST_PP_ENUM_BINARY_PARAMS(n,const I,& i) ) const       \
  {                                                                           \
    size_type compact(a0.extent());                                           \
    return boost::proto::make_expr<tag::function_,container::domain>          \
                                  ( boost::reference_wrapper<A0>(a0)          \
                                  , nt2::aggregate(BOOST_PP_ENUM(n,M4,~))     \
                                  , nt2::boxify(compact)                      \
                                  );                                          \
  }                                                                           \
};                                                                            \
/**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

#undef M0
#undef M1
#undef M2
#undef M3
#undef M4
} }

#endif
