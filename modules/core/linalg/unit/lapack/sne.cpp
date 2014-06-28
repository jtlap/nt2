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
#include <nt2/include/functions/tri1l.hpp>
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
  size_t m=25,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr);
  b.resize( nt2::of_size(m,4) );

  for(size_t i = 2; i <= 4 ; ++i)
  {
    b( _ , i) = b(_ , 1) ;
  }
  b.resize( nt2::of_size(m+5,4) );
  t_t s1 = nt2::zeros(m+m,m, nt2::meta::as_<T>());

  s1( _(7,m+7) , _(5,n+5) ) = nt2::mcsne(    a( _(1,m), _ ) , b( _(1,m) , _) );
  t_t s2 = nt2::linsolve( a( _(1,m), _ ) , b( _(1,m) , _) );

  NT2_TEST_ULP_EQUAL( s1( _(7,n+6) , _(5,8) ) , s2( _(1,n) , _ ), T(100));
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

  NT2_TEST_ULP_EQUAL(s1(_(1,3)), s2(_(1,3)), T(100));
}
