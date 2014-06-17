//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_MCSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_MCSNE_HPP_INCLUDED

#include <nt2/linalg/functions/mcsne.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/constants/eps.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

#include <nt2/core/container/table/table.hpp>

#include <nt2/table.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mcsne_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
    typedef typename boost::dispatch::meta::downgrade<ctype_t>::type dtype;
    typedef typename nt2::container::table<ctype_t> t_ct;
    typedef  t_ct                                      result_type;

     BOOST_FORCEINLINE result_type operator()(A0 const& a, A1 const& b) const
    {
      nt2_la_int lda = a.leading_size();
      nt2_la_int na = nt2::width(a);

      t_ct e,x;

      double eps = boost::simd::Eps<double>();
      double anrm = nt2::lange( boost::proto::value(a),'I');
      double cte = anrm*eps*nt2::sqrt( double(na));
      double xnrm, rnrm;

      nt2::container::table<dtype> sa,sb,sx;
      nt2::container::table<dtype,nt2::upper_triangular_> sr,sr1(nt2::of_size(na,na));
      sa = nt2::cast<dtype>(a);
      sr = nt2::qr(sa,nt2::no_pivot_);

      size_t size_n = sizeof(dtype)*(na);

      for(nt2_la_int i=0; i<na; i++)
      {
        std::memcpy(sr1.raw()+i*na, sr.raw()+i*lda, size_n);
      }

      boost::proto::value(sr).swap(boost::proto::value(sr1) );

      sx= nt2::mtimes(nt2::trans(sa),nt2::cast<dtype>(b));

      sx = nt2::linsolve(nt2::trans(sr),sx);
      sx = nt2::linsolve(sr,sx);

      x = nt2::cast<ctype_t>(sx);
      e = b - nt2::mtimes(a,x);

      for( size_t i = 1; i<=10;++i)
      {
        sx = nt2::cast<dtype> (nt2::mtimes(nt2::trans(a),e) ) ;

        sx = nt2::linsolve(nt2::trans(sr),sx);
        sx = nt2::linsolve(sr,sx);

        e = nt2::cast<ctype_t>(sx);
        rnrm = nt2::maximum(nt2::abs(e(_)));
        x = x + e;
        e = b - nt2::mtimes(a,x);

        xnrm = nt2::maximum(nt2::abs(x(_)));

        if(rnrm < xnrm*cte) { break; }
      }
      return x;
    }
  };

} }

#endif
