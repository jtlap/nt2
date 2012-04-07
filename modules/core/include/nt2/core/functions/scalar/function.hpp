//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/type_traits/is_const.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/include/vector_tie.hpp>

namespace nt2 { namespace ext
{
#define M0(z,n,t) (BOOST_PP_CAT(I,n))
#define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(I,n)> >)

#define M2(z,n,t)                                                               \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_                      \
                          , (A0)(S)(N)BOOST_PP_REPEAT(n,M0,~)                   \
                          , ((expr_ < table_<unspecified_<A0>, S>               \
                                    , nt2::tag::terminal_, N                    \
                                    >                                           \
                            ))                                                  \
                            BOOST_PP_REPEAT(n,M1,~)                             \
                          )                                                     \
{                                                                               \
  typedef typename boost::remove_const<A0>::type                  base;         \
  typedef typename boost::mpl::if_< boost::is_const<A0>                         \
                                  , typename base::const_reference              \
                                  , typename base::reference                    \
                                  >::type                         result_type;  \
  typedef typename base::index_type::type                         idx_t;        \
                                                                                \
  BOOST_FORCEINLINE result_type                                                 \
  operator()(A0& a0, BOOST_PP_ENUM_BINARY_PARAMS(n,I,i) ) const                 \
  {                                                                             \
    return  boost::proto::value(a0)                                             \
            [ nt2::sub2ind( a0.extent()                                         \
                          , boost::fusion::                                     \
                            vector_tie(BOOST_PP_ENUM_PARAMS(n,i))               \
                          , idx_t()                                             \
                          )                                                     \
            ];                                                                  \
  }                                                                             \
};                                                                              \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M2,~)

#undef M0
#undef M1
#undef M2
} }

#endif
