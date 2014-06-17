//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/linalg/details/utility/llspgen.hpp>
#include <nt2/include/functions/sne.hpp>
#include <nt2/include/functions/csne.hpp>
#include <nt2/include/functions/mcsne.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(sne, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;

  size_t m=20,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr,nt2::meta::as_<T>());

  t_t s1 = nt2::sne(a,b);
  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1(_(1,n)), s2(_(1,n)), T(300));
}


NT2_TEST_CASE_TPL(csne, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;

  size_t m=20,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr,nt2::meta::as_<T>());

  t_t s1 = nt2::csne(a,b);

  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1, s2(_(1,n)), T(100));
}


NT2_TEST_CASE_TPL(msne, (double) )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;
  size_t m=20,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr);
  t_t s1 = nt2::mcsne(a,b);
  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1, s2(_(1,n)), T(100));
}

NT2_TEST_CASE_TPL(msne_complex, (double) )
{
  using nt2::_;

  typedef std::complex<T>          cT;
  typedef nt2::table<cT>           t_t;

  t_t a = nt2::cons<cT>(nt2::of_size(4,3)
                    ,cT(2,0),cT(1,0),cT(1,0)
                    ,cT(1,0),cT(2,0),cT(2,0)
                    ,cT(2,0),cT(5,0),cT(7,0)
                    ,cT(2,0),cT(4,0),cT(1,0)
                    );
  t_t b = nt2::cons<cT>(nt2::of_size(4,1)
                    ,cT(1,0),cT(2,0),cT(5,0),cT(2,0));

  t_t s1 = nt2::mcsne(a,b);
  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1, s2(_(1,3)), T(100));
}

// #include <sys/time.h>
// #include <iostream>

// NT2_TEST_CASE_TPL(msne_test, (double) )
// {
//   using nt2::_;

//   typedef nt2::table<T>           t_t;

//   t_t a,x,r,b;
//   clock_t start,end;
//   size_t m=20,n=10,q=6,nr=1;

//   nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr);
//   double norma = nt2::norm(a);


//   start = clock();
//   t_t s1 = nt2::mcsne(a,b);
//   end = clock();
//   std::cout << "mcsne: " << (end-start)/10000000. << std::endl;
//   start = clock();
//   t_t s2 = nt2::linsolve(a,b);
//   end = clock();
//   std::cout << "dgelsy: " << (end-start)/10000000. << std::endl;


//   nt2::table<double> e = b - nt2::mtimes(a,s1);
//   double nres = norm(nt2::mtimes(nt2::trans(a),e))/(norm(e)*norma);
//   std::cout << "mcsne nres: " << nres << std::endl;

//   e = b - nt2::mtimes(a,s2(_(1,n)) );
//   nres = norm(nt2::mtimes(nt2::trans(a),e))/(norm(e)*norma);
//   std::cout << "dgelsy nres: " << nres << std::endl;

//   NT2_TEST_ULP_EQUAL(s1, s2(_(1,n)), T(10000000));
// }
