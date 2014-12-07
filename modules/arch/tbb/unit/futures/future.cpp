//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 futures future"

#include <boost/dispatch/functor/forward.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


namespace nt2
{
    namespace tag
    {
        template<class T> struct tbb_;
    }
}

typedef typename boost::dispatch::default_site<void>::type Site;
typedef typename nt2::tag::tbb_<Site> Arch;
typedef typename nt2::make_future< Arch,int >::type future;

struct p1
{
    typedef int result_type;

    int operator()() const
    {
        return 1;
    }
};

struct p2
{
    typedef int result_type;

    int operator()(future value) const
    {
        return value.get()*2;
    }
};

struct p3
{
    typedef int result_type;

    int operator()(future value) const
    {
        return value.get()*3;
    }
};

struct p4
{
    typedef int result_type;

    int operator()(future) const
    {
        return 50;
    }
};

NT2_TEST_CASE( then_future )
{
  future f1 = nt2::async<Arch>(p1());
  future f2 = f1.then(p2());
  future f3 = f2.then(p3());

  future f4 = nt2::async<Arch>(p1()).then(p2()).then(p3());

  int value1 = f3.get();
  int value2 = f4.get();

  NT2_TEST_EQUAL(value1,6) ;
  NT2_TEST_EQUAL(value2,6) ;

  p1 w1;
  p2 w2;
  p3 w3;

  future f5 = nt2::async<Arch>(std::move(w1));
  future f6 = f5.then(std::move(w2));
  future f7 = f6.then(std::move(w3));

  future f8 = nt2::async<Arch>(std::move(w1)).then(std::move(w2)).then(std::move(w3));

  int value3 = f7.get();
  int value4 = f8.get();

  NT2_TEST_EQUAL(value3,6) ;
  NT2_TEST_EQUAL(value4,6) ;
}

NT2_TEST_CASE( make_ready_future )
{
  future f1 = nt2::make_ready_future<Arch,int>(12);

  int value1 = f1.get();

  NT2_TEST_EQUAL(value1,12) ;

  int initial_value = 12;

  future f2 = nt2::make_ready_future<Arch,int>(initial_value);

  int value2 = f2.get();

  NT2_TEST_EQUAL(value2,12) ;
}

NT2_TEST_CASE( when_all_future )
{
  future f1 = nt2::make_ready_future<Arch,int>(12);
  future f2 = nt2::make_ready_future<Arch,int>(24);
  future f3 = nt2::make_ready_future<Arch,int>(48);

  future f4 = nt2::when_all<Arch>(f1,f2,f3);
  future f5 = f4.then(p4());
  int value1 = f5.get();

  NT2_TEST_EQUAL(value1,50) ;

  future f6 = nt2::make_ready_future<Arch,int>(12);
  future f7 = nt2::make_ready_future<Arch,int>(24);
  future f8 = nt2::make_ready_future<Arch,int>(48);

  future f9 = nt2::when_all<Arch>(f6,f7,f8).then(p4());
  int value2 = f9.get();

  NT2_TEST_EQUAL(value2,50) ;

}
