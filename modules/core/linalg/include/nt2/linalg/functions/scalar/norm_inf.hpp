//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_NORM_INF_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_NORM_INF_HPP_INCLUDED
#include <nt2/linalg/functions/norm_inf.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/property_of.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_inf_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0) || isvector(a0), "a0 is not matrix nor vector");
      typedef typename details::is_definitely_vector<typename A0::extent_type>::type choice_t;
      return eval(a0, choice_t());
    }

    BOOST_FORCEINLINE type_t
    eval(A0 const& a0, boost::mpl::true_ const &) const
    {
      return nt2::globalmax(nt2::abs(a0));
    }
    BOOST_FORCEINLINE type_t
    eval(A0 const& a0, boost::mpl::false_ const &) const
    {
      if (isvector(a0))
      {
        return nt2::globalmax(nt2::abs(a0));
      }
      else
      {
        return nt2::globalmax(nt2::asum1(a0, 2));
      }
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_inf_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)

                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

     BOOST_FORCEINLINE
     result_type operator()(A0 const& a0
                           ,  const nt2::policy<ext::matrix_> &
                           ) const
     {
       return nt2::globalmax(nt2::asum1(a0, 2));
     }

     BOOST_FORCEINLINE
     result_type operator()(A0 const& a0
                           , const nt2::policy<ext::vector_> &
                           ) const
     {
       return nt2::globalmax(nt2::abs(a0));
     }

     template < class T >
     BOOST_FORCEINLINE result_type operator()(const A0 & a0
                                             , const T &
                                             ) const
    {
      BOOST_MPL_ASSERT_MSG((false), UNKNOWN_OPTION_TO_NORM_INF, (T));
      return Nan<result_type>();
    }

  };
} }

#endif
