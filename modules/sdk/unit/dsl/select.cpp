/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::dsl::select"

#include <nt2/sdk/dsl/select.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/proto/proto.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct SizeGrammar;

struct SizeGrammarCases
{
  template<typename Arity>
  struct  case_ 
        : boost::proto::when<boost::proto::_, boost::mpl::int_<-1>() > {};
};

template<>
struct  SizeGrammarCases::case_< boost::mpl::size_t<1> >
      : boost::proto::when<boost::proto::_, boost::mpl::int_<1337>() >
{};

template<>
struct  SizeGrammarCases::case_< boost::mpl::size_t<2> >
      : boost::proto::when<boost::proto::_, boost::mpl::int_<42>() >
{};


template<>
struct  SizeGrammarCases::case_< boost::mpl::size_t<4> >
      : boost::proto::when<boost::proto::_, boost::mpl::int_<911>() >
{};

struct SizeGrammar
  : boost::proto::select_ < SizeGrammarCases
                          , boost::mpl::sizeof_<boost::proto::_value>()
                          >
{};

boost::proto::terminal<double>::type  _d;
boost::proto::terminal<float>::type   _f;
boost::proto::terminal<short>::type   _s;
boost::proto::terminal<char>::type    _c;

////////////////////////////////////////////////////////////////////////////////
// Test dispatching on some arbitrary grammar with select
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(select)
{
  SizeGrammar g;
  
  NT2_TEST_EQUAL( int(g(_f)), 911);
  NT2_TEST_EQUAL( int(g(_s)), 42);
  NT2_TEST_EQUAL( int(g(_c)), 1337);
  NT2_TEST_EQUAL( int(g(_d)), -1);
}
