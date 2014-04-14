//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/geqrf.hpp>
#include <nt2/include/functions/geqp3.hpp>
#include <nt2/include/functions/mqr.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL(mqr_non_square, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;
  t_t tau_q3,tau_rf, r_p3, r_rf,c,c1;

  t_i jpvt = nt2::zeros(10,1, nt2::meta::as_<nt2_la_int>());

  c = nt2::eye(15,15,nt2::meta::as_<T>());
  c1 = nt2::eye(15,15,nt2::meta::as_<T>());

  t_t q  =  T(10)* nt2::ones (15, 10, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (15, 10, nt2::meta::as_<T>());

  t_t q_p3(q);
  t_t q_rf(q);

  nt2::geqrf(boost::proto::value(q_rf),boost::proto::value(tau_rf));
  nt2::geqp3(boost::proto::value(q_p3), boost::proto::value(jpvt), boost::proto::value(tau_q3));

  nt2::mqr(boost::proto::value(q_rf), boost::proto::value(tau_rf), boost::proto::value(c) );
  nt2::mqr(boost::proto::value(q_p3), boost::proto::value(tau_q3),boost::proto::value(c1));


  r_rf = nt2::triu ( q_rf );
  r_p3 = nt2::triu ( q_p3 );

  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d, nt2::meta::as_<T>());

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = T(1);


  NT2_TEST_ULP_EQUAL(q, mtimes(c,r_rf) , T(10));
  NT2_TEST_ULP_EQUAL(mtimes(q,p), mtimes(c1,r_p3) , T(10));

}



NT2_TEST_CASE_TPL(mqr_square, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;
  t_t tau_q3,tau_rf, r_p3, r_rf,c,c1;

  t_i jpvt = nt2::zeros(10,1, nt2::meta::as_<nt2_la_int>());

  c = nt2::eye(10,10,nt2::meta::as_<T>());
  c1 = nt2::eye(10,10,nt2::meta::as_<T>());

  t_t q  =  T(10)* nt2::ones (10, 10, nt2::meta::as_<T>())
           - T(4)*nt2::eye  (10, 10, nt2::meta::as_<T>());

  t_t q_p3(q);
  t_t q_rf(q);

  nt2::geqrf(boost::proto::value(q_rf),boost::proto::value(tau_rf));
  nt2::geqp3(boost::proto::value(q_p3), boost::proto::value(jpvt), boost::proto::value(tau_q3));

  nt2::mqr(boost::proto::value(q_rf), boost::proto::value(tau_rf), boost::proto::value(c) );
  nt2::mqr(boost::proto::value(q_p3), boost::proto::value(tau_q3),boost::proto::value(c1));

  r_rf = nt2::triu ( q_rf );
  r_p3 = nt2::triu ( q_p3 );

  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d, nt2::meta::as_<T>());

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = T(1);


  NT2_TEST_ULP_EQUAL(q, mtimes(c,r_rf) , T(10));
  NT2_TEST_ULP_EQUAL(mtimes(q,p), mtimes(c1,r_p3) , T(10));


}

NT2_TEST_CASE_TPL(mqr_non_square_complex, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           t_t;
  typedef nt2::table<nt2_la_int>   t_i;
  t_t tau_q3,tau_rf, r_p3, r_rf,c,c1;

  t_i jpvt = nt2::zeros(10,1, nt2::meta::as_<nt2_la_int>());

  c = nt2::eye(15,15,nt2::meta::as_<cT>());
  c1 = nt2::eye(15,15,nt2::meta::as_<cT>());

  t_t q  =  T(10)* nt2::ones (15, 10, nt2::meta::as_<cT>())
           - T(4)*nt2::eye  (15, 10, nt2::meta::as_<cT>());

  t_t q_p3(q);
  t_t q_rf(q);

  nt2::geqrf(boost::proto::value(q_rf),boost::proto::value(tau_rf));
  nt2::geqp3(boost::proto::value(q_p3), boost::proto::value(jpvt), boost::proto::value(tau_q3));

  nt2::mqr(boost::proto::value(q_rf), boost::proto::value(tau_rf), boost::proto::value(c) );
  nt2::mqr(boost::proto::value(q_p3), boost::proto::value(tau_q3),boost::proto::value(c1));


  r_rf = nt2::triu ( q_rf );
  r_p3 = nt2::triu ( q_p3 );

  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d, nt2::meta::as_<cT>());

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = T(1);


  NT2_TEST_ULP_EQUAL(q, mtimes(c,r_rf) , T(10));
  NT2_TEST_ULP_EQUAL(mtimes(q,p), mtimes(c1,r_p3) , T(10));

}



NT2_TEST_CASE_TPL(mqr_square_complex, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           t_t;
  typedef nt2::table<nt2_la_int>   t_i;
  t_t tau_q3,tau_rf, r_p3, r_rf,c,c1;

  t_i jpvt = nt2::zeros(10,1, nt2::meta::as_<nt2_la_int>());

  c = nt2::eye(10,10,nt2::meta::as_<cT>());
  c1 = nt2::eye(10,10,nt2::meta::as_<cT>());

  t_t q  =  T(10)* nt2::ones (10, 10, nt2::meta::as_<cT>())
           - T(4)*nt2::eye  (10, 10, nt2::meta::as_<cT>());

  t_t q_p3(q);
  t_t q_rf(q);

  nt2::geqrf(boost::proto::value(q_rf),boost::proto::value(tau_rf));
  nt2::geqp3(boost::proto::value(q_p3), boost::proto::value(jpvt), boost::proto::value(tau_q3));

  nt2::mqr(boost::proto::value(q_rf), boost::proto::value(tau_rf), boost::proto::value(c) );
  nt2::mqr(boost::proto::value(q_p3), boost::proto::value(tau_q3),boost::proto::value(c1));

  r_rf = nt2::triu ( q_rf );
  r_p3 = nt2::triu ( q_p3 );

  std::size_t d = nt2::numel(jpvt);
  t_t p = nt2::zeros(d, nt2::meta::as_<cT>());

  for(std::size_t i = 1; i<= d;++i)
   p(jpvt(i),i) = T(1);


  NT2_TEST_ULP_EQUAL(q, mtimes(c,r_rf) , T(10));
  NT2_TEST_ULP_EQUAL(mtimes(q,p), mtimes(c1,r_p3) , T(10));


}
