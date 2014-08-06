//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
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


#define NT2_TEST_LOAD(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();
#define NT2_TEST_APPLY(r, data, elem) data<elem>

template<class T, class U, std::size_t N, bool masked=false, bool zero=false>
struct nt2_test_run_load_gather
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::load;
    using boost::simd::tag::load_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    using boost::simd::insert;
    using boost::simd::splat;
    using boost::simd::logical;
    using boost::simd::if_else;
    using boost::simd::meta::as_logical;

    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

    typedef native<T,ext_t>                                       vT;

    typedef typename boost::dispatch::meta::
            make_integer< N, unsigned>::type                      iT;

    typedef typename boost::simd::meta
                          ::vector_of<iT,cardinal_of<vT>::value>::type viT;
    typedef typename
            boost::dispatch::
            meta::call<load_(U*,boost::dispatch::meta::as_<vT>,viT)>::type r_t;

    typedef typename boost::simd::meta::as_logical<r_t>::type vlT;

    typedef typename boost::simd::meta::scalar_of<vlT>::type s_type;

    time_t seed = time(NULL);
    std::cout<<" Seed for random number generator "<<seed<<'\n';
    srand(seed);

    NT2_TEST( (boost::is_same<vT,r_t>::value) );

    U data[ cardinal_of<vT>::value*3 ];
    for(size_t i=0;i<cardinal_of<vT>::value*3;++i)
      data[i] = i%2 ? U(1+i) : -U(1+i);

    viT index;
    for(size_t i=0;i<cardinal_of<viT>::value;++i)
      index[i] = rand() % (cardinal_of<vT>::value*3);

    vlT mask;
    r_t old= zero ? splat<r_t>(0) : splat<r_t>(-42);

    if (masked)
      for(size_t i=0;i<cardinal_of<vlT>::value;++i)
        insert(s_type(rand()%2), mask, i);

    r_t v;

    if (zero) v = masked ? boost::simd::load<vT>(&data[0], index, mask) : boost::simd::load<vT>(&data[0], index);
    else      v = masked ? boost::simd::load<vT>(&data[0], index, mask, old) : boost::simd::load<vT>(&data[0], index);

    for(size_t j=0;j<cardinal_of<vT>::value;++j)
    {
      if(masked) NT2_TEST_EQUAL(v[j] , ( if_else(mask[j],static_cast<T>(data[index[j]]),static_cast<T>(old[j]) )));
      else       NT2_TEST_EQUAL(v[j] , static_cast<T>( data[index[j]] ));
    }
  }
};

template<class T, class U>
struct nt2_test_run_load_mask_zero_gather32 : nt2_test_run_load_gather<T,U,4,true,true>
{};


template<class T, class U>
struct nt2_test_run_load_mask_gather32 : nt2_test_run_load_gather<T,U,4,true>
{};

template<class T, class U>
struct nt2_test_run_load_gather32 : nt2_test_run_load_gather<T,U,4>
{};

template<class T, class U>
struct nt2_test_run_load_mask_zero_gather64 : nt2_test_run_load_gather<T,U,8,true,true>
{};

template<class T, class U>
struct nt2_test_run_load_mask_gather64 : nt2_test_run_load_gather<T,U,8,true>
{};

template<class T, class U>
struct nt2_test_run_load_gather64 : nt2_test_run_load_gather<T,U,8,false,false>
{};

NT2_TEST_CASE_TPL( load_mask_zero_gather32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_zero_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_gather_32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_gather32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather32_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather32
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}

NT2_TEST_CASE_TPL( load_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather64, BOOST_SIMD_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather64, BOOST_SIMD_SIMD_TYPES)
}

NT2_TEST_CASE_TPL( load_mask_zero_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_mask_zero_gather64, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather64_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather64
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}


template<typename Type, typename Target, typename Index>
void gather_indices()
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::dispatch::meta::as_;
  using boost::simd::meta::cardinal_of;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                        ::call<load_( Type*, as_<Target>, Index)>::type
                    )
                  , Target
                  );
  static const std::size_t cd = cardinal_of<Target>::value;

  Type data[cd*3];

  for (std::size_t ii=0;ii<3*cd;ii++)
    data[ii]=ii;

  int ind[cardinal_of<Index>::value];
  for (std::size_t ii=0;ii<cardinal_of<Index>::value;ii++)
    ind[ii]=3*ii;

  Index index = load<Index>(&ind[0]);

  Target loaded = load<Target>(&data[0],index);

  Target ref = boost::simd::splat<Target>(Type(0));
  for (std::size_t ii=0;ii<cardinal_of<Index>::value;ii++)
    ref[ii] = data[ind[ii]];

  NT2_TEST_EQUAL(loaded,ref);
}

template<typename Type, typename Target, typename Index, typename Mask>
void gather_indices_mask()
{
  using boost::simd::load;
  using boost::simd::extract;
  using boost::simd::if_else;
  using boost::simd::tag::load_;
  using boost::dispatch::meta::as_;
  using boost::simd::meta::cardinal_of;
  using boost::simd::meta::scalar_of;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta
                        ::call<load_( Type*, as_<Target>, Index, Mask, Target)>::type
                    )
                  , Target
                  );

  static const std::size_t cd = cardinal_of<Target>::value;

  typedef typename scalar_of<Mask>::type l_type;

  Type data[cd*3];

  for (std::size_t ii=0;ii<3*cd;ii++)
    data[ii]=ii;

  int ind[cardinal_of<Index>::value];
  for (std::size_t ii=0;ii<cardinal_of<Index>::value;ii++)
    ind[ii]=3*ii;

  Target ref = boost::simd::splat<Target>(Type(0));
  Target old = boost::simd::splat<Target>(Type(65));

  time_t seed = time(NULL);
  std::cout<<" Seed for random number generator "<<seed<<'\n';
  srand(seed);

  Mask mask;

  for(size_t ii=0;ii<cd;++ii)
    insert(l_type(rand()%2), mask, ii);

  for (std::size_t ii=0;ii<cardinal_of<Index>::value;ii++)
    ref[ii] = if_else(extract(mask,ii),data[ind[ii]],extract(old,ii));

  Index index = load<Index>(&ind[0]);

  Target loaded = load<Target>(&data[0],index,mask,old);

  NT2_TEST_EQUAL(loaded,ref);
}

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

//loading 64 bit avx types using 32bit sse indices
NT2_TEST_CASE_TPL(test_gather32sse_64avx, (long long)(double))
{
  typedef boost::simd::native<T, boost::simd::tag::avx_> n_t;
  typedef boost::simd::native<int32_t,boost::simd::tag::sse_> i_t;
  typedef typename boost::simd::meta::as_logical<n_t>::type l_t;

  gather_indices<T,n_t,i_t>();
  gather_indices_mask<T,n_t,i_t,l_t>();
}

//loading 32 bit sse types using 64bit avx indices
NT2_TEST_CASE_TPL(test_gather64avx_32sse, (int)(float))
{
  typedef boost::simd::native<T, boost::simd::tag::sse_> n_t;
  typedef boost::simd::native<int64_t,boost::simd::tag::avx_> i_t;
  typedef typename boost::simd::meta::as_logical<n_t>::type l_t;

  gather_indices<T,n_t,i_t>();
  gather_indices_mask<T,n_t,i_t,l_t>();
}

//loading 32 bit sse types using 32bit sse indices
NT2_TEST_CASE_TPL(test_gather32sse_32sse, (int)(float))
{
  typedef boost::simd::native<T, boost::simd::tag::sse_> n_t;
  typedef boost::simd::native<int32_t,boost::simd::tag::sse_> i_t;
  typedef typename boost::simd::meta::as_logical<n_t>::type l_t;

  gather_indices<T,n_t,i_t>();
  gather_indices_mask<T,n_t,i_t,l_t>();
}

//loading 64 bit sse type using a 64 bit sse index
NT2_TEST_CASE_TPL(test_gather64sse_64sse, (long long)(double))
{
  typedef boost::simd::native<T, boost::simd::tag::sse_> n_t;
  typedef boost::simd::native<int64_t,boost::simd::tag::sse_> i_t;
  typedef typename boost::simd::meta::as_logical<n_t>::type l_t;

  gather_indices<T,n_t,i_t>();
  gather_indices_mask<T,n_t,i_t,l_t>();
}

#endif
