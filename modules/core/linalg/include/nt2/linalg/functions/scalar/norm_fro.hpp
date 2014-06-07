//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_NORM_fro_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_NORM_fro_HPP_INCLUDED
#include <nt2/linalg/functions/norm_fro.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/property_of.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_fro_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return norm2(a0(nt2::_));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_fro_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)

                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const & a0,  A1 const&)
    {
      return norm2(a0(nt2::_));
    }

  };
} }

#endif
