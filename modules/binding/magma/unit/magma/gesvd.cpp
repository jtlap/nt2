//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(gesvd, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;


  t_t in  = nt2::ones (1000, 1000, nt2::meta::as_<T>())
          + T(10)*nt2::eye  (1000,1000, nt2::meta::as_<T>());

  char jobu =  'N';
  char jobvt = 'N';

  t_t s,vt,u;

  s.resize(nt2::of_size(std::min(1000,1000),1));

  nt2_la_int p = 5;
  p = nt2::gesvd( boost::proto::value(in),boost::proto::value(s)
                , boost::proto::value(u),boost::proto::value(vt),jobu,jobvt);

  NT2_TEST_EQUAL(p, 0);
}


NT2_TEST_CASE_TPL(gesvdc, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           t_t;


  t_t in  = nt2::ones (1000, 1000, nt2::meta::as_<cT>())
          + T(10)*nt2::eye  (1000,1000, nt2::meta::as_<cT>());

  char jobu =  'N';
  char jobvt = 'N';

  t_t vt,u;
  nt2::table<T> s;

  s.resize(nt2::of_size(std::min(1000,1000),1));

  nt2_la_int p = 5;
  p = nt2::gesvd( boost::proto::value(in),boost::proto::value(s)
                , boost::proto::value(u),boost::proto::value(vt),jobu,jobvt);

  NT2_TEST_EQUAL(p, 0);
}
