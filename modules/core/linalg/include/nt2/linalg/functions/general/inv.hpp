//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED

#include <nt2/linalg/functions/inv.hpp>
#include <nt2/include/functions/trf.hpp>
#include <nt2/include/functions/tri.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/sdk/meta/concrete.hpp>
//#include <nt2/sdk/error/warning.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::inv_
                                      , N , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_ASSERT_MSG( issquare(boost::proto::child_c<0>(in))
                      , "INV: Argument must be a square matrix"
                      );

      // If needed, resize
      out.resize(nt2::extent(in));

      // Reuse output memory if possible
      BOOST_AUTO_TPL( tmp, concrete(out) );
      tmp = boost::proto::child_c<0>(in);

      nt2::container::table<nt2_la_int> ip;
      nt2_la_int                        lapack_info;

      // Factorize A as L/U and call tri
      nt2::trf(tmp,ip);
      nt2::tri(tmp,ip);

    // NT2_WARNING( (rcond(boost::proto::child_c<0>(in),tmp) >= nt2::Eps<base_t>())
    //            , "INV: matrix is singular to machine precision."
    //            );

      return out = tmp;
    }
  };
} }

#endif
