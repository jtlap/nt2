//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BLAS_FUNCTIONS_UTILS_BLAS_UNBAND_H_HPP_INCLUDED
#define NT2_BLAS_FUNCTIONS_UTILS_BLAS_UNBAND_H_HPP_INCLUDED

#include <nt2/blas/functions/unband_h.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace blas { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( unband_h_, tag::cpu_,
                              (SHAPE)(UPLO)(IN)(KD),
                              (scalar_<int8_<SHAPE>>)
                              (scalar_<int8_<UPLO>>)
                              (scalar_<unspecified_<IN>>)
                              (scalar_<integer_<KD>>)// kq
                            )
  {
    typedef IN result_type;
    BOOST_FORCEINLINE result_type operator()( const SHAPE&
                                            , const UPLO&
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
                              ((node_<A1,nt2::tag::unband_h_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,2>::type         in_type;
    typedef typename  meta::strip<in_type>::type                           sin_type;
    typedef typename  sin_type::value_type                                   type_t;
    typedef typename meta::is_complex<type_t>::type                      is_cmplx_t;
    result_type operator()(A0& out, const A1& in) const
    {
      char shape   =  boost::proto::child_c<0>(in);
      char uplo    =  boost::proto::child_c<1>(in);
      in_type& tin =  boost::proto::child_c<2>(in);
      int kd       =  boost::proto::child_c<3>(in);
      int n = width(tin);
      out = zeros(of_size(n, n), meta::as_<type_t>());
      if (shape == 'H' || shape == 'h')
      {
        inner_unpack(tin, out, n, kd, uplo, is_cmplx_t());
      }
      else
      {
        inner_unpack(tin, out, n, kd, uplo, boost::mpl::false_());
      }
      return out;
    }
  private :
    template<class I, class O>
    BOOST_FORCEINLINE static void inner_unpack(const I& in, O& out,
                                                int n, int kd,
                                                char uplo,  const boost::mpl::false_ &)
    {
      if (uplo == 'U' || uplo ==  'u')
      {
        for (int j = 1;  j <= n;  ++j)
        {
          auto ii = _(max(1, j-kd), j);
          out(ii, j) = in(kd+1+ii-j, j);
          out(j, ii) = in(kd+1+ii-j, j);
        }
      }
      else
      {
        for (int j = 1;  j <= n;  ++j)
        {
          auto ii = _(j, min(n, j+kd));
          out(ii, j) = in(1+ii-j, j);
          out(j, ii) = in(1+ii-j, j);
        }
      }
    }
    template<class I, class O>
    BOOST_FORCEINLINE static  void inner_unpack(const I& in, O& out,
                                                int n, int kd,
                                                char uplo,  const boost::mpl::true_ &)
    {
      if (uplo == 'U' || uplo ==  'u')
      {
        for (int j = 1;  j <= n;  ++j)
        {
          auto ii = _(max(1, j-kd), j);
          out(ii, j) = in(kd+1+ii-j, j);
          out(j, ii) = conj(in(kd+1+ii-j, j));
        }
      }
      else
      {
        for (int j = 1;  j <= n;  ++j)
        {
          auto ii = _(j, min(n, j+kd));
          out(ii, j) = in(1+ii-j, j);
          out(j, ii) = conj(in(1+ii-j, j));
        }
      }
    }
  };

}  } }

#endif
