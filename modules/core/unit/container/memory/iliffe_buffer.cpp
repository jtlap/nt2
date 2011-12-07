//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory iliffe_buffer"

#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/container/memory/iliffe_buffer.hpp>

/*

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

#include <boost/array.hpp>
#include <boost/type_traits/is_same.hpp>*/

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#define DIMS                                                                   \
(boost::mpl::size_t<1>) \
/**/

//==============================================================================
// iliffe_buffer type has some dimensions
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dimensions, DIMS )
{
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;

  typedef iliffe_buffer<T, buffer<int>, buffer<int> > type;
  
  NT2_TEST_EQUAL((dimensions_of<type>::value), T::value );
}

//==============================================================================
// iliffe_buffer type has some value
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_values, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<T>, buffer<float> >())
  , value_of<_>
  , T
  );
}

//==============================================================================
// iliffe_buffer type has a model
//==============================================================================
template<class T, class U>
struct  apply_model
      : boost::mpl::apply < typename boost::dispatch::meta::model_of<T>::type
                          , U
                          >
{};

NT2_TEST_CASE_TPL( iliffe_buffer_models, NT2_TYPES )
{
  using boost::dispatch::meta::model_of;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using boost::mpl::_;
  
  NT2_TEST_EXPR_TYPE
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<int>, buffer<float> >())
  , (apply_model<_,T>)
  , (iliffe_buffer<boost::mpl::size_t<1>, buffer<T>, buffer<T> >)
  );
}

//==============================================================================
// 1D iliffe_buffer models Buffer Concept
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_1D_as_buffer, NT2_TYPES )
{
  using nt2::memory::allocator;
  using nt2::memory::dereference;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  boost::array<std::size_t,1> szs = {{5}};
  boost::array<std::size_t,1> bs = {{-2}};

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer constructor
  //////////////////////////////////////////////////////////////////////////////
  iliffe_buffer<boost::mpl::size_t<1>,buffer<T>,buffer<T> > tab(szs,bs);

  boost::array<std::ptrdiff_t,1> pos;

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(pos[0]=-2;pos[0]<=2;++pos[0])
    dereference(tab,pos) = T(10*(1+pos[0]));

  for(pos[0]=-2;pos[0]<=2;++pos[0])
    NT2_TEST_EQUAL(dereference(tab,pos), T(10*(1+pos[0])) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  boost::array<std::size_t,1> bases_2 = {{0}};
  rebase(tab, bases_2 );

  for(pos[0]=0;pos[0]<=4;++pos[0])
    dereference(tab,pos) = T(2*(1+pos[0]));

  for(pos[0]=0;pos[0]<=4;++pos[0])
    NT2_TEST_EQUAL(dereference(tab,pos), T(2*(1+pos[0]) ) );

/*
* boost::array<std::size_t,1> sizes_2 = {{6}};

  //////////////////////////////////////////////////////////////////////////////
  // array type supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  resize(tab, sizes_2 );

  for(pos[0]=-2;pos[0]<=4;++pos[0])
    dereference(tab,pos) = int(10*(1+pos[0]));

  for(pos[0]=-2;pos[0]<=4;++pos[0])
    NT2_TEST_EQUAL(dereference(tab,pos), 10*(1+pos[0]) );
 */
}
/*
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
  using nt2::matlab_order_;

  iliffe_buffer<2,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > tab;

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

  for(pos[1]=0;pos[1]<=1;++pos[1]) {
    for(pos[0]=-2;pos[0]<=2;++pos[0]){
      dereference<2UL>(tab,pos) = int(10*(1+pos[1]) + (1+pos[0]));
    }
  }

  std::cout << std::endl;
  for(pos[1]=0;pos[1]<=1;++pos[1]) {
    for(pos[0]=-2;pos[0]<=2;++pos[0]){
      NT2_TEST_EQUAL(dereference<2UL>(tab,pos), 10*(1+pos[1]) + (1+pos[0]) );
    }
  }


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
  using nt2::matlab_order_;

  iliffe_buffer<3,int,buffer<int>,buffer<byte>,matlab_order_,T,allocator<int> > tab;

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
*/
