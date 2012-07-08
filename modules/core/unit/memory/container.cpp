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
#include <nt2/core/container/table/semantic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#define DIMS (nt2::_1D)(nt2::_2D)(nt2::_3D)(nt2::_4D)

//==============================================================================
// container type has some value
//==============================================================================
NT2_TEST_CASE_TPL( container_values, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;
  using boost::dispatch::meta::value_of;

  NT2_TEST_EXPR_TYPE( (container<T, settings()>())
                    , value_of<_>
                    , T
                    );
}

//==============================================================================
// container type has a model
//==============================================================================
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

  NT2_TEST_EXPR_TYPE
  ( (container<int, settings()>())
  , (apply_model<_,T>)
  , (container<T, settings()>)
  );
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_dynamic_default_ctor, DIMS)
{
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  container<double,settings(T)> b;

  NT2_TEST(b.empty());
  NT2_TEST_EQUAL(b.size()             , 0u );
  NT2_TEST_EQUAL(b.leading_size()     , 0u );
  NT2_TEST_EQUAL(b.extent(), of_size_<0>());
  NT2_TEST_EQUAL(b.raw(), (double*)(0));
}

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_static_default_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings(of_size_<3,7>)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        b[i+3*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j] ,T((1+i) + 10*(1+j)) );
  }

  {
    typedef container<T,settings(of_size_<1,5>)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<1,5>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<5;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<5;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j] ,T((1+i) + 10*(1+j)) );
  }
}

//==============================================================================
// Test for container default ctor of automatic containers
//==============================================================================
NT2_TEST_CASE_TPL( container_automatic_static_default_ctor, NT2_TYPES)
{
  using nt2::of_size_;
  using nt2::settings;
  using nt2::automatic_;
  using nt2::memory::container;

  {
    typedef container<T,settings(of_size_<3,7>, automatic_)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        b[i+3*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j] ,T((1+i) + 10*(1+j)) );
  }

  {
    typedef container<T,settings(of_size_<1,7>, automatic_)> type;
    type b;

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size()             , b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<1,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j] ,T((1+i) + 10*(1+j)) );
  }
}

//==============================================================================
// Test for container size ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_size_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings()> type;
    type b( of_size(3,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<3,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        b[i+3*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( b[i+3*j] ,T((1+i) + 10*(1+j)) );
  }


  {
    typedef container<T,settings()> type;
    type b( of_size(1,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), (of_size_<1,7>()) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( b[i+1*j] ,T((1+i) + 10*(1+j)) );
  }
}

//==============================================================================
// Test for container copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( container_copy_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings()> type;
    type b( of_size(5,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        b[i+5*j] = T((1+i) + 10*(1+j));

    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(5,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL( x[i+5*j], b[i+5*j] );
  }

  {
    typedef container<T,settings()> type;
    type b( of_size(1,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(1,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( x[i+1*j], b[i+1*j] );
  }
}

//==============================================================================
// Test for automatic container copy ctor
//==============================================================================
NT2_TEST_CASE_TPL( automatic_container_copy_ctor, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings(of_size_<3,7>, automatic_)> type;
    type b;

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        b[i+3*j] = T((1+i) + 10*(1+j));

    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(3,7) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL( x[i+3*j], b[i+3*j] );
  }

  {
    typedef container<T,settings(of_size_<1,7>, automatic_)> type;
    type b;

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    type x( b );

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(1,7) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL( x[i+1*j], b[i+1*j] );
  }
}

//==============================================================================
// Test for container assignment
//==============================================================================
NT2_TEST_CASE_TPL( container_assignment, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings()> type;
    type b( of_size(5,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        b[i+5*j] = T((1+i) + 10*(1+j));

    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(5,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j], T((1+i) + 10*(1+j)));
  }

  {
    typedef container<T,settings()> type;
    type b( of_size(1,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(1,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j], T((1+i) + 10*(1+j)));
  }
}

//==============================================================================
// Test for automatic container assignment
//==============================================================================
NT2_TEST_CASE_TPL( automatic_container_assignment, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings(of_size_<5,3>)> type;
    type b;

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        b[i+5*j] = T((1+i) + 10*(1+j));

    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(5,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j], T((1+i) + 10*(1+j)));
  }

  {
    typedef container<T,settings(of_size_<1,3>)> type;
    type b;

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    type x;

    x = b;

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(1,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);
    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j], T((1+i) + 10*(1+j)));
  }
}

//==============================================================================
// Test for container swap
//==============================================================================
NT2_TEST_CASE_TPL( container_swap, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::memory::container;

  {
    typedef container<T,settings()> type;
    type b( of_size(5,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        b[i+5*j] = T((1+i) + 10*(1+j));

    type x( of_size(7,2) );

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<7;++i)
        x[i+7*j] = T((1+i) + 10*(1+j));

    swap(x,b);

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), of_size(7,2) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(5,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);

    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<5;++i)
        NT2_TEST_EQUAL(x[i+5*j], T((1+i) + 10*(1+j)));

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<7;++i)
        NT2_TEST_EQUAL(b[i+7*j], T((1+i) + 10*(1+j)));
  }

  {
    typedef container<T,settings()> type;
    type b( of_size(1,3) );

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        b[i+1*j] = T((1+i) + 10*(1+j));

    type x( of_size(1,2) );

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<1;++i)
        x[i+1*j] = T((1+i) + 10*(1+j));

    swap(x,b);

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL( b.extent(), of_size(1,2) );
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    NT2_TEST(!x.empty());
    NT2_TEST_EQUAL(x.leading_size(), x.extent()[0] );
    NT2_TEST_EQUAL( x.extent(), of_size(1,3) );
    NT2_TEST_EQUAL(x.raw(), &x[0]);

    NT2_TEST_NOT_EQUAL(x.raw(), b.raw());

    for(typename type::difference_type j=0;j<3;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(x[i+1*j], T((1+i) + 10*(1+j)));

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<1;++i)
        NT2_TEST_EQUAL(b[i+1*j], T((1+i) + 10*(1+j)));
  }
}

//==============================================================================
// Test for container resize
//==============================================================================
NT2_TEST_CASE_TPL( container_resize, NT2_TYPES)
{
  using nt2::of_size;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::memory::container;

  {
    typedef container<T,settings()> type;
    type b;

    NT2_TEST(b.empty());
    NT2_TEST_EQUAL(b.size(),  0u );
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL(b.extent(), of_size_<0>());
    NT2_TEST_EQUAL(b.raw(), (T*)(0));

    b.resize( of_size(3,2) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL(b.extent(), of_size(3,2));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<3;++i)
        b[i+3*j] = T((1+i) + 10*(1+j));

    for(typename type::difference_type j=0;j<2;++j)
      for(typename type::difference_type i=0;i<3;++i)
        NT2_TEST_EQUAL(b[i+3*j], T((1+i) + 10*(1+j)));

    b.resize( of_size(1,11) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL(b.extent(), of_size(1,11));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<11;++j)
      b[j] = T(j);

    for(typename type::difference_type j=0;j<11;++j)
        NT2_TEST_EQUAL(b[j], T(j) );

    b.resize( of_size(2,7) );

    NT2_TEST(!b.empty());
    NT2_TEST_EQUAL(b.leading_size(), b.extent()[0] );
    NT2_TEST_EQUAL(b.extent(), of_size(2,7));
    NT2_TEST_EQUAL(b.raw(), &b[0]);

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<2;++i)
        b[i+2*j] = T((1+j) + 10*(1+i));

    for(typename type::difference_type j=0;j<7;++j)
      for(typename type::difference_type i=0;i<2;++i)
        NT2_TEST_EQUAL(b[i+2*j], T((1+j) + 10*(1+i)) );
  }
}
