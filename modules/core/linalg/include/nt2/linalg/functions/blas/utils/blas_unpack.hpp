//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UTILS_UNPACK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UTILS_UNPACK_HPP_INCLUDED

#include <nt2/linalg/functions/blas_unpack.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( blas_unpack_, tag::cpu_,
                              (UPLO)(SHAPE)(IN),
                              (scalar_<int8_<UPLO>>)// uplo
                              (scalar_<int8_<SHAPE>>)// shape
                              (scalar_<unspecified_<IN> >)
                            )
  {
    typedef IN result_type;
    BOOST_FORCEINLINE result_type operator()( const UPLO&
                                            , const SHAPE&
                                            , const IN& in
                                            )
    {
      return in;
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::blas_unpack_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,2>::type         in_type;
    typedef typename  meta::strip<in_type>::type                           sin_type;
    typedef typename  sin_type::value_type                                   type_t;
    typedef typename meta::is_complex<type_t>::type                      is_cmplx_t;
    result_type operator()(A0& out, const A1& in) const
    {
      char uplo =  boost::proto::child_c<0>(in);
      char shape =  boost::proto::child_c<1>(in);
      in_type& tin =  boost::proto::child_c<2>(in);
      int n = iround(sqrt(oneplus(Eight<int>()*numel(tin)))) >> 1;
      NT2_DISPLAY(n);
      out.resize(of_size(n, n));
      if (shape != 'T' && shape != 't')
      {
        out.resize(of_size(n, n));
        inner_unpack_sh(tin, out, n, uplo, shape);
      }
      else
      {
        out = zeros(n, n, meta::as_<type_t>());
        inner_unpack_t(tin, out, n, uplo);
      }
      return out;
    }
  private:
    template < class I, class O>
    BOOST_FORCEINLINE static  void inner_unpack_t(const I& in, O& out, int n, char uplo)
    {
      if (uplo == 'U' || uplo ==  'u')
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          out(_(1, i), i) = in(_(k, k+i-1));
          k+= i;
        }
      }
      else
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          int p =  n-i+1;
          out(_(i, n), i) = in(_(k, k+p-1));
          k+= p;
        }
      }
    }
    template < class I, class O>
    BOOST_FORCEINLINE static  void inner_unpack_sh(const I& in, O& out, int n, char uplo,  char shape)
    {
      if (shape == 'H' || shape == 'h')
      {
        inner_unpack(in, out, n, uplo, is_cmplx_t());
      }
      else
      {
        inner_unpack(in, out, n, uplo, boost::mpl::false_());
      }
    }

    template < class I, class O>
    BOOST_FORCEINLINE static  void inner_unpack(const I& in, O& out, int n, char uplo,  const boost::mpl::false_ &)
    {
      if (uplo == 'U' || uplo ==  'u')
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          out(_(1, i), i) = in(_(k, k+i-1));
          out(i, _(1, i)) = in(_(k, k+i-1));
          k+= i;
        }
      }
      else
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          int p =  n-i+1;
          out(_(i, n), i) = in(_(k, k+p-1));
          out(i, _(i, n)) = in(_(k, k+p-1));
          k+= p;
        }
      }
    }

    template < class I, class O>
    BOOST_FORCEINLINE static  void inner_unpack(const I& in, O& out, int n, char uplo,  const boost::mpl::true_ &)
    {
      if (uplo == 'U' || uplo ==  'u')
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          out(_(1, i), i) = in(_(k, k+i-1));
          out(i, _(1, i)) = conj(in(_(k, k+i-1)));
          k+= i;
        }
      }
      else
      {
        int k = 1;
        for (int i = 1;  i <= n;  ++i)
        {
          int p =  n-i+1;
          out(_(i, n), i) = in(_(k, k+p-1));
          out(i, _(i, n)) = conj(in(_(k, k+p-1)));
          k+= p;
        }
      }
    }
  };
} }

#endif
