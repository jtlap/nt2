/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory iliffe_buffer"

#include <nt2/core/container/memory/iliffe_buffer.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/core/container/memory/buffer.hpp>

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

#include <boost/array.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


#define PADDING                                                                   \
(nt2::memory::no_padding)(nt2::memory::lead_padding)(nt2::memory::global_padding) \
/**/

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer type has some dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_dimensions, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::value), 1UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::value), 2UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::value), 3UL );
  NT2_TEST_EQUAL((dimensions_of< iliffe_buffer<4,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::value), 4UL );
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_values, PADDING )
{
  using boost::is_same;
  using boost::dispatch::meta::value_of;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;
  using boost::mpl::_;

  iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib1D;
  iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib2D;
  iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib3D;
  iliffe_buffer<4,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib4D;

  NT2_TEST_EXPR_TYPE(ib1D, value_of<_>, int );
  NT2_TEST_EXPR_TYPE(ib2D, value_of<_>, int );
  NT2_TEST_EXPR_TYPE(ib3D, value_of<_>, int );
  NT2_TEST_EXPR_TYPE(ib4D, value_of<_>, int );

}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer type has storage_order
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_storage_order, PADDING )
{
  using boost::is_same;
  using nt2::meta::storage_order_of;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;
  using nt2::matlab_order_;
  using nt2::fortran_order_;
  using boost::mpl::_;

  // C storage order
  iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib1D;
  iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib2D;
  iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib3D;
  iliffe_buffer<4,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > ib4D;

  NT2_TEST_EXPR_TYPE(ib1D, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(ib2D, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(ib3D, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(ib4D, storage_order_of<_>, C_order_ );



  // matlab storage order
  iliffe_buffer<1,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > ib1D_;
  iliffe_buffer<2,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > ib2D_;
  iliffe_buffer<3,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > ib3D_;
  iliffe_buffer<4,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > ib4D_;

  NT2_TEST_EXPR_TYPE(ib1D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(ib2D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(ib3D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(ib4D_, storage_order_of<_>, matlab_order_ );


  // fortran storage order
  iliffe_buffer<1,int,buffer<int>,buffer<byte>,fortran_order_,T,allocator<int> > _ib1D_;
  iliffe_buffer<2,int,buffer<int>,buffer<byte>,fortran_order_,T,allocator<int> > _ib2D_;
  iliffe_buffer<3,int,buffer<int>,buffer<byte>,fortran_order_,T,allocator<int> > _ib3D_;
  iliffe_buffer<4,int,buffer<int>,buffer<byte>,fortran_order_,T,allocator<int> > _ib4D_;

  NT2_TEST_EXPR_TYPE(_ib1D_, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_ib2D_, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_ib3D_, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_ib4D_, storage_order_of<_>, fortran_order_ );


}


////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_models, PADDING )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using boost::mpl::apply;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  typedef typename model_of< iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::type model1d;
  typedef typename model_of< iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::type model2d;
  typedef typename model_of< iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > >::type model3d;

  NT2_TEST((is_same<typename apply<model1d,float>::type, iliffe_buffer<1,float,buffer<int>,buffer<byte>,C_order_,T,allocator<float> > >::value ));
  NT2_TEST((is_same<typename apply<model2d,float>::type, iliffe_buffer<2,float,buffer<int>,buffer<byte>,C_order_,T,allocator<float> > >::value ));
  NT2_TEST((is_same<typename apply<model3d,float>::type, iliffe_buffer<3,float,buffer<int>,buffer<byte>,C_order_,T,allocator<float> > >::value ));
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer has some reference
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_reference, PADDING )
{
  using boost::is_same;
  using nt2::memory::allocator;
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dereference_;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  typedef iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > base;

  NT2_TEST((is_same< typename dereference_<base&,1>::type, int**&>::value) );
  NT2_TEST((is_same< typename dereference_<base&,2>::type, int*& >::value) );
  NT2_TEST((is_same< typename dereference_<base&,3>::type, int& >::value) );

  NT2_TEST((is_same< typename dereference_<base const&,1>::type, int** const&>::value) );
  NT2_TEST((is_same< typename dereference_<base const&,2>::type, int* const& >::value) );
  NT2_TEST((is_same< typename dereference_<base const&,3>::type, int const&  >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_1D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{-2}};
  boost::array<std::ptrdiff_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-2;pos[0]<=2;++pos[0])
    dereference<1UL>(tab,pos) = int(10*(1+pos[0]));

  for(pos[0]=-2;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );



  boost::array<std::size_t,1> sizes_2 = {{6}};
  boost::array<std::size_t,1> bases_2 = {{-3}};

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  resize(tab, sizes_2, bases_2, T() );

  for(pos[0]=-3;pos[0]<=2;++pos[0])
    dereference<1UL>(tab,pos) = int(10*(1+pos[0]));

  for(pos[0]=-3;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );

}

////////////////////////////////////////////////////////////////////////////////
// iliffe_buffer models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_2D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<2,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > tab;

  boost::array<std::size_t,2> sizes = {{5,2}};
  boost::array<std::size_t,2> bases = {{-2,0}};
  boost::array<std::ptrdiff_t,2> pos;

  //////////////////////////////////////////////////////////////////////////////
  //  iliffe_buffer supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=2;++pos[0])
      dereference<2UL>(tab,pos) = int(10*(1+pos[1]) + (1+pos[0]));

  for(pos[1]=0;pos[1]<=1;++pos[1])
    for(pos[0]=-2;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );


  // boost::array<std::size_t,2> sizes_1 = {{5,2}};
  // boost::array<std::size_t,2> bases_1 = {{-2,0}};

  boost::array<std::size_t,2> sizes_1 = {{5,3}};
  boost::array<std::size_t,2> bases_1 = {{-3,1}};

  //////////////////////////////////////////////////////////////////////////////
  //  iliffe_buffer supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  resize(tab, sizes_1, bases_1, T() );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[1]=1;pos[1]<=3;++pos[1])
    for(pos[0]=-3;pos[0]<=1;++pos[0])
      dereference<2UL>(tab,pos) = int(10*(1+pos[1]) + (1+pos[0]));

  for(pos[1]=1;pos[1]<=3;++pos[1])
    for(pos[0]=-3;pos[0]<=1;++pos[0])
    NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );


}


////////////////////////////////////////////////////////////////////////////////
// array type models Buffer Concept
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( iliffe_buffer_3D_as_buffer, PADDING )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<3,int,buffer<int>,buffer<byte>,C_order_,T,allocator<int> > tab;

  boost::array<std::size_t,3> sizes = {{2,2,2}};
  boost::array<std::size_t,3> bases = {{0,0,0}};
  boost::array<std::size_t,3> pos;

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, T() );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
      dereference<3UL>(tab,pos) = int(100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

  for(pos[2]=0;pos[2]<2;++pos[2])
    for(pos[1]=0;pos[1]<2;++pos[1])
      for(pos[0]=0;pos[0]<2;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));


  boost::array<std::size_t,3> sizes_1 = {{3,3,3}};
  boost::array<std::size_t,3> bases_1 = {{0,0,0}};

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  resize(tab, sizes_1, bases_1, T() );


  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<3;++pos[1])
      for(pos[0]=0;pos[0]<3;++pos[0])
      dereference<3UL>(tab,pos) = int(100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

  for(pos[2]=0;pos[2]<3;++pos[2])
    for(pos[1]=0;pos[1]<3;++pos[1])
      for(pos[0]=0;pos[0]<3;++pos[0])
    NT2_TEST_EQUAL(dereference<3UL>(tab,pos), 100*(1+pos[2]) + 10*(1+pos[1]) + (1+pos[0]));

}

NT2_TEST_CASE( iliffe_buffer_1D_as_buffer_from_data_pointer )
{
  using nt2::memory::allocator;
  using nt2::memory::initialize;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::byte;
  using nt2::C_order_;

  iliffe_buffer<1,int,buffer<int>,buffer<byte>,C_order_,nt2::memory::no_padding,allocator<int> > tab;

  boost::array<std::size_t,1> sizes = {{5}};
  boost::array<std::size_t,1> bases = {{1}};
  boost::array<std::ptrdiff_t,1> pos;

  allocator<int> alloc;
  int* data = (int*) alloc.allocate(5*sizeof(int));

  for (int i = 0; i < 5; i++){
          data[i] = 10*(i+2);
  }
  //////////////////////////////////////////////////////////////////////////////
  // array type supports being initialized externally
  //////////////////////////////////////////////////////////////////////////////
  initialize(tab, sizes, bases, nt2::memory::no_padding(), data );

  //////////////////////////////////////////////////////////////////////////////
  // array type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////

  for(pos[0]=1;pos[0]<=5;++pos[0])
    NT2_TEST_EQUAL(dereference<1UL>(tab,pos), 10*(1+pos[0]) );
}
