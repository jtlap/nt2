//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(disable: 4996) // std::transform on pointers may be unsafe
#endif

#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/simd/algorithm.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/constants/one.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

struct plus
{
  template<class T>
  T operator()(T const& t0, T const& t1) const
  {
    return t0 + t1;
  }
};

struct plus_one
{
  template<class T>
  T operator()(T const& t0) const
  {
    using boost::simd::One;
    return t0 + One<T>();
  }
};

static const std::size_t vsize = 113;

template <typename T>
using aligned_vector = std::vector<T, boost::simd::allocator<T> >;

template <typename T>
class unaligned_vector : public std::vector<T, boost::simd::allocator<T, 8> > {
    typedef std::vector<T, boost::simd::allocator<T, 8> > super;

    private:
    bool is_aligned() const {
        return boost::simd::is_aligned(super::data());
    }

    public:
    unaligned_vector(std::size_t the_size)
        : std::vector<T, boost::simd::allocator<T, 8> >(the_size + 1) {
    }

    std::size_t size() const {
        return super::size() - 1;
    }

    T* data() {
        T* the_data = super::data();
        return boost::simd::is_aligned(the_data)
            ? the_data + 1
            : the_data + 0;
    }

    const T* data() const {
        const T* the_data = super::data();
        return boost::simd::is_aligned(the_data)
            ? the_data + 1
            : the_data + 0;
    }

    typename super::const_iterator begin() const {
        return is_aligned()
            ? super::begin() + 1
            : super::begin() + 0;
    }

    typename super::const_iterator end() const {
        return is_aligned()
            ? super::end() - 0
            : super::end() - 1;
    }

};

template <typename T, typename I, typename O>
void transform_unary_test()
{
  I data_in(vsize);
  for(size_t i=0; i<vsize; ++i)
    data_in[i] = T(i);

  O data_out1(vsize);
  boost::simd::transform(data_in.data(), data_in.data()+data_in.size(), data_out1.data(), plus_one());
  O data_out2(vsize);
  std::transform(data_in.data(), data_in.data()+data_in.size(), data_out2.data(), plus_one());

  NT2_TEST_EQUAL(data_out1, data_out2);
}

template <typename T, typename I1, typename I2, typename O>
void transform_binary_test()
{
  I1 data_in1(vsize);
  I2 data_in2(vsize);
  for(size_t i=0; i<vsize; ++i)
  {
    data_in1[i] = T(i);
    data_in2[i] = T(10 + i);
  }

  O data_out1(vsize);
  boost::simd::transform(data_in1.data(), data_in1.data()+data_in1.size(), data_in2.data(), data_out1.data(), plus());

  O data_out2(vsize);
  std::transform(data_in1.data(), data_in1.data()+data_in1.size(), data_in2.data(), data_out2.data(), plus());

  NT2_TEST_EQUAL(data_out1, data_out2);
}

#define TRANSFORM_UNARY_TEST(I, O)                                             \
NT2_TEST_CASE_TPL( transform_unary_##I##_##O, BOOST_SIMD_SIMD_TYPES )          \
{                                                                              \
    typedef   aligned_vector<T> AI;                                            \
    typedef unaligned_vector<T> UI;                                            \
                                                                               \
    typedef   aligned_vector<T> AO;                                            \
    typedef unaligned_vector<T> UO;                                            \
                                                                               \
    transform_unary_test<T, I, O>();                                           \
}

#define TRANSFORM_BINARY_TEST(I1, I2, O)                                       \
NT2_TEST_CASE_TPL( transform_binary_##I1##_##I2##_##O, BOOST_SIMD_SIMD_TYPES ) \
{                                                                              \
    typedef   aligned_vector<T> AI;                                            \
    typedef unaligned_vector<T> UI;                                            \
                                                                               \
    typedef   aligned_vector<T> AO;                                            \
    typedef unaligned_vector<T> UO;                                            \
                                                                               \
    transform_binary_test<T, I1, I2, O>();                                     \
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation
////////////////////////////////////////////////////////////////////////////////
TRANSFORM_UNARY_TEST(AI, AO)
TRANSFORM_UNARY_TEST(UI, AO)
TRANSFORM_UNARY_TEST(AI, UO)
TRANSFORM_UNARY_TEST(UI, UO)

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with binary operation
////////////////////////////////////////////////////////////////////////////////
TRANSFORM_BINARY_TEST(AI, AI, AO)
TRANSFORM_BINARY_TEST(UI, UI, UO)

TRANSFORM_BINARY_TEST(AI, AI, UO)
TRANSFORM_BINARY_TEST(UI, UI, AO)

TRANSFORM_BINARY_TEST(AI, UI, UO)
TRANSFORM_BINARY_TEST(UI, AI, AO)

TRANSFORM_BINARY_TEST(AI, UI, AO)
TRANSFORM_BINARY_TEST(UI, AI, UO)
