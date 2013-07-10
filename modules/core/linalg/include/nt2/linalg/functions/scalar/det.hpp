//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_DET_HPP_INCLUDED
#include <nt2/linalg/functions/det.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/issquare.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_floating<type_t>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(issquare(a0), "det for non square matrix");
      return nt2::details::lu_result<A0>(a0).det();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::det_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

} }

#endif
