/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sys::string"

#include <nt2/sdk/sys/string.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Local streaming operator
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
inline std::ostream& operator<<( std::ostream& os, nt2::sys::string const& s )
{
  return os << s.c_str();
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string default constructor
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(default_ctor)
{
  nt2::sys::string empty;

  NT2_UNIT_TEST_EQUAL(empty,"");
  NT2_UNIT_TEST_EQUAL(empty.size(),0U);
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string formating constructor
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(format_ctor)
{
  nt2::sys::string s("%1.1f %d %s",0.1,42,"lol");

  NT2_UNIT_TEST_EQUAL(s,"0.1 42 lol");
  NT2_UNIT_TEST_EQUAL(s.size(),10U);
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string copy constructor
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(copy_ctor)
{
  nt2::sys::string origin("origin");
  nt2::sys::string copy(origin);

  NT2_UNIT_TEST_EQUAL(origin,copy);
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string swap method and function
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(swap)
{
  nt2::sys::string a("a");
  nt2::sys::string b("b");

  b.swap(a);
  NT2_UNIT_TEST_EQUAL(a,"b");
  NT2_UNIT_TEST_EQUAL(b,"a");

  b.swap(a);
  NT2_UNIT_TEST_EQUAL(a,"a");
  NT2_UNIT_TEST_EQUAL(b,"b");
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string operator=(string)
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(compare_string)
{
  nt2::sys::string string1("string1");
  nt2::sys::string string2("string2");
  nt2::sys::string string1b(string1);

  NT2_UNIT_TEST_EQUAL(string1,string1b);
  NT2_UNIT_TEST_EQUAL(string1b,string1);
  NT2_UNIT_TEST_EQUAL(string1,"string1");
  NT2_UNIT_TEST_EQUAL("string1",string1);

  NT2_UNIT_TEST_NOT_EQUAL(string1,string2);
  NT2_UNIT_TEST_NOT_EQUAL(string2,string1);
  NT2_UNIT_TEST_NOT_EQUAL(string1,"string2");
  NT2_UNIT_TEST_NOT_EQUAL("string2",string1);
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string operator=(string)
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(assign_string)
{
  nt2::sys::string origin("origin");
  nt2::sys::string copy;
  copy = origin;

  NT2_UNIT_TEST_EQUAL(origin,copy);
}

////////////////////////////////////////////////////////////////////////////////
// Test sys::string operator=(char const*)
////////////////////////////////////////////////////////////////////////////////
NT2_UNIT_TEST_CASE(assign_cstr)
{
  nt2::sys::string copy;
  copy = "origin";

  NT2_UNIT_TEST_EQUAL(copy,"origin");
}
