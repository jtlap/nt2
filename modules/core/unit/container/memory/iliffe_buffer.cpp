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
#include <nt2/core/container/memory/fixed_allocator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>

#define DIMS                                    \
(boost::mpl::size_t<1>)(boost::mpl::size_t<2>)  \
(boost::mpl::size_t<3>)(boost::mpl::size_t<4>)  \
/**/

//==============================================================================
// iliffe_buffer type has some dimensions
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_dimensions, DIMS )
{
  using nt2::memory::iliffe_buffer;
  using nt2::meta::dimensions_of;
  using nt2::memory::buffer;

  typedef iliffe_buffer<T, buffer<int>, buffer<int*> > type;
  
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
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<T>, void >())
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
  ( (iliffe_buffer<boost::mpl::size_t<1>, buffer<int>, void >())
  , (apply_model<_,T>)
  , (iliffe_buffer<boost::mpl::size_t<1>, buffer<T>, T >)
  );
}

//==============================================================================
// 1D iliffe_buffer models Buffer Concept
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_1D_as_buffer, NT2_TYPES )
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer constructor
  //////////////////////////////////////////////////////////////////////////////
  typedef iliffe_buffer<boost::mpl::size_t<1>,buffer<T>,void> tab_t;
  tab_t tab(5,-2);

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports R/W access through Position
  //////////////////////////////////////////////////////////////////////////////
  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    tab[pos] = T(10*(3+pos));

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    NT2_TEST_EQUAL(tab[pos], T(10*(3+pos)) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being rebased
  //////////////////////////////////////////////////////////////////////////////
  tab.rebase( 0 );

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    tab[pos] = T(2*(1+pos));

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    NT2_TEST_EQUAL(tab[pos], T(2*(1+pos) ) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being resized
  //////////////////////////////////////////////////////////////////////////////
  tab.resize( 6u );

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    tab[pos] = T(10*(1+pos));

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    NT2_TEST_EQUAL(tab[pos], T(10*(1+pos)) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being restructured
  //////////////////////////////////////////////////////////////////////////////
  tab.restructure( 4u, 1 );

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    tab[pos] = T(pos);

  for(typename tab_t::difference_type pos=tab.lower();pos <= tab.upper();++pos)
    NT2_TEST_EQUAL(tab[pos], T(pos) );
}

//==============================================================================
// 2D iliffe_buffer models Buffer Concept
//==============================================================================
NT2_TEST_CASE_TPL( iliffe_buffer_2D_as_buffer, (double) ) //NT2_TYPES )
{
  using nt2::memory::iliffe_buffer;
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer constructor
  //////////////////////////////////////////////////////////////////////////////
  typedef
  iliffe_buffer< boost::mpl::size_t<2>, buffer<T>, buffer<T*> > tab_t;

  boost::array<std::size_t,2> sz = {{ 3 ,  5 }};
  boost::array<std::size_t,2> bs = {{ -1, -2 }};
  
  tab_t tab( sz, bs );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports R/W access through 1D Position
  //////////////////////////////////////////////////////////////////////////////
  for(int i=-1;i<=13;i++)
    tab[i] = 2+i;

  for(int i=-1;i<=13;++i)
    NT2_TEST_EQUAL( tab[i], (2+i) );
    
  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports R/W access through 2D Position
  //////////////////////////////////////////////////////////////////////////////
  for(int j=-2;j<=2;++j)
    for(int i=-1;i<=1;++i)
      tab[ boost::fusion::vector_tie(i,j) ] = (2+i) + 10*(3+j);

  for(int j=-2;j<=2;++j)
    for(int i=-1;i<=1;++i)
      NT2_TEST_EQUAL( tab[ boost::fusion::vector_tie(i,j) ], (2+i) + 10*(3+j) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being rebased externally
  //////////////////////////////////////////////////////////////////////////////
  boost::array<std::size_t,2> bs2 = {{ 0, 1 }};
  tab.rebase( bs2 );

  for(int j=1;j<=5;++j)
    for(int i=0;i<=2;++i)
      tab[ boost::fusion::vector_tie(i,j) ] = j*(i+1);

  for(int j=1;j<=5;++j)
    for(int i=0;i<=2;++i)
      NT2_TEST_EQUAL( tab[ boost::fusion::vector_tie(i,j) ], j*(i+1) );

  //////////////////////////////////////////////////////////////////////////////
  // iliffe_buffer type supports being resized externally
  //////////////////////////////////////////////////////////////////////////////
  boost::array<std::size_t,2> ss2 = {{ 6, 6 }};
  tab.resize( ss2 );
  
  for(int j=1;j<=6;++j)
    for(int i=0;i<=5;++i)
      tab[ boost::fusion::vector_tie(i,j) ] = (i+1) + 20*j;

  for(int j=1;j<=6;++j)
    for(int i=0;i<=5;++i)
      NT2_TEST_EQUAL( tab[ boost::fusion::vector_tie(i,j) ], (i+1) + 20*j );
}
