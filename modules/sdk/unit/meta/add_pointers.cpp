/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::add_pointers"

#include <nt2/sdk/meta/add_pointers.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test add_pointer with 0 pointer added
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(add_no_pointer)
{
  using nt2::meta::add_pointers;
  using boost::is_same;

  NT2_TEST((is_same<add_pointers<float        , 0>::type,float>::value)       );
  NT2_TEST((is_same<add_pointers<double const , 0>::type,double const>::value));
  NT2_TEST((is_same<add_pointers<void*        , 0>::type,void*>::value)       );
  NT2_TEST((is_same<add_pointers<char* const  , 0>::type,char* const>::value) );
  NT2_TEST((is_same<add_pointers<int&         , 0>::type,int&>::value)        );
  NT2_TEST((is_same<add_pointers<int const&   , 0>::type,int const&>::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test add_pointer with 1..3 pointer added
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(add_some_pointers)
{
  using nt2::meta::add_pointers;
  using boost::is_same;

  NT2_TEST((is_same<add_pointers<float        , 1>::type,float*>::value)        );
  NT2_TEST((is_same<add_pointers<double const , 1>::type,double const*>::value) );
  NT2_TEST((is_same<add_pointers<void*        , 1>::type,void**>::value)        );
  NT2_TEST((is_same<add_pointers<char* const  , 1>::type,char* const*>::value)  );
  NT2_TEST((is_same<add_pointers<int&         , 1>::type,int*>::value)          );
  NT2_TEST((is_same<add_pointers<int const&   , 1>::type,int const*>::value)    );

  NT2_TEST((is_same<add_pointers<float        , 3>::type,float***>::value)        );
  NT2_TEST((is_same<add_pointers<double const , 3>::type,double const***>::value) );
  NT2_TEST((is_same<add_pointers<void*        , 3>::type,void****>::value)        );
  NT2_TEST((is_same<add_pointers<char* const  , 3>::type,char* const***>::value)  );
  NT2_TEST((is_same<add_pointers<int&         , 3>::type,int***>::value)          );
  NT2_TEST((is_same<add_pointers<int const&   , 3>::type,int const***>::value)    );
}

