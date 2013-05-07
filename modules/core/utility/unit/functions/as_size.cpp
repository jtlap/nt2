//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::as_size function"

#include <nt2/table.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/as_size.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( sequence_as_size )
{
  using nt2::as_size;
  using nt2::of_size;

  NT2_TEST_EQUAL( of_size(3)      , as_size( of_size(3)       ) );
  NT2_TEST_EQUAL( of_size(3,4)    , as_size( of_size(3,4)     ) );
  NT2_TEST_EQUAL( of_size(3,4,5)  , as_size( of_size(3,4,5)   ) );
  NT2_TEST_EQUAL( of_size(3,4,5,6), as_size( of_size(3,4,5,6) ) );
}

NT2_TEST_CASE( expr_as_size )
{
  using nt2::as_size;
  using nt2::of_size;
  nt2::table<std::size_t> ref;

  ref.resize( of_size(1) );
  ref(1) = 3;
  NT2_TEST_EQUAL( of_size(3,3) , as_size( ref ) );

  ref.resize( of_size(1,2) );
  ref(1) = 3; ref(2) = 4;
  NT2_TEST_EQUAL( of_size(3,4) , as_size( ref ) );

  ref.resize( of_size(1,3) );
  ref(1) = 3; ref(2) = 4; ref(3) = 5;
  NT2_TEST_EQUAL( of_size(3,4,5) , as_size( ref ) );

  ref.resize( of_size(1,4) );
  ref(1) = 3; ref(2) = 4; ref(3) = 5; ref(4) = 6;
  NT2_TEST_EQUAL( of_size(3,4,5,6) , as_size( ref ) );
}

NT2_TEST_CASE( scalars_as_size )
{
  using nt2::as_size;
  using nt2::of_size;
  using nt2::of_size_;
  using boost::mpl::int_;

  NT2_TEST_EQUAL( of_size(3,3)    , as_size( 3      ) );
  NT2_TEST_EQUAL( of_size(3,4)    , as_size( 3,4    ) );
  NT2_TEST_EQUAL( of_size(3,4,5)  , as_size( 3,4,5  ) );
  NT2_TEST_EQUAL( of_size(3,4,5,6), as_size( 3,4,5,6) );

  NT2_TEST_EXPR_TYPE( as_size(int_<3>())
                    , boost::mpl::_
                    , (of_size_<3,3>)
                    );

  NT2_TEST_EXPR_TYPE( as_size(int_<3>(),int_<4>())
                    , boost::mpl::_
                    , (of_size_<3,4>)
                    );

  NT2_TEST_EXPR_TYPE( as_size(int_<3>(),int_<4>(),int_<5>())
                    , boost::mpl::_
                    , (of_size_<3,4,5>)
                    );

  NT2_TEST_EXPR_TYPE( as_size(int_<3>(),int_<4>(),int_<5>(),int_<6>())
                    , boost::mpl::_
                    , (of_size_<3,4,5,6>)
                    );
}
