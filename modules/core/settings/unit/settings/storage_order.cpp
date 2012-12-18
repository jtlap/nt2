/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::storage_order "

#include <nt2/core/settings/storage_order.hpp>
#include <nt2/sdk/meta/permute_view.hpp>

#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// storage order apply
////////////////////////////////////////////////////////////////////////////////
template<class T, class U>
struct matlab_apply_ : nt2::matlab_order_::apply<T, U> {};

template<class T, class U>
struct fortran_apply_ : nt2::fortran_order_::apply<T, U> {};

template<class T, class U>
struct C_apply_ : nt2::C_order_::apply<T, U> {};

NT2_TEST_CASE( storage_order_apply)
{
  using boost::mpl::apply;
  using nt2::matlab_order_;
  using nt2::fortran_order_;
  using nt2::C_order_;
  using boost::mpl::_;

  typedef boost::mpl::size_t<4> size;
  typedef boost::mpl::size_t<0> dim_0;
  typedef boost::mpl::size_t<1> dim_1;
  typedef boost::mpl::size_t<2> dim_2;
  typedef boost::mpl::size_t<3> dim_3;

  //////////////////////////////////////////////////////////////////////////////
  // matlab_storage order
  //////////////////////////////////////////////////////////////////////////////
  NT2_TEST_EXPR_TYPE((dim_0()),(C_apply_<size,_>),(boost::mpl::size_t<3>));
  NT2_TEST_EXPR_TYPE((dim_1()),(C_apply_<size,_>),(boost::mpl::size_t<2>));
  NT2_TEST_EXPR_TYPE((dim_2()),(C_apply_<size,_>),(boost::mpl::size_t<1>));
  NT2_TEST_EXPR_TYPE((dim_3()),(C_apply_<size,_>),(boost::mpl::size_t<0>));

  //////////////////////////////////////////////////////////////////////////////
  // fortran_storage order
  //////////////////////////////////////////////////////////////////////////////
  NT2_TEST_EXPR_TYPE((dim_0()),(fortran_apply_<size,_>),(boost::mpl::size_t<0>));
  NT2_TEST_EXPR_TYPE((dim_1()),(fortran_apply_<size,_>),(boost::mpl::size_t<1>));
  NT2_TEST_EXPR_TYPE((dim_2()),(fortran_apply_<size,_>),(boost::mpl::size_t<2>));
  NT2_TEST_EXPR_TYPE((dim_3()),(fortran_apply_<size,_>),(boost::mpl::size_t<3>));

  //////////////////////////////////////////////////////////////////////////////
  // C_storage order
  //////////////////////////////////////////////////////////////////////////////
  NT2_TEST_EXPR_TYPE((dim_0()),(matlab_apply_<size,_>),(boost::mpl::size_t<0>));
  NT2_TEST_EXPR_TYPE((dim_1()),(matlab_apply_<size,_>),(boost::mpl::size_t<1>));
  NT2_TEST_EXPR_TYPE((dim_2()),(matlab_apply_<size,_>),(boost::mpl::size_t<2>));
  NT2_TEST_EXPR_TYPE((dim_3()),(matlab_apply_<size,_>),(boost::mpl::size_t<3>));
}

NT2_TEST_CASE( storage_order_permute_view )
{
  using boost::array;
  using nt2::meta::permute_view;
  using nt2::matlab_order_;
  using nt2::C_order_;
  using nt2::fortran_order_;
  using boost::fusion::at_c;

  typedef const boost::array<std::size_t,4> Seq;
  Seq sizes = {{5,2,4,3}};

  permute_view<Seq,C_order_> C_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<3>(C_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<2>(C_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<1>(C_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<0>(C_permuted));

  permute_view<Seq,matlab_order_> matlab_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<0>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<1>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<2>(matlab_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<3>(matlab_permuted));

  permute_view<Seq,fortran_order_> fortran_permuted(sizes);

  NT2_TEST_EQUAL( at_c<0>(sizes), at_c<0>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<1>(sizes), at_c<1>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<2>(sizes), at_c<2>(fortran_permuted));
  NT2_TEST_EQUAL( at_c<3>(sizes), at_c<3>(fortran_permuted));
}
