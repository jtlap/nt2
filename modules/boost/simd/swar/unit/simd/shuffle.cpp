//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - shuffle/simd Mode"

#include <boost/simd/toolbox/swar/include/functions/shuffle.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <iostream>

struct identity_
{
  template<class Index, class Cardinal> struct apply : Index {};
};

struct reverse_
{
  template<class Index, class Cardinal>
  struct apply : boost::mpl::int_<Cardinal::value - Index::value - 1> {};
};

struct mirror_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::int_ < (Index::value < Cardinal::value/2)
                          ? Index::value
                          : (Cardinal::value - 1 - Index::value)
                          >
  {};
};

template<int N>
struct bcast_
{
  template<class Index, class Cardinal>
  struct apply
  {
    BOOST_MPL_ASSERT_MSG
    ( (N < Cardinal::value)
    , OUT_OF_BOUND_SIMD_BROADCAST
    , (Cardinal)
    );

    typedef boost::mpl::int_< N > type;
  };
};

struct null_
{
  template<class Index, class Cardinal> struct apply : boost::mpl::int_<-1> {};
};

struct half_null_
{
  template<class Index, class Cardinal>
  struct apply : boost::mpl::int_< Index::value % 2 ? Index::value/2 : -1> {};
};

struct random_
{
  template<class Index, class Cardinal>
  struct apply  : boost::mpl
                ::int_< (Index::value * 3 + 1) % Cardinal::value > {};
};

NT2_TEST_CASE_TPL ( shuffle, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  vT origin, reference;
  vT id, shuffled, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = shuffle<identity_>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  shuffled = shuffle<reverse_>(origin);
  NT2_TEST_EQUAL(shuffled,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = i%2 ? origin[i/2] : 0;
  hnull = shuffle<half_null_>(origin);
  NT2_TEST_EQUAL(hnull,reference);

  NT2_TEST_EQUAL( shuffle<null_>(origin), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = shuffle<mirror_>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = shuffle< bcast_<1> >(origin);
  NT2_TEST_EQUAL(bcasted,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[(i*3+1) % vT::static_size];
  randed = shuffle< random_ >(origin);
  NT2_TEST_EQUAL(randed,reference);
}

struct low0_upshuffled_
{
  template<class Index, class Cardinal>
  struct apply  : boost::mpl
                ::int_< (Index::value < Cardinal::value/2) ? Index::value : -1 > {};
};

struct lowshuffled_up0_
{
  template<class Index, class Cardinal>
  struct apply  : boost::mpl
                ::int_< (Index::value < Cardinal::value/2) ? -1 : Index::value > {};
};

NT2_TEST_CASE_TPL( shuffle_optim, (float)(int32_t)(uint32_t) )
{
  using boost::simd::shuffle;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  {
    typedef native<T,ext_t>           vT;

    vT origin, reference, shuffled;
    for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
    origin[0] = boost::simd::Valmax<T>();

    // Half 0/shuffle
    for(std::size_t i=0; i < vT::static_size;++i)
      reference[i] = i < vT::static_size/2 ? origin[i] : 0;

    shuffled = shuffle<low0_upshuffled_>(origin);
    NT2_TEST_EQUAL(shuffled,reference);

    // Half shuffle/0
    for(std::size_t i=0; i < vT::static_size;++i)
      reference[i] = i < vT::static_size/2 ? 0 : origin[i];

    shuffled = shuffle<lowshuffled_up0_>(origin);
    NT2_TEST_EQUAL(shuffled,reference);
  }
}

NT2_TEST_CASE_TPL( shuffle_index2, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,2>::type    vT;

  vT origin, reference;
  vT id, shuffled, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = shuffle<0,1>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  shuffled = shuffle<1,0>(origin);
  NT2_TEST_EQUAL(shuffled,reference);

  NT2_TEST_EQUAL( (shuffle<-1,-1>(origin)), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = shuffle<0,0>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = shuffle<1,1>(origin);
  NT2_TEST_EQUAL(bcasted,reference);
}

NT2_TEST_CASE_TPL( shuffle_index4, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,4>::type    vT;

  vT origin, reference;
  vT id, shuffled, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = shuffle<0,1,2,3>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  shuffled = shuffle<3,2,1,0>(origin);
  NT2_TEST_EQUAL(shuffled,reference);

  NT2_TEST_EQUAL( (shuffle<-1,-1,-1,-1>(origin)), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = shuffle<0,1,1,0>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = shuffle<1,1,1,1>(origin);
  NT2_TEST_EQUAL(bcasted,reference);
}

NT2_TEST_CASE_TPL( shuffle_index8, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,8>::type    vT;

  vT origin, reference;
  vT id, shuffled, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = shuffle<0,1,2,3,4,5,6,7>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  shuffled = shuffle<7,6,5,4,3,2,1,0>(origin);
  NT2_TEST_EQUAL(shuffled,reference);

  NT2_TEST_EQUAL( (shuffle<-1,-1,-1,-1,-1,-1,-1,-1>(origin)), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = shuffle<0,1,2,3,3,2,1,0>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = shuffle<1,1,1,1,1,1,1,1>(origin);
  NT2_TEST_EQUAL(bcasted,reference);
}

NT2_TEST_CASE_TPL( shuffle_index16, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,16>::type    vT;

  vT origin, reference;
  vT id, shuffled, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = shuffle<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  shuffled = shuffle<15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0>(origin);
  NT2_TEST_EQUAL(shuffled,reference);

  NT2_TEST_EQUAL( (shuffle<-1,-1,-1,-1,-1,-1,-1,-1
                          ,-1,-1,-1,-1,-1,-1,-1,-1>(origin)), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = shuffle<0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = shuffle<1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1>(origin);
  NT2_TEST_EQUAL(bcasted,reference);
}

NT2_TEST_CASE_TPL( shuffle_index2_2arg, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::shuffle;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,2>::type    vT;

  vT origin1, origin2, reference, res;
  for(std::size_t i=0; i < vT::static_size;++i)
  { origin1[i] = T(65+i); origin2[i] = T(i); }
  reference[0] = origin1[0]; reference[1] = origin2[1]; 
  res = shuffle<0,3>(origin1, origin2);
  NT2_TEST_EQUAL(res,reference);
  reference[0] = 0; reference[1] = origin2[1]; 
  res = shuffle<-1,3>(origin1, origin2);
  NT2_TEST_EQUAL(res,reference);
}
