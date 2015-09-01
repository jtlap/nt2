//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cdf2rdf.hpp>

#include <nt2/include/functions/nseig.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/cdf2rdf.hpp>
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


NT2_TEST_CASE_TPL(cdf2rdf, NT2_REAL_TYPES)
{
  using nt2::cdf2rdf;
  using nt2::mtimes;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  t_t b =      nt2::cons<T>(nt2::of_size(3, 3), 0, 1, 0, -1, 0, 0, 0, 0, 1);
  ct_t cw;
  ct_t cv;
  nt2::tie(cv, cw) = nseig(b);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes( cv, cw)-mtimes(b, cv))), 8*nt2::Eps<T>());
  t_t w, v;
  nt2::tie(v, w) = cdf2rdf(cv, cw);
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(mtimes( v, w)-mtimes(b, v))), 8*nt2::Eps<T>());
}

