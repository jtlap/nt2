//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( cat_scalar, (float)(double) )
{
  typedef std::complex<T> cT;
  {
    nt2::table<cT> d = nt2::cat(1, cT(3), cT(5));
    NT2_TEST_EQUAL(d(1,1),cT(3));
    NT2_TEST_EQUAL(d(2,1),cT(5));
  }
  {
    nt2::table<cT> d = nt2::cat(2, cT(3), cT(5));
    NT2_TEST_EQUAL(d(1,1),cT(3));
    NT2_TEST_EQUAL(d(1,2),cT(5));
  }
  {
    nt2::table<cT> d = nt2::cat(3, cT(3), cT(5));
    NT2_TEST_EQUAL(d(1,1,1),cT(3));
    NT2_TEST_EQUAL(d(1,1,2),cT(5));
  }
  {
    nt2::table<cT> d = nt2::cat(4, cT(3), cT(5));
    NT2_TEST_EQUAL(d(1,1,1,1),cT(3));
    NT2_TEST_EQUAL(d(1,1,1,2),cT(5));
  }
}

NT2_TEST_CASE_TPL( cat, (float)(double) )
{
  typedef std::complex<T> cT;
  {
    nt2::table<cT,nt2::_2D> a = nt2::rif(nt2::of_size(2, 3), nt2::meta::as_<cT>());
    nt2::table<cT,nt2::_2D> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<cT>());
    nt2::table<cT,nt2::_2D> d = cat(1, a, b);
    NT2_TEST_EQUAL(a, d(nt2::_(1u, size(a, 1)),nt2::_ ));
    NT2_TEST_EQUAL(b, d(nt2::_(size(a, 1)+1, nt2::end_),nt2::_));
  }

  {
    nt2::table<cT> a = nt2::rif(nt2::of_size(3, 2), nt2::meta::as_<cT>());
    nt2::table<cT> b = nt2::cif(nt2::of_size(3, 4), nt2::meta::as_<cT>());
    nt2::table<cT> d = cat(2, a, b);
    NT2_TEST_EQUAL(a, d(nt2::_, nt2::_(1u, size(a, 2))));
    NT2_TEST_EQUAL(b, d(nt2::_, nt2::_(size(a, 2)+1, nt2::end_)));
  }

  {
    nt2::table<cT> a = nt2::rif(nt2::of_size(4, 3), nt2::meta::as_<cT>());
    nt2::table<cT> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<cT>());
    nt2::table<cT> d = cat(3, a, b);
    NT2_TEST_EQUAL(a, d(nt2::_,nt2::_,1));
    NT2_TEST_EQUAL(b, d(nt2::_,nt2::_,2));
  }

  {
    nt2::table<cT> a = nt2::rif(nt2::of_size(4, 3), nt2::meta::as_<cT>());
    nt2::table<cT> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<cT>());
    nt2::table<cT> d = cat(4, a, b);
    NT2_TEST_EQUAL(a, d(nt2::_,nt2::_,nt2::_,1));
    NT2_TEST_EQUAL(b, d(nt2::_,nt2::_,nt2::_,2));
  }
}
