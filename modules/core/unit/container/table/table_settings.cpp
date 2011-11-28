/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table "

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

////////////////////////////////////////////////////////////////////////////////
// table type has some dimensions
////////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::meta::dimensions_of;

  // test default dimension of table
  NT2_TEST_EQUAL( (dimensions_of<table<T> >::value), 4UL) ;

  NT2_TEST_EQUAL( (dimensions_of<table<T,_1D> >::value), 1UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_2D> >::value), 2UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_3D> >::value), 3UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<T,_4D> >::value), 4UL) ;
}


////////////////////////////////////////////////////////////////////////////////
// table type has some value
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( table_values, NT2_TYPES )
{
  using boost::dispatch::meta::value_of;
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using boost::mpl::_;

  table<T,_1D> t1D;
  table<T,_2D> t2D;
  table<T,_3D> t3D;
  table<T,_4D> t4D;

  NT2_TEST_EXPR_TYPE(t1D, value_of<_>, T );
  NT2_TEST_EXPR_TYPE(t2D, value_of<_>, T );
  NT2_TEST_EXPR_TYPE(t3D, value_of<_>, T );
  NT2_TEST_EXPR_TYPE(t4D, value_of<_>, T );

}

////////////////////////////////////////////////////////////////////////////////
// table type has a model
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( table_models, NT2_TYPES )
{
  using boost::is_same;
  using boost::dispatch::meta::model_of;
  using boost::mpl::apply;
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;

  typedef typename model_of< table<T,_1D> >::type model1d;
  typedef typename model_of< table<T,_2D> >::type model2d;
  typedef typename model_of< table<T,_3D> >::type model3d;
  typedef typename model_of< table<T,_4D> >::type model4d;


  NT2_TEST((is_same<typename apply<model1d,float>::type, table<float,_1D> >::value ));
  NT2_TEST((is_same<typename apply<model2d,float>::type, table<float,_2D> >::value ));
  NT2_TEST((is_same<typename apply<model3d,float>::type, table<float,_3D> >::value ));
  NT2_TEST((is_same<typename apply<model4d,float>::type, table<float,_4D> >::value ));

}

////////////////////////////////////////////////////////////////////////////////
// table type has storage_order
////////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL( table_storage_order ,NT2_TYPES)
{
  using nt2::table;
  using nt2::meta::storage_order_of;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::matlab_order_;
  using nt2::C_order_;
  using nt2::fortran_order_;
  using boost::mpl::_;

  using nt2::settings;

  //Test default table storage order
  table<T> a0;
  NT2_TEST_EXPR_TYPE(a0, storage_order_of<_>, matlab_order_ );

  table<T,_1D> t1D;
  table<T,_2D> t2D;
  table<T,_3D> t3D;
  table<T,_4D> t4D;

  NT2_TEST_EXPR_TYPE(t1D, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t2D, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t3D, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t4D, storage_order_of<_>, matlab_order_ );


  //Test storage order in settings

  //test matlab storage order
  table<T,settings(_1D,matlab_order_)> t1D_;
  table<T,settings(_2D,matlab_order_)> t2D_;
  table<T,settings(_3D,matlab_order_)> t3D_;
  table<T,settings(_4D,matlab_order_)> t4D_;

  NT2_TEST_EXPR_TYPE(t1D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t2D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t3D_, storage_order_of<_>, matlab_order_ );
  NT2_TEST_EXPR_TYPE(t4D_, storage_order_of<_>, matlab_order_ );


  //test C storage order
  table<T,settings(_1D,C_order_)> t1D__;
  table<T,settings(_2D,C_order_)> t2D__;
  table<T,settings(_3D,C_order_)> t3D__;
  table<T,settings(_4D,C_order_)> t4D__;

  NT2_TEST_EXPR_TYPE(t1D__, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(t2D__, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(t3D__, storage_order_of<_>, C_order_ );
  NT2_TEST_EXPR_TYPE(t4D__, storage_order_of<_>, C_order_ );

  //test Fortran storage order
  table<T,settings(_1D,fortran_order_)> _t1D__;
  table<T,settings(_2D,fortran_order_)> _t2D__;
  table<T,settings(_3D,fortran_order_)> _t3D__;
  table<T,settings(_4D,fortran_order_)> _t4D__;

  NT2_TEST_EXPR_TYPE(_t1D__, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_t2D__, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_t3D__, storage_order_of<_>, fortran_order_ );
  NT2_TEST_EXPR_TYPE(_t4D__, storage_order_of<_>, fortran_order_ );


}
