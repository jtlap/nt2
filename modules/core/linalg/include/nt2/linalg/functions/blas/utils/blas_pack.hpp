//==============================================================================
//         Copyright 2013 - 2014   Jean-Thierry Lapresté
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_BLAS_UTILS_PACK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_BLAS_UTILS_PACK_HPP_INCLUDED

#include <nt2/linalg/functions/blas_pack.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/constants/eight.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( blas_pack_, tag::cpu_,
                              (UPLO)(IN),
                              (scalar_<int8_<UPLO>>)// uplo
                               (scalar_<unspecified_<IN> >)
                            )
  {
    typedef IN result_type;
    BOOST_FORCEINLINE result_type operator()( const UPLO&
                                            , const IN& in
                                            )
    {
      return in;
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::blas_pack_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,1>::type         in_type;
    typedef typename  meta::strip<in_type>::type                           sin_type;
    typedef typename  sin_type::value_type                                   type_t;
    typedef nt2::container::table<type_t>                                     tab_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>       o_semantic;
    result_type operator()(A0& out, const A1& in) const
    {
      char uplo =  boost::proto::child_c<0>(in);
      in_type& tin =  boost::proto::child_c<1>(in);
      size_t n = height(tin);
      out.resize(of_size(1, (n*(n+1) >> 1)));
      if (uplo == 'U' || uplo ==  'u')
      {
        size_t k = 1;
        for (size_t i = 1;  i <= n;  ++i)
        {
          out(_(k, k+i-1)) = rowvect(tin(_(1, i), i));
          k+= i;
        }
      }
      else
      {
        size_t k = 1;
        for (size_t i = 1;  i <= n;  ++i)
        {
          size_t p =  n-i+1;
          out(_(k, k+p-1)) = rowvect(tin(_(i, n), i));
          k+= p;
        }
      }
      return out;
    }
  };

} }

#endif
