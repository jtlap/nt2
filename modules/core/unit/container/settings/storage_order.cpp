/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::storage_order "

#include <nt2/table.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/sdk/meta/permute_view.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// storage order apply
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_order_apply)
{
  using boost::is_same;
  using nt2::table;
  using boost::mpl::int_;
  using boost::mpl::apply;
  using nt2::matlab_order_;
  using nt2::fortran_order_;
  using nt2::C_order_;

  typedef int_<4> size;
  typedef int_<0> dim_0;
  typedef int_<1> dim_1;
  typedef int_<2> dim_2;
  typedef int_<3> dim_3;


////////////////////////////////////////////////////////////////////////////////
// matlab_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<matlab_order_::apply<size, dim_0> ::type, int_<3>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_1> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_2> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_3> ::type, int_<0>  >::value ));


////////////////////////////////////////////////////////////////////////////////
// fortran_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<fortran_order_::apply<size, dim_0> ::type, int_<3>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_1> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_2> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_3> ::type, int_<0>  >::value ));


////////////////////////////////////////////////////////////////////////////////
// C_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<C_order_::apply<size, dim_0> ::type, int_<0>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_1> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_2> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_3> ::type, int_<3>  >::value ));

}


NT2_TEST_CASE( storage_order_permute_view )
{
  using boost::array;
  using boost::is_same;
  using nt2::meta::permute_view;
  using nt2::matlab_order_;
  using nt2::C_order_;
  using nt2::fortran_order_;
  using boost::fusion::at_c;


  typedef boost::array<std::size_t,4> Seq;
  Seq sizes = {{5,2,4,3}};



  permute_view<Seq,C_order_> C_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<0>(C_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<1>(C_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<2>(C_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<3>(C_permuted));


  permute_view<Seq,matlab_order_> matlab_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<3>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<2>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<1>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<0>(matlab_permuted));


  permute_view<Seq,fortran_order_> fortran_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<3>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<2>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<1>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<0>(fortran_permuted));

}
