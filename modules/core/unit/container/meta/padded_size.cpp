//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::padded_size"

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <nt2/core/utility/of_size/pad.hpp>
#include <nt2/core/utility/of_size/of_size.hpp>
#include <nt2/sdk/meta/padded_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check padded_size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( padded_size )
{
  using nt2::of_size_;
  using boost::mpl::int_;
  using nt2::meta::padded_size;

  NT2_TEST_EQUAL( (padded_size< of_size_<2,3,4>::values_type, int_<1>, int_<1> >::value)
                , 2*3*4
                );

  NT2_TEST_EQUAL( (padded_size< of_size_<5,4,2>::values_type, int_<32>, int_<1> >::value)
                , 64
                );

  NT2_TEST_EQUAL( (padded_size< of_size_<5,4,2>::values_type, int_<1>, int_<32> >::value)
                , 256
                );

  NT2_TEST_EQUAL( (padded_size< of_size_<5,4,5>::values_type, int_<128>, int_<8> >::value)
                , 256
                );
}

////////////////////////////////////////////////////////////////////////////////
// Check pad
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pad )
{
  using nt2::pad;
  using nt2::of_size_;
  using boost::mpl::int_;
  using boost::fusion::at_c;
  
  NT2_TEST_EQUAL( at_c<0>( pad(of_size_<6,1,2,3>(), 4) ),  8 );
  NT2_TEST_EQUAL( at_c<0>( pad(of_size_<6,1,2,3>(), 8) ),  8 );
  NT2_TEST_EQUAL( at_c<0>( pad(of_size_<6,1,2,3>(),16) ), 16 );
  NT2_TEST_EQUAL( at_c<0>( pad(of_size_<6,1,2,3>(),32) ), 32 );
  NT2_TEST_EQUAL( at_c<1>( pad(of_size_<6,1,2,3>(),16) ), 1  );
  NT2_TEST_EQUAL( at_c<2>( pad(of_size_<6,1,2,3>(),16) ), 2  );
  NT2_TEST_EQUAL( at_c<3>( pad(of_size_<6,1,2,3>(),16) ), 3  );  
}
