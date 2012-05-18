//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite_buffer as a Buffer"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/meta/adapt_composite.hpp>
#include <nt2/sdk/memory/composite_buffer.hpp>

#include <boost/fusion/include/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct foo { double d; float f; char c; };
NT2_ADAPT_COMPOSITE(foo,(double,d)(float,f)(char,c))

////////////////////////////////////////////////////////////////////////////////
// composite_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( composite_buffer )
{
  using nt2::memory::composite_buffer;
  using nt2::memory::buffer;

  typedef composite_buffer< buffer<foo> > tab;

  std::cout << nt2::type_id<tab::data_t>() << "\n";
  std::cout << nt2::type_id<tab::value_type>() << "\n";
  std::cout << nt2::type_id<tab::reference>() << "\n";
  std::cout << nt2::type_id<tab::const_reference>() << "\n";
  std::cout << nt2::type_id<tab::iterator>() << "\n";
  std::cout << nt2::type_id<tab::const_iterator>() << "\n";
  std::cout << nt2::type_id<tab::reverse_iterator>() << "\n";
  std::cout << nt2::type_id<tab::const_reverse_iterator>() << "\n";
}

