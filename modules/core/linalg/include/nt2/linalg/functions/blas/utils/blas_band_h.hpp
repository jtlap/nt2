//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UTILS_BLAS_BAND_H_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UTILS_BLAS_BAND_H_HPP_INCLUDED

#include <nt2/linalg/functions/blas_band_h.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( blas_band_h_, tag::cpu_,
                              (UPLO)(IN)(KD),
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<unspecified_<IN> >)
                              (scalar_<integer_<KD>>)// kd
                            )
  {
    typedef IN result_type;
    BOOST_FORCEINLINE result_type operator()( const UPLO&
                                            , const IN& in
                                            , const KD&
                                            )
    {
      return in;
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::blas_band_h_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,1>::type         in_type;
    typedef typename  meta::strip<in_type>::type                           sin_type;
    typedef typename  sin_type::value_type                                   type_t;
    typedef nt2::container::table<type_t>                                     tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      char uplo =  boost::proto::child_c<0>(in);
      int kd =  boost::proto::child_c<2>(in);
      in_type& tin =  boost::proto::child_c<1>(in);
      int n = width(tin);
      out = zeros(of_size(kd+1, n), meta::as_<type_t>());
      if (uplo == 'U' || uplo == 'u')
      {
        for(int j=1; j <= n; ++j)
        {
          int m = kd+1-j;
          auto ii = _( max(1,j-kd), j);
          out( m + ii, j ) = tin( ii, j);
        }
      }
      else
      {
        for(int j=1; j <= n; ++j)
        {
          int m = 1-j;
          auto ii = _( j, min(n,j+kd));
          out( m + ii, j ) = tin( ii, j  );
        }
      }
      return out;
    }
  };

} }

#endif
