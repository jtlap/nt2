//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"

#include <cstdlib>
#include <time.h>

#define NT2_TEST_ALIGNED_LOAD(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();

template<class T, class U>
struct nt2_test_run_aligned_load_gather
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::aligned_load;
    using boost::simd::tag::aligned_load_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
    typedef native<T,ext_t>                        vT;
    typedef typename boost::dispatch::meta::as_integer<vT>::type viT;

    typedef typename
            boost::dispatch::
            meta::call<aligned_load_(U*,viT,boost::dispatch::meta::as_<vT>)>::type rT;

    NT2_TEST_TYPE_IS( rT, vT );

    BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  U, cardinal_of<vT>::value*3 );

    for(size_t i=0;i<cardinal_of<vT>::value*3;++i) data[i] = U(1+i);

    viT index;
    rT ref;

    // Spread out the gather values
    index[0] = cardinal_of<vT>::value*3 -1;
    index[cardinal_of<viT>::value-1] = 0;

    for(size_t i=1;i<cardinal_of<viT>::value-1;++i)
    {
      index[i] = T(i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1));
    }

    for(size_t i=0;i<cardinal_of<vT>::value;++i) ref[i] = data[index[i]];

    rT v = boost::simd::aligned_load<vT>(&data[0], index);

    NT2_TEST_EQUAL(v , ref);
  }
};

NT2_TEST_CASE_TPL( load_gather, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_LOAD, aligned_load_gather, BOOST_SIMD_TYPES)
}

template<class T, class U>
struct nt2_test_run_mask_aligned_load_gather
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::aligned_load;
    using boost::simd::tag::aligned_load_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    using boost::simd::splat;
    using boost::simd::if_else;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
    typedef native<T,ext_t>                        vT;
    typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
    typedef typename boost::simd::meta::as_logical<vT>::type vlT;
    typedef typename boost::simd::meta::scalar_of<vlT>::type l_type;
    typedef typename
            boost::dispatch::
            meta::call<aligned_load_(U*,viT,boost::dispatch::meta::as_<vT>)>::type rT;
    typedef typename boost::simd::meta::scalar_of<rT>::type t_type;

    NT2_TEST_TYPE_IS( rT, vT );

    BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  U, cardinal_of<vT>::value*3 );

    for(size_t i=0;i<cardinal_of<vT>::value*3;++i) data[i] = U(1+i);

    viT index;
    rT ref;
    rT old =splat<rT>(65);

    srand(time(NULL));

    vlT mask;
    for(size_t i=0;i<cardinal_of<viT>::value;++i)
      insert(l_type(rand()%2), mask, i);
    // Spread out the gather values
    index[0] = cardinal_of<vT>::value*3 -1;
    index[cardinal_of<viT>::value-1] = 0;

    for(size_t i=1;i<cardinal_of<viT>::value-1;++i)
    {
      index[i] = T(i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1));
    }

    for(size_t i=0;i<cardinal_of<vT>::value;++i) ref[i] = if_else(mask[i],t_type(data[index[i]]),old[i]);

    rT v = boost::simd::aligned_load<vT>(&data[0], index, old, mask);

    NT2_TEST_EQUAL(v , ref);
  }
};

NT2_TEST_CASE_TPL( mask_load_gather, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_ALIGNED_LOAD, mask_aligned_load_gather, BOOST_SIMD_TYPES)
}
