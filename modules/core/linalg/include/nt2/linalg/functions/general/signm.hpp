//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_SIGNM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_SIGNM_HPP_INCLUDED

#include <nt2/linalg/functions/signm.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/assert.hpp>

namespace nt2
{
  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( signm_, tag::cpu_
                              , (A0)
                              , (scalar_< unspecified_<A0> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(1)
      {
        return sign(a0);
      }
    };

    // signm tag only used for matrix
    template<class Domain, int N, class Expr>
    struct size_of<tag::signm_,Domain,N,Expr>
    {
      typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
      typedef _2D                                                      result_type;
      BOOST_FORCEINLINE result_type operator()(Expr& e) const
      {
        BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                         "signm needs a square matrix or a scalar");
        return nt2::extent(boost::proto::child_c<0>(e));
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                                , (A0)(A1)
                                , ((ast_<A0, nt2::container::domain>))
                                  ((node_<A1, nt2::tag::signm_, boost::mpl::long_<1>, nt2::container::domain>))
                                )
    {
    typedef void                                                    result_type;
    typedef typename A1::value_type                                  value_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename meta::as_real<value_type>::type                     r_type;
    typedef typename meta::as_complex<r_type>::type                   cplx_type;
    typedef table<cplx_type>                                             ctab_t;
    typedef typename A0::index_type                                  index_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, const A1& a1) const
    {
      compute_signm(boost::proto::child_c<0>(a1), a0);
    }

    private:
      template < class T >
      BOOST_FORCEINLINE static void compute_signm(const T& a0, A0& res)
      {
        ctab_t u, t;
        nt2::tie(u, t) = schur(a0, nt2::cmplx_);
        res =  mtimes(mtimes(u, from_diag(sign(diag_of(t)))), ctrans(u));
      }
    };
  }
}

#endif
