//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_QR1UP_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_GENERAL_QR1UP_HPP_INCLUDED

#include <nt2/linalg/functions/qr1up.hpp>
#include <nt2/linalg/details/qrupdate/declare/qr1up.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{

//---------------------------------------------Real-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( qr1up_, tag::cpu_
                            , (Q)(S0)(R)(S1)(U)(S2)(V)(S3)
                            , ((container_<nt2::tag::table_,  double_<Q>, S0 >)) //q
                              ((container_<nt2::tag::table_,  double_<R>, S1 >)) //r
                              ((container_<nt2::tag::table_,  double_<U>, S2 >)) //u
                              ((container_<nt2::tag::table_,  double_<V>, S3 >)) //v
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()( Q& q, R& r, U& u, V& v) const
     {
       typedef typename Q::value_type                                        value_t;
       nt2_la_int  m = nt2::height(q);
       nt2_la_int  n = nt2::width(r);
       nt2_la_int  k = nt2::height(r);
       nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
       nt2_la_int  ldr = nt2::max(r.leading_size(), One<size_t>());
       container::table<value_t> w(of_size(2*k));
       NT2_F77NAME(dqr1up) (&m, &n, &k, q.data(), &ldq, r.data(), &ldr, u.data(), v.data(), w.data());
     }
  };

//---------------------------------------------Real-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( qr1up_, tag::cpu_
                            , (Q)(S0)(R)(S1)(U)(S2)(V)(S3)
                            , ((container_<nt2::tag::table_,  single_<Q>, S0 >)) //q
                              ((container_<nt2::tag::table_,  single_<R>, S1 >)) //r
                              ((container_<nt2::tag::table_,  single_<U>, S2 >)) //u
                              ((container_<nt2::tag::table_,  single_<V>, S3 >)) //v
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()( Q& q, R& r, U& u, V& v) const
     {
       typedef typename Q::value_type                                        value_t;
       nt2_la_int  m = nt2::height(q);
       nt2_la_int  n = nt2::width(r);
       nt2_la_int  k = nt2::height(r);
       nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
       nt2_la_int  ldr = nt2::max(r.leading_size(), One<size_t>());
       container::table<value_t> w(of_size(2*k));
       NT2_F77NAME(sqr1up) (&m, &n, &k, q.data(), &ldq, r.data(), &ldr, u.data(), v.data(), w.data());
     }
  };


//---------------------------------------------Complex-single------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( qr1up_, tag::cpu_
                            , (Q)(S0)(R)(S1)(U)(S2)(V)(S3)
                            , ((container_<nt2::tag::table_,  complex_<single_<Q>>, S0 >)) //q
                              ((container_<nt2::tag::table_,  complex_<single_<R>>, S1 >)) //r
                              ((container_<nt2::tag::table_,  complex_<single_<U>>, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<single_<V>>, S3 >)) //v
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()( Q& q, R& r, U& u, V& v) const
     {
       typedef typename Q::value_type                                        value_t;
       typedef typename meta::as_real<value_t>::type                        rvalue_t;
       nt2_la_int  m = nt2::height(q);
       nt2_la_int  n = nt2::width(r);
       nt2_la_int  k = nt2::height(r);
       nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
       nt2_la_int  ldr = nt2::max(r.leading_size(), One<size_t>());
       container::table<value_t> w(of_size(k));
       container::table<rvalue_t> rw(of_size(k));
       NT2_F77NAME(sqr1up) (&m, &n, &k, q.data(), &ldq, r.data(), &ldr, u.data(), v.data(), w.data(), rw.data());
     }
  };

//---------------------------------------------Complex-double------------------------------------------------//

  BOOST_DISPATCH_IMPLEMENT  ( qr1up_, tag::cpu_
                            , (Q)(S0)(R)(S1)(U)(S2)(V)(S3)
                            , ((container_<nt2::tag::table_,  complex_<double_<Q>>, S0 >)) //q
                              ((container_<nt2::tag::table_,  complex_<double_<R>>, S1 >)) //r
                              ((container_<nt2::tag::table_,  complex_<double_<U>>, S2 >)) //u
                              ((container_<nt2::tag::table_,  complex_<double_<V>>, S3 >)) //v
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()( Q& q, R& r, U& u, V& v) const
     {
       typedef typename Q::value_type                                        value_t;
       typedef typename meta::as_real<value_t>::type                        rvalue_t;
       nt2_la_int  m = nt2::height(q);
       nt2_la_int  n = nt2::width(r);
       nt2_la_int  k = nt2::height(r);
       nt2_la_int  ldq = nt2::max(q.leading_size(), One<size_t>());
       nt2_la_int  ldr = nt2::max(r.leading_size(), One<size_t>());
       container::table<value_t> w(of_size(k));
       container::table<rvalue_t> rw(of_size(k));
       NT2_F77NAME(sqr1up) (&m, &n, &k, q.data(), &ldq, r.data(), &ldr, u.data(), v.data(), w.data(), rw.data());
     }
  };
} }

#endif
