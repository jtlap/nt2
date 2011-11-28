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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// table type and storage order
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( storage_order, NT2_TYPES )
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
// table and matlab_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<matlab_order_::apply<size, dim_0> ::type, int_<3>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_1> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_2> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<matlab_order_::apply<size, dim_3> ::type, int_<0>  >::value ));


////////////////////////////////////////////////////////////////////////////////
// table and fortran_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<fortran_order_::apply<size, dim_0> ::type, int_<3>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_1> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_2> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<fortran_order_::apply<size, dim_3> ::type, int_<0>  >::value ));


////////////////////////////////////////////////////////////////////////////////
// table and C_storage order
////////////////////////////////////////////////////////////////////////////////

  NT2_TEST((is_same<C_order_::apply<size, dim_0> ::type, int_<0>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_1> ::type, int_<1>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_2> ::type, int_<2>  >::value ));
  NT2_TEST((is_same<C_order_::apply<size, dim_3> ::type, int_<3>  >::value ));

}

