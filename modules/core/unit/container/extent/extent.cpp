//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//=============================================================================
#define NT2_UNIT_MODULE "nt2::extent"

#include <nt2/core/container/extent/extent.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/core/settings/size.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#define M0(z,n,t) (nt2::BOOST_PP_CAT(BOOST_PP_CAT(_,n),D))
#define DYN_DIM_LIST BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

//=============================================================================
// Does extent<> behaves correctly in meta?
//=============================================================================
NT2_TEST_CASE_TPL( meta_extent, DYN_DIM_LIST )
{
  using boost::is_same;
  using nt2::container::extent;
  using nt2::of_size_;
  using boost::dispatch::meta::value_of;
  using boost::dispatch::meta::hierarchy_of;

  using boost::dispatch::meta::expr_;
  using boost::dispatch::meta::extent_;
  using boost::dispatch::meta::table_;
  
  NT2_TEST(( is_same< T
                    , typename value_of< extent<T> >::type
                    >::value
          ));

  NT2_TEST(( is_same< expr_< extent_< extent<T>
                                    , of_size_<1,T::static_size> 
                                    > 
                           , nt2::container::domain
                           , boost::proto::tag::terminal
                           >
                    , typename hierarchy_of< extent<T> >::type
                    >::value
          ));
}

//=============================================================================
// Does extent<_0D> behaves correctly ?
//=============================================================================
NT2_TEST_CASE( _0d )
{
  using nt2::_0D;
  using nt2::container::extent;
  using boost::dispatch::meta::expr_;
  using boost::dispatch::meta::table_;
  using boost::dispatch::meta::array_;

  //============================================================================
  // Default construction
  //============================================================================
  extent<_0D> x;
  NT2_TEST( x.empty() );
  NT2_TEST_EQUAL( x.size()  , 0);
  NT2_TEST_EQUAL( x.size(1) , 1);
  NT2_TEST_EQUAL( x.size(2) , 1);
  NT2_TEST_EQUAL( x.lower(0), 1);
  NT2_TEST_EQUAL( x.upper(0), 1);
  NT2_TEST_EQUAL( x(1)      , 1);
  NT2_TEST_EQUAL( x(2)      , 1);
  NT2_TEST_EQUAL( x(3)      , 1);
  NT2_TEST_EQUAL( x(4)      , 1);

  NT2_TEST_EQUAL( nt2::size(x)(1), 1);
  NT2_TEST_EQUAL( nt2::size(x)(2), 1);

  //============================================================================
  // Copy construction
  //============================================================================
  extent<_0D> y(x);
  NT2_TEST( y.empty() );
  NT2_TEST_EQUAL( y.size()  , 0);
  NT2_TEST_EQUAL( y.size(1) , 1);
  NT2_TEST_EQUAL( y.size(2) , 1);
  NT2_TEST_EQUAL( y.lower(0), 1);
  NT2_TEST_EQUAL( y.upper(0), 1);
  NT2_TEST_EQUAL( y(1)      , 1);
  NT2_TEST_EQUAL( y(2)      , 1);
  NT2_TEST_EQUAL( y(3)      , 1);
  NT2_TEST_EQUAL( y(4)      , 1);
  
//  NT2_TEST_EQUAL( nt2::size(y), 0);    
}

//=============================================================================
// Does extent<_nD> behaves correctly ?
//=============================================================================
NT2_TEST_CASE_TPL ( _nD, DYN_DIM_LIST )
{
  using nt2::container::extent;

  //============================================================================
  // Default construction
  //============================================================================
  extent<T> x;
  std::size_t dims = T::static_size;

  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , dims  );

  NT2_TEST_EQUAL( x(1)      , 0     );
  NT2_TEST_EQUAL( x.size(1) , 1     );
  NT2_TEST_EQUAL( x.size(2) , dims  );
  NT2_TEST_EQUAL( x.lower(1), 1     );
  NT2_TEST_EQUAL( x.lower(2), 1     );
  NT2_TEST_EQUAL( x.upper(1), 1     );
  NT2_TEST_EQUAL( x.upper(2), dims  );

  for(std::size_t i= 3; i<= dims;++i)
  {
    NT2_TEST_EQUAL( x(i)      , 1 );
    NT2_TEST_EQUAL( x.size(i) , 1 );
    NT2_TEST_EQUAL( x.lower(i), 1 );
    NT2_TEST_EQUAL( x.upper(i), 1 );
  }

  //============================================================================
  // Copy construction
  //============================================================================
  extent<T> y(x);
  NT2_TEST_EQUAL( y(1)      , 0     );
  NT2_TEST_EQUAL( y.size(1) , 1     );
  NT2_TEST_EQUAL( y.size(2) , dims  );
  NT2_TEST_EQUAL( y.lower(1), 1     );
  NT2_TEST_EQUAL( y.lower(2), 1     );
  NT2_TEST_EQUAL( y.upper(1), 1     );
  NT2_TEST_EQUAL( y.upper(2), dims  );

  for(std::size_t i= 3; i<= dims;++i)
  {
    NT2_TEST_EQUAL( y(i)      , 1 );
    NT2_TEST_EQUAL( y.size(i) , 1 );
    NT2_TEST_EQUAL( y.lower(i), 1 );
    NT2_TEST_EQUAL( y.upper(i), 1 );
  }
}

//=============================================================================
// Does extent<of_size_<...>> behaves correctly ?
//=============================================================================
NT2_TEST_CASE( default_ctor_static )
{
  using nt2::of_size_;
  using nt2::container::extent;

  //============================================================================
  // Default construction
  //============================================================================ 
  extent< of_size_<9,7,5> > x;
    
  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , 3  );

  NT2_TEST_EQUAL( x(1)      , 9 );
  NT2_TEST_EQUAL( x(2)      , 7 );
  NT2_TEST_EQUAL( x(3)      , 5 );

  NT2_TEST_EQUAL( x.size(1) , 1 );
  NT2_TEST_EQUAL( x.size(2) , 3 );
  NT2_TEST_EQUAL( x.size(3) , 1 );
  NT2_TEST_EQUAL( x.lower(1), 1 );
  NT2_TEST_EQUAL( x.lower(2), 1 );
  NT2_TEST_EQUAL( x.lower(3), 1 );
  NT2_TEST_EQUAL( x.upper(1), 1 );
  NT2_TEST_EQUAL( x.upper(2), 3 );
  NT2_TEST_EQUAL( x.upper(3), 1 );

  //============================================================================
  // Copy construction
  //============================================================================
  extent< of_size_<9,7,5> > y(x);
  
  NT2_TEST( !y.empty() );
  NT2_TEST_EQUAL( y.size()  , 3  );

  NT2_TEST_EQUAL( y(1)      , 9 );
  NT2_TEST_EQUAL( y(2)      , 7 );
  NT2_TEST_EQUAL( y(3)      , 5 );

  NT2_TEST_EQUAL( y.size(1) , 1 );
  NT2_TEST_EQUAL( y.size(2) , 3 );
  NT2_TEST_EQUAL( y.size(3) , 1 );
  NT2_TEST_EQUAL( y.lower(1), 1 );
  NT2_TEST_EQUAL( y.lower(2), 1 );
  NT2_TEST_EQUAL( y.lower(3), 1 );
  NT2_TEST_EQUAL( y.upper(1), 1 );
  NT2_TEST_EQUAL( y.upper(2), 3 );
  NT2_TEST_EQUAL( y.upper(3), 1 );
}

//=============================================================================
// Does extent<_1D> behaves correctly with value construction ?
//=============================================================================
NT2_TEST_CASE( value_1D )
{
  using nt2::_1D;
  using nt2::container::extent;

  //============================================================================
  // Default construction
  //============================================================================ 
  extent< _1D > x(1337);
    
  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , 1  );

  NT2_TEST_EQUAL( x(1)      , 1337 );
  
  NT2_TEST_EQUAL( x.size(1) , 1 );
  NT2_TEST_EQUAL( x.size(2) , 1 );
  NT2_TEST_EQUAL( x.lower(1), 1 );
  NT2_TEST_EQUAL( x.lower(2), 1 );
  NT2_TEST_EQUAL( x.upper(1), 1 );
  NT2_TEST_EQUAL( x.upper(2), 1 );

  //============================================================================
  // Copy construction
  //============================================================================
  extent< _1D > y(x);
  
  NT2_TEST( !y.empty() );
  NT2_TEST_EQUAL( y.size()  , 1  );

  NT2_TEST_EQUAL( y(1)      , 1337 );

  NT2_TEST_EQUAL( y.size(1) , 1 );
  NT2_TEST_EQUAL( y.size(2) , 1 );
  NT2_TEST_EQUAL( y.lower(1), 1 );
  NT2_TEST_EQUAL( y.lower(2), 1 );
  NT2_TEST_EQUAL( y.upper(1), 1 );
  NT2_TEST_EQUAL( y.upper(2), 1 );
}


//=============================================================================
// Does extent<_1D> behaves correctly with value construction ?
//=============================================================================
NT2_TEST_CASE( value_2D )
{
  using nt2::_2D;
  using nt2::container::extent;

  //============================================================================
  // Default construction
  //============================================================================ 
  extent< _2D > x(13,37);
    
  NT2_TEST( !x.empty() );
  NT2_TEST_EQUAL( x.size()  , 2  );

  NT2_TEST_EQUAL( x(1)      , 13 );
  NT2_TEST_EQUAL( x(2)      , 37 );
  
  NT2_TEST_EQUAL( x.size(1) , 1 );
  NT2_TEST_EQUAL( x.size(2) , 2 );
  NT2_TEST_EQUAL( x.lower(1), 1 );
  NT2_TEST_EQUAL( x.lower(2), 1 );
  NT2_TEST_EQUAL( x.upper(1), 1 );
  NT2_TEST_EQUAL( x.upper(2), 2 );

  //============================================================================
  // Copy construction
  //============================================================================
  extent< _2D > y(x);
  
  NT2_TEST( !y.empty() );
  NT2_TEST_EQUAL( y.size()  , 2  );

  NT2_TEST_EQUAL( y(1)      , 13 );
  NT2_TEST_EQUAL( y(2)      , 37 );

  NT2_TEST_EQUAL( y.size(1) , 1 );
  NT2_TEST_EQUAL( y.size(2) , 2 );
  NT2_TEST_EQUAL( y.lower(1), 1 );
  NT2_TEST_EQUAL( y.lower(2), 1 );
  NT2_TEST_EQUAL( y.upper(1), 1 );
  NT2_TEST_EQUAL( y.upper(2), 2 );
}
