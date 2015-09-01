//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rsf2csf.hpp>

#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/rsf2csf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/triu.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/linalg/options.hpp>


NT2_TEST_CASE_TPL(rsf2csf, NT2_REAL_TYPES)
{
  using nt2::rsf2csf;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b =      nt2::cons<T>(nt2::of_size(3, 3), 0, 1, 0, -1, 0, 0, 0, 0, 1);
  NT2_DISPLAY(b);
  t_t u;
  t_t t;
  nt2::tie(u, t) = schur(b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes( u, t)-mtimes(b, u))), 8*nt2::Eps<T>());
  ct_t cu, ct;
  nt2::tie(cu, ct) = rsf2csf(u, t);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes( cu, ct)-mtimes(b, cu))), 8*nt2::Eps<T>());

}

