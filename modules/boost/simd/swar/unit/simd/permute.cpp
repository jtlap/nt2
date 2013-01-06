//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - permute/simd Mode"

#include <boost/simd/toolbox/swar/include/functions/permute.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

struct identity_
{
  template<class Index, class Cardinal>
  struct apply : Index
  {
  };
};

struct reverse_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_<Cardinal::value - Index::value - 1>
  {
  };
};

struct mirror_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_ < !(Cardinal::value/2 <= Index::value)
                ? Index::value
                : (Cardinal::value - 1 - Index::value)
              >
  {};
};

template<unsigned int N>
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
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::int_<-1>
  {
  };
};

struct half_null_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_< Index::value % 2 ? Index::value/2 : -1 >
  {
  };
};

struct random_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_< (Index::value * 3 + 1) % Cardinal::value >
  {
  };
};

NT2_TEST_CASE_TPL ( permute, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::permute;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  vT origin, reference;
  vT id, permuted, hnull, mirrored, bcasted,randed;
  for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
  origin[0] = boost::simd::Valmax<T>();

  id = permute<identity_>(origin);
  NT2_TEST_EQUAL(id,origin);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[vT::static_size - i -1];
  permuted = permute<reverse_>(origin);
  NT2_TEST_EQUAL(permuted,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = i%2 ? origin[i/2] : 0;
  hnull = permute<half_null_>(origin);
  NT2_TEST_EQUAL(hnull,reference);

  NT2_TEST_EQUAL( permute<null_>(origin), nt2::Zero<vT>());

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[i<vT::static_size/2 ? i : vT::static_size - i -1];
  mirrored = permute<mirror_>(origin);
  NT2_TEST_EQUAL(mirrored,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[1];
  bcasted = permute< bcast_<1> >(origin);
  NT2_TEST_EQUAL(bcasted,reference);

  for(std::size_t i=0; i < vT::static_size;++i)
    reference[i] = origin[(i*3+1) % vT::static_size];
  randed = permute< random_ >(origin);
  NT2_TEST_EQUAL(randed,reference);
}

struct low0_upshuffled_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_< !(Cardinal::value/2 <= Index::value)
               ? Index::value
               : -1
             >
  {
  };
};

struct lowshuffled_up0_
{
  template<class Index, class Cardinal>
  struct apply
       : boost::mpl::
         int_< !(Cardinal::value/2 <= Index::value)
               ? -1
               : Index::value
             >
  {
  };
};

NT2_TEST_CASE_TPL( permute_optim, (float)(int32_t)(uint32_t) )
{
  using boost::simd::permute;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  {
    typedef native<T,ext_t>           vT;

    vT origin, reference, permuted;
    for(std::size_t i=1; i < vT::static_size;++i) origin[i] = T(65+i);
    origin[0] = boost::simd::Valmax<T>();

    // Half 0/shuffle
    for(std::size_t i=0; i < vT::static_size;++i)
      reference[i] = i < vT::static_size/2 ? origin[i] : 0;

    permuted = permute<low0_upshuffled_>(origin);
    NT2_TEST_EQUAL(permuted,reference);

    // Half shuffle/0
    for(std::size_t i=0; i < vT::static_size;++i)
      reference[i] = i < vT::static_size/2 ? 0 : origin[i];

    permuted = permute<lowshuffled_up0_>(origin);
    NT2_TEST_EQUAL(permuted,reference);
  }
}
