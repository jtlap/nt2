//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_EXPR_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_EXPR_CHOL_HPP_INCLUDED

#include <nt2/toolbox/linalg/functions/chol.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/toolbox/linalg/functions/factorizations/chol.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0>))
                              ((node_ < A1
                                      , nt2::tag::chol_
                                      , boost::mpl::long_<1>
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      // Copy data in a0 first
      a0 = boost::proto::child_c<0>(a1);

      // Factorize in place in a0 and affect the result
      a0 = factorization::chol(a0,'U',in_place_).upper_result();
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0>))
                              ((node_ < A1
                                      , nt2::tag::chol_
                                      , boost::mpl::long_<2>
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      // Copy data in a0 first
      a0 = boost::proto::child_c<0>(a1);

      // Factorize in place and affect the result
      a0 = factorization::chol(a0,'L',in_place_).lower_result();
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)
                            , ((node_<A0, elementwise_<T0>, N0>))
                              ((node_ < A1
                                      , nt2::tag::chol_
                                      , boost::mpl::long_<1>
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      // Copy data in a0 first
      a0 = boost::proto::child_c<0>(a1);

      // Factorize in place in a0 and affect the result
      a0 = factorization::chol( a0, 'U', in_place_ ).upper_result();
      return a0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)
                            , ((node_<A0, elementwise_<T0>, N0>))
                              ((node_ < A1
                                      , nt2::tag::chol_
                                      , boost::mpl::long_<2>
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      // Copy data in a0 first
      a0 = boost::proto::child_c<0>(a1);

      // Factorize in place in a0 and affect the result
      a0 = factorization::chol(a0, 'L', in_place_).lower_result();
      return a0;
    }
  };
} }

#endif
