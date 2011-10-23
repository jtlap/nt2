//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - SIMD logical<T>"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of logical<T> in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/toolbox/boolean/logical.hpp>

NT2_TEST_CASE_TPL ( logical_hierarchy_of, BOOST_SIMD_TYPES )
{
  using boost::is_same;
  using boost::simd::native;
  using boost::simd::logical;
  using boost::dispatch::meta::simd_;
  using boost::simd::ext::logical_;
  using boost::dispatch::meta::hierarchy_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  NT2_TEST((is_same < simd_< logical_< native< logical<T>, ext_t> >, ext_t>
                    , typename hierarchy_of< native< logical<T>, ext_t> >::type 
                    >::value 
          ));
}