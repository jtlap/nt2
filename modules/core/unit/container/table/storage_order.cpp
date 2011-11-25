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
  using nt2::matlab_so_;
  using nt2::c_so_;
  using nt2::storage_order_;

  typedef boost::mpl::int_<2> size;
  typedef boost::mpl::int_<1> dim;

  NT2_TEST((is_same<storage_order_<matlab_so_, size, dim>::type, boost::mpl::int_<0>  >::value ));
  NT2_TEST((is_same<storage_order_<c_so_, size, dim>::type, boost::mpl::int_<1>  >::value ));

}

