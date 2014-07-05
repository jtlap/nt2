//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/mnormest.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(mnormest, NT2_REAL_TYPES)
{
  using nt2::mnormest;
  using nt2::tag::mnormest_;

  nt2::table<T> n = nt2::ones(10, 10, nt2::meta::as_<T>());
  size_t cnt;
  NT2_TEST_ULP_EQUAL(mnormest(n, T(1.0e-6)), nt2::Ten<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(mnormest(n, T(1.0e-6), cnt), nt2::Ten<T>(), 0.5);
  NT2_TEST_EQUAL(cnt, 2u);
  NT2_TEST_ULP_EQUAL(mnormest(n)           , nt2::Ten<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(mnormest(n, cnt)      , nt2::Ten<T>(), 0.5);
  NT2_TEST_EQUAL(cnt, 2u);
}
NT2_TEST_CASE_TPL(mnormest2, NT2_REAL_TYPES)
{
  nt2::table<T> n = nt2::cons(nt2::of_size(10, 10),
                              T(0.8147), T(0.1576), T(0.6557), T(0.7060), T(0.4387), T(0.2760), T(0.7513), T(0.8407), T(0.3517), T(0.0759),
                              T(0.9058), T(0.9706), T(0.0357), T(0.0318), T(0.3816), T(0.6797), T(0.2551), T(0.2543), T(0.8308), T(0.0540),
                              T(0.1270), T(0.9572), T(0.8491), T(0.2769), T(0.7655), T(0.6551), T(0.5060), T(0.8143), T(0.5853), T(0.5308),
                              T(0.9134), T(0.4854), T(0.9340), T(0.0462), T(0.7952), T(0.1626), T(0.6991), T(0.2435), T(0.5497), T(0.7792),
                              T(0.6324), T(0.8003), T(0.6787), T(0.0971), T(0.1869), T(0.1190), T(0.8909), T(0.9293), T(0.9172), T(0.9340),
                              T(0.0975), T(0.1419), T(0.7577), T(0.8235), T(0.4898), T(0.4984), T(0.9593), T(0.3500), T(0.2858), T(0.1299),
                              T(0.2785), T(0.4218), T(0.7431), T(0.6948), T(0.4456), T(0.9597), T(0.5472), T(0.1966), T(0.7572), T(0.5688),
                              T(0.5469), T(0.9157), T(0.3922), T(0.3171), T(0.6463), T(0.3404), T(0.1386), T(0.2511), T(0.7537), T(0.4694),
                              T(0.9575), T(0.7922), T(0.6555), T(0.9502), T(0.7094), T(0.5853), T(0.1493), T(0.6160), T(0.3804), T(0.0119),
                              T(0.9649), T(0.9595), T(0.1712), T(0.0344), T(0.7547), T(0.2238), T(0.2575), T(0.4733), T(0.5678), T(0.3371));
  size_t cnt;
  NT2_TEST_ULP_EQUAL(mnormest(n, cnt)      ,  T(5.389506873116636676), 10);
  NT2_TEST_EQUAL(cnt, sizeof(T)/2);
}
