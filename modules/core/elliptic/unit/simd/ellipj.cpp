//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/elliptic/include/functions/scalar/ellipj.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/eps.hpp>

#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( ellipj_real__1_0,  NT2_SIMD_REAL_TYPES)
{

  using nt2::ellipj;
  using nt2::tag::ellipj_;
  using nt2::table;
  using nt2::splat;
  using boost::fusion::tuple;
  using boost::simd::native;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;

  T u[] = {nt2::Zero<T>(), nt2::Half<T>(),nt2::One<T>(), nt2::Pio_2<T>(),  nt2::Two<T>()};
  T m[] = {T(0), T(0.25), T(0.5), T(0.75), T(1)};
  size_t N =  sizeof(u)/sizeof(T);
  table<T>sn = nt2::reshape(nt2::cons<T>(
                             T(0.0),   T(0.479425538604203),   T(0.841470984807897),   T(1.000000000000000),   T(0.909297426825682),
                             T(0.0),   T(0.475082936028536),   T(0.822635578129862),   T(0.995043241129267),   T(0.962898177598278),
                             T(0.0),   T(0.470750473655657),   T(0.803001824895644),   T(0.979739559290852),   T(0.994662325358018),
                             T(0.0),   T(0.466428449803636),   T(0.782632847839289),   T(0.953740968539957),   T(0.996920661888935),
                             T(0.0),   T(0.462117157260010),   T(0.761594155955765),   T(0.917152335667274),   T(0.964027580075817)
                           ), 5, 5);
  table<T>cn = nt2::reshape(nt2::cons<T>(
                             T(1.0),   T(0.877582561890373),   T(0.540302305868140),   T(0.000000000000000),   T(-0.416146836547142),
                             T(1.0),   T(0.879941022963758),   T(0.568568998095171),   T(0.099443191234811),   T(-0.269864965451086),
                             T(1.0),   T(0.882266394890440),   T(0.595976567672141),   T(0.200275799737678),   T(-0.103183615527762),
                             T(1.0),   T(0.884558930322778),   T(0.622483594549257),   T(0.300629614190727),   T(0.078416796025652),
                             T(1.0),   T(0.886818883970074),   T(0.648054273663885),   T(0.398536815338387),   T(0.265802228834080)
                           ), 5, 5);
  table<T>dn = nt2::reshape(nt2::cons<T>(
                             T(1.0),   T(1.000000000000000),   T(1.000000000000000),   T(1.000000000000000),   T(1.000000000000000),
                             T(1.0),   T(0.971377398838179),   T(0.911492005669132),   T(0.867451576210880),   T(0.876474058312326),
                             T(1.0),   T(0.942972425777386),   T(0.823161001631596),   T(0.721148526990303),   T(0.710861047784087),
                             T(1.0),   T(0.914785972733695),   T(0.735264829236530),   T(0.563723002631921),   T(0.504590819797781),
                             T(1.0),   T(0.886818883970074),   T(0.648054273663885),   T(0.398536815338387),   T(0.265802228834080)
                           ), 5, 5);

#ifndef BOOST_SIMD_NO_INVALIDS
   T ui[] = {nt2::Inf<T>(), nt2::Minf<T>(),nt2::Nan<T>()};
   table<T> sni = nt2::reshape(nt2::cons<T>(
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                   1,    -1,   nt2::Nan<T>()
                               ), 3, 5);
   table<T> cni = nt2::reshape(nt2::cons<T>(
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 0,     0,   nt2::Nan<T>()
                               ), 3, 5);
   table<T> dni = nt2::reshape(nt2::cons<T>(
                                 1,     1,     1,
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 nt2::Nan<T>(),   nt2::Nan<T>(),   nt2::Nan<T>(),
                                 0,     0,   nt2::Nan<T>()
                               ), 3, 5);
#endif

   vT s, c, d;
   for(size_t i=1; i <= N; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       ellipj(splat<vT>(u[i-1]), splat<vT>(m[j-1]),nt2::_(), s, c, d);
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dn(i, j)), 13);
     }
   }
#ifndef BOOST_SIMD_NO_INVALIDS
   for(size_t i=1; i <= 3; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       ellipj(splat<vT>(ui[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>(), s, c, d);
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dni(i, j)), 1);
     }
   }
#endif

   for(size_t i=1; i <= N; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       s = ellipj(splat<vT>(u[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>(), c, d);
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dn(i, j)), 13);
     }
   }
#ifndef BOOST_SIMD_NO_INVALIDS
   for(size_t i=1; i <= 3; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       s = ellipj(splat<vT>(ui[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>(), c, d);
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dni(i, j)), 1);
     }
   }
#endif

   for(size_t i=1; i <= N; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::vector_tie(s, c) = ellipj(splat<vT>(u[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>(), d);
       std::cout << s << " -<s c >- " << c << std::endl;
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dn(i, j)), 13);
     }
   }
#ifndef BOOST_SIMD_NO_INVALIDS
   for(size_t i=1; i <= 3; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::vector_tie(s, c) = ellipj(splat<vT>(ui[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>(), d);
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dni(i, j)), 1);
     }
   }
#endif

   for(size_t i=1; i <= N; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::vector_tie(s, c, d) = ellipj(splat<vT>(u[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>());
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dn(i, j)), 13);
     }
   }
#ifndef BOOST_SIMD_NO_INVALIDS
   for(size_t i=1; i <= 3; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::vector_tie(s, c, d) = ellipj(splat<vT>(ui[i-1]), splat<vT>(m[j-1]),nt2::Eps<T>());
       NT2_TEST_ULP_EQUAL(s, splat<vT>(sni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(c, splat<vT>(cni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(d, splat<vT>(dni(i, j)), 1);
     }
   }
#endif

   for(size_t i=1; i <= N; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::tuple<vT, vT, vT> t = ellipj(splat<vT>(u[i-1]), splat<vT>(m[j-1]));
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<0>(t), splat<vT>(sn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<1>(t), splat<vT>(cn(i, j)), 13);
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<2>(t), splat<vT>(dn(i, j)), 13);
     }

   }
#ifndef BOOST_SIMD_NO_INVALIDS
   for(size_t i=1; i <= 3; ++i)
   {
     for(size_t j=1; j <= N; ++j)
     {
       boost::fusion::tuple<vT, vT, vT> t = ellipj(splat<vT>(ui[i-1]), splat<vT>(m[j-1]));
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<0>(t), splat<vT>(sni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<1>(t), splat<vT>(cni(i, j)), 1);
       NT2_TEST_ULP_EQUAL(boost::fusion::at_c<2>(t), splat<vT>(dni(i, j)), 1);
     }
   }
#endif

}
