//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::linspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::linspace_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::linspace_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::linspace_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::linspace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::linspace_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::linspace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::linspace_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::linspace_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::linspace_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::linspace_>)
                    );
}

NT2_TEST_CASE_TPL( linspace, NT2_REAL_TYPES )
{
  using nt2::meta::value_type_;

  nt2::table<T> ref(nt2::of_size(1,100));
  for(int i=1;i<=100;++i)
    ref(i) = T(0) + (T(1)/99)*(i-1);

  NT2_TEST_EXPR_TYPE( (nt2::linspace(T(0),T(1)))
                    , (value_type_<boost::mpl::_>)
                    , (T)
                    );

  nt2::table<T> x = nt2::linspace(T(0),T(1));
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,100) );
  NT2_TEST_ULP_EQUAL( x, ref, 15 );

  for(int i=1;i<=100;++i)
    ref(i) = T(1) + (T(-1)/99)*(i-1);

  nt2::table<T> xr = nt2::linspace(T(1),T(0));
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,100) );
  NT2_TEST_ULP_EQUAL( xr, ref, 15 );
}

NT2_TEST_CASE_TPL( linspace_with_size, NT2_REAL_TYPES )
{
  using nt2::meta::value_type_;

  nt2::table<T> ref(nt2::of_size(1,7));
  for(int i=1;i<=7;++i)
    ref(i) = T(0) + (T(1)/6)*(i-1);

  NT2_TEST_EXPR_TYPE( (nt2::linspace(T(0),T(1),7))
                    , (value_type_<boost::mpl::_>)
                    , (T)
                    );

  nt2::table<T> x = nt2::linspace(T(0),T(1),7);
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  for(int i=1;i<=7;++i)
    ref(i) = T(1) + (T(-1)/6)*(i-1);

  nt2::table<T> xr = nt2::linspace(T(1),T(0),7);
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );

  nt2::table<T> xn1 = nt2::linspace(T(0),T(9),1);
  NT2_TEST_EQUAL( xn1.extent(), nt2::of_size(1,1 ) );
  NT2_TEST_EQUAL( xn1(1), 9 );
}

NT2_TEST_CASE_TPL( linspace_worst, NT2_REAL_TYPES )
{
  for(size_t i = 0; i < 8; ++i)
  {
    nt2::table<T> z = nt2::linspace(T(-100), nt2::predecessor(T(0)), 100+i);
    NT2_TEST(nt2::globalall(z));
    z(nt2::end_) = T(nt2::predecessor(T(0)));
    NT2_TEST(nt2::globalall(z));
  }
}

NT2_TEST_CASE_TPL( linspace_best, NT2_REAL_TYPES )
{
  nt2::table<T> z = nt2::linspace(T(-1), T(1), 257);
  nt2::table<T> ref(nt2::of_size(1,257));

  for(size_t i = 1; i <= 257; ++i)
    ref(i) =  T(-1)+T(i-1)/128;

  NT2_TEST_EQUAL(z,ref);
}
NT2_TEST_CASE_TPL( linspace_cplx, (double)(float) )
{
  typedef std::complex<T> cT; 
  nt2::table<cT> z = nt2::linspace(cT(-1, -1), cT(1, 1), 257);
  nt2::table<cT> ref(nt2::of_size(1,257));

  for(size_t i = 1; i <= 257; ++i)
    ref(i) =  cT(-1, -1)+cT(T(i-1)/128, T(i-1)/128);

  NT2_TEST_EQUAL(z,ref);
}
