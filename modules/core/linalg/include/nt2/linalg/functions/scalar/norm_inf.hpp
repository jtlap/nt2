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
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/property_of.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_inf_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (isvector(a0))
      {
        return nt2::globalmax(nt2::abs(a0));
      }
      else if (ismatrix(a0))
      {
        return nt2::globalmax(nt2::asum1(a0, 2));
      }
      else
      {
        BOOST_ASSERT_MSG(false, "a0 is not matrix nor vector");
        return Nan<result_type>();
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

    NT2_FUNCTOR_CALL(2)
    {
      return eval(a0, a1);
    }

    BOOST_FORCEINLINE result_type eval( const A0 & a0
                                      , const nt2::policy<ext::matrix_> &) const
    {
      return nt2::globalmax(nt2::asum1(a0, 2));
    }

    BOOST_FORCEINLINE result_type eval( const A0 & a0
                                      , const nt2::policy<ext::vector_> &) const
    {
      return nt2::globalmax(nt2::abs(a0));
    }

    template < class T >
    BOOST_FORCEINLINE result_type eval(const A0 & a0, const T &)
    {
      BOOST_ASSERT_MSG(false, "unknown option to norm_inf");
      return Nan<result_type>();
    }

  };
} }

#endif
