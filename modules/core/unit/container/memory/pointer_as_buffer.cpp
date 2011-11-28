/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory T* adaptation as a Buffer"

#include <nt2/core/container/memory/adapted/pointer.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
////////////////////////////////////////////////////////////////////////////////
// pointer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_dimensions )
{
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL((dimensions_of< int* >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< float const** >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< double*** >::value), 3UL);
}


////////////////////////////////////////////////////////////////////////////////
// pointer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_storage_order )
{
  using nt2::meta::storage_order_of;
  using nt2::C_order_;
  using boost::mpl::_;

  int* a0;
  float const** a1;
  double*** a2;

  NT2_TEST_EXPR_TYPE(a0, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(a1, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(a2, storage_order_of<_>, C_order_ );

}

////////////////////////////////////////////////////////////////////////////////
// pointer type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_values )
{
  using boost::is_same;
  using boost::dispatch::meta::value_of;

  NT2_TEST((is_same< value_of< int* >::type  , int>::value ));
  NT2_TEST((is_same< value_of< int** >::type , int>::value ));
  NT2_TEST((is_same< value_of< int*** >::type, int>::value ));

  NT2_TEST((is_same< value_of< int const* >::type  , int const>::value ));
  NT2_TEST((is_same< value_of< int const** >::type , int const>::value ));
  NT2_TEST((is_same< value_of< int const*** >::type, int const>::value ));
}

////////////////////////////////////////////////////////////////////////////////
// pointer type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_model )
{
  using boost::mpl::apply;
  using boost::is_same;
  using boost::dispatch::meta::model_of;

  typedef model_of< int* >::type model1d;
  typedef model_of< int** >::type model2d;
  typedef model_of< int*** >::type model3d;

  NT2_TEST((is_same<apply<model1d,float>::type, float* >::value ));
  NT2_TEST((is_same<apply<model2d,float>::type, float** >::value ));
  NT2_TEST((is_same<apply<model3d,float>::type, float*** >::value ));
}


////////////////////////////////////////////////////////////////////////////////
// pointer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_reference )
{
  using boost::is_same;
  using nt2::meta::dereference_;

  typedef double***       base;
  typedef double const*** cbase;

  NT2_TEST((is_same< dereference_<base&,1>::type, double**& >::value) );
  NT2_TEST((is_same< dereference_<base&,2>::type, double*& >::value) );
  NT2_TEST((is_same< dereference_<base&,3>::type, double& >::value) );

  NT2_TEST((is_same< dereference_<base const&,1>::type, double** const& >::value) );
  NT2_TEST((is_same< dereference_<base const&,2>::type, double*  const& >::value) );
  NT2_TEST((is_same< dereference_<base const&,3>::type, double   const& >::value) );

  NT2_TEST((is_same< dereference_<cbase&,1>::type, double const**& >::value) );
  NT2_TEST((is_same< dereference_<cbase&,2>::type, double const*& >::value) );
  NT2_TEST((is_same< dereference_<cbase&,3>::type, double const& >::value) );

  NT2_TEST((is_same< dereference_<cbase const&,1>::type, double const** const& >::value) );
  NT2_TEST((is_same< dereference_<cbase const&,2>::type, double const*  const& >::value) );
  NT2_TEST((is_same< dereference_<cbase const&,3>::type, double const& >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// pointer type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_1D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  double* tab = new double[5];

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::size_t,1> pos;

  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  for(pos[0]=0;pos[0]<5;++pos[0])
    dereference<1UL>(tab,pos) = double(10*(1+pos[0]));

  for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );

  delete[] tab;
}

////////////////////////////////////////////////////////////////////////////////
// pointer type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_2D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  typedef double* ptr;
  ptr* tab = new ptr[2];

  for(int i=0;i<2;++i) tab[i] = new double[5];

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::ptrdiff_t,2> pos;

  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
      dereference<2UL>(tab,pos) = double(10*(1+pos[1]) + (1+pos[0]));

  for(pos[1]=0;pos[1]<2;++pos[1])
    for(pos[0]=0;pos[0]<5;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );

  for(int i=0;i<2;++i) delete[] tab[i];
  delete[] tab;
}

////////////////////////////////////////////////////////////////////////////////
// pointer type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer_3D_as_buffer )
{
  using boost::array;
  using nt2::memory::initialize;
  using nt2::memory::dereference;

  typedef double** pptr;
  typedef double*  ptr;
  pptr* tab = new pptr[2];

  for(int i=0;i<2;++i)
  {
    tab[i] = new ptr[3];
    for(int j=0;j<3;++j)
      tab[i][j] = new double[4];
  }

  boost::array<std::size_t,3> sizes = {{4,3,2}};
  boost::array<std::size_t,3> bases = {{0,0,0}};
  boost::array<std::size_t,3> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<3;++pos[1])
      for(pos[0]=0;pos[0]<4;++pos[0])
      dereference<3UL>(tab,pos) = double(100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<3;++pos[1])
      for(pos[0]=0;pos[0]<4;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

  for(int i=0;i<2;++i)
  {
    for(int j=0;j<3;++j) delete[] tab[i][j];
    delete[] tab[i];
  }

  delete[] tab;
}

