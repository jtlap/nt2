//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory container"

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include "local_semantic.hpp"
#include "local_io.hpp"

// List of dimensions to test for
#define DIMS (nt2::_1D)(nt2::_2D)(nt2::_3D)(nt2::_4D)

NT2_TEST_CASE_TPL( container_values, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;
  using boost::dispatch::meta::value_of;

  NT2_TEST_EXPR_TYPE( (container<some_kind_, T, settings()>())
                    , value_of<_>
                    , T
                    );
}

template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( container_models, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;

  NT2_TEST_EXPR_TYPE( (container<some_kind_, int, settings()>())
                    , (apply_model<_,T>)
                    , (container<some_kind_, T, settings()>)
                    );
}

NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  container<some_kind_, double,settings(T)> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()             , 0u );
  NT2_TEST_EQUAL(b.leading_size()     , 0u );
  NT2_TEST_EQUAL(b.extent(), of_size_<0>());
}

NT2_TEST_CASE_TPL( container_static_default_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings(of_size_<3,7>)> type;

  type b;
  std::vector<T> ref(3*7);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size() , b.extent()[0]     );
  NT2_TEST_EQUAL(b.extent()       , (of_size_<3,7>()) );
  NT2_TEST_EQUAL(b.data()          , &b[0]             );

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<3;++i)
      b[i+3*j] = ref[i+3*j] = T((1+i) + 10*(1+j));

  NT2_TEST_EQUAL( b, ref );
}

NT2_TEST_CASE_TPL( container_automatic_static_default_ctor, NT2_TYPES)
{
  using nt2::of_size_;
  using nt2::settings;
  using nt2::automatic_;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings(of_size_<3,7>, automatic_)> type;
  type b;
  std::vector<T> ref(3*7);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<3;++i)
      b[i+3*j] = ref[i+3*j] = T((1+i) + 10*(1+j));

  NT2_TEST_EQUAL( b, ref );
}

NT2_TEST_CASE_TPL( container_size_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type b( of_size(3,7) );
  std::vector<T> ref(3*7);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<3;++i)
      b[i+3*j] = ref[i+3*j] = T((1+i) + 10*(1+j));

  NT2_TEST_EQUAL( b, ref );
}

NT2_TEST_CASE_TPL( container_copy_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type b( of_size(5,3) );

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
      b[i+5*j] = T((1+i) + 10*(1+j));

  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  NT2_TEST_EQUAL( x, b );
}

NT2_TEST_CASE_TPL( automatic_container_copy_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings(of_size_<3,7>, automatic_)> type;
  type b;

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<3;++i)
      b[i+3*j] = T((1+i) + 10*(1+j));

  type x( b );

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(3,7)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  NT2_TEST_EQUAL( x, b );
}

NT2_TEST_CASE_TPL( container_assignment, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type b( of_size(5,3) );

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
      b[i+5*j] = T((1+i) + 10*(1+j));

  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  NT2_TEST_EQUAL(x,b);
}

NT2_TEST_CASE_TPL( automatic_container_assignment, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings(of_size_<5,3>)> type;
  type b;

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
      b[i+5*j] = T((1+i) + 10*(1+j));

  type x;

  x = b;

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST_EQUAL( x.extent(), (of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);
  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  NT2_TEST_EQUAL(x,b);
}

NT2_TEST_CASE_TPL( container_swap, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type b( of_size(5,3) ), ref_b;

  for(typename type::difference_type j=0;j<3;++j)
    for(typename type::difference_type i=0;i<5;++i)
      b[i+5*j] = T((1+i) + 10*(1+j));

  ref_b = b;

  type x( of_size(7,2) ), ref_x;

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<7;++i)
      x[i+7*j] = T((1+i) + 10*(1+j));

  ref_x = x;

  swap(x,b);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL( b.extent(), (of_size(7,2)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  NT2_TEST(!x.empty());
  NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
  NT2_TEST( (x.extent() == of_size(5,3)) );
  NT2_TEST_EQUAL(x.data(), &x[0]);

  NT2_TEST_NOT_EQUAL(x.data(), b.data());

  NT2_TEST_EQUAL(x, ref_b);
  NT2_TEST_EQUAL(b, ref_x);
}

NT2_TEST_CASE_TPL( container_resize, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type b;

  std::vector<T> ref;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size(),  0u );
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), of_size_<0>());

  b.resize( of_size(3,2) );
  ref.resize(3*2);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(3,2)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(typename type::difference_type j=0;j<2;++j)
    for(typename type::difference_type i=0;i<3;++i)
      b[i+3*j] = ref[i+3*j] = T((1+i) + 10*(1+j));

  NT2_TEST_EQUAL(b,ref);

  b.resize( of_size(1,11) );
  ref.resize(11);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(1,11)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(typename type::difference_type j=0;j<11;++j)
    b[j] = ref[j] = T(j);

  NT2_TEST_EQUAL(b,ref);

  b.resize( of_size(2,7) );
  ref.resize(2*7);

  NT2_TEST(!b.empty());
  NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
  NT2_TEST_EQUAL(b.extent(), (of_size(2,7)) );
  NT2_TEST_EQUAL(b.data(), &b[0]);

  for(typename type::difference_type j=0;j<7;++j)
    for(typename type::difference_type i=0;i<2;++i)
      b[i+2*j] = ref[i+2*j] = T((1+j) + 10*(1+i));

  NT2_TEST_EQUAL(b,ref);
}

NT2_TEST_CASE_TPL( container_push_back, NT2_TYPES)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  typedef container<some_kind_, T,settings()> type;
  type a(nt2::of_size(2, 3));

  std::vector<T> ref(2*3);

  for(std::ptrdiff_t i=0; i<2*3; ++i) a[i] = ref[i] = T(0);
  for(std::ptrdiff_t i=0; i<7; ++i)   a.push_back(T(i));
  for(std::ptrdiff_t i=0; i<7; ++i)   ref.push_back(T(i));

  NT2_TEST_EQUAL( a.extent(), nt2::of_size(2*3+7) );
  NT2_TEST_EQUAL( a, ref );
}

NT2_TEST_CASE_TPL( container_push_back_range, NT2_TYPES)
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::memory::container;

  typedef container<some_kind_, T,_2D> type;
  type a(nt2::of_size(2, 3));
  type b(nt2::of_size(2, 3));

  std::vector<T> ref(2*6);

  for(std::ptrdiff_t i=0; i<2*3; ++i) b[i] = 2*(a[i] = T(1+i));

  std::ptrdiff_t i=0;
  for(; i<6; ++i)  ref[i] = a[i];
  for(; i<12; ++i) ref[i] = b[i-6];

  a.push_back(b, 1);

  NT2_TEST_EQUAL( a.extent(), nt2::of_size(2,6) );
  NT2_TEST_EQUAL( a, ref );

  type c(nt2::of_size(7, 5));

  NT2_TEST_ASSERT(a.push_back(c, 1));
}
