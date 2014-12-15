//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UTILS_BLAS_UNBAND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UTILS_BLAS_UNBAND_HPP_INCLUDED

#include <nt2/linalg/functions/blas_unband.hpp>
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

  BOOST_DISPATCH_IMPLEMENT  ( blas_unband_, tag::cpu_,
                              (IN)(M)(KL)(KU),
                              (scalar_<unspecified_<IN> >)
                              (scalar_<integer_<M >>)// m
                              (scalar_<integer_<KL>>)// kl
                              (scalar_<integer_<KU>>)// ku
                            )
  {
    typedef IN result_type;
    BOOST_FORCEINLINE result_type operator()( const IN& in
                                            , const M&
                                            , const KL&
                                            , const KU&
                                            )
    {
      return in;
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::blas_unband_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type         in_type;
    typedef typename  meta::strip<in_type>::type                           sin_type;
    typedef typename  sin_type::value_type                                   type_t;
    typedef nt2::container::table<type_t>                                     tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      int m  =  boost::proto::child_c<1>(in);
      int kl =  boost::proto::child_c<2>(in);
      int ku =  boost::proto::child_c<3>(in);
      in_type& tin =  boost::proto::child_c<0>(in);
      int n = width(tin);
      out = zeros(of_size(m, n), meta::as_<type_t>());
      for(int j=1; j <= n; ++j)
      {
        auto ii =  _(max(1, j-ku), min(m, j+kl));
        int k = ku+1-j;
        out(ii, j) = tin(ii+k,j);
      }
      return out;
    }
  };

} }

#endif
