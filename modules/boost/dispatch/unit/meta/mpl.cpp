//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::hierarchy_of mpl int"

#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

#include <boost/mpl/int.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE(hierarchy_of_mpl_int_)
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::int32_;
  using boost::dispatch::meta::scalar_;
  using boost::dispatch::meta::mpl_integral_;
  using boost::dispatch::meta::nth_hierarchy;
  using boost::dispatch::meta::hierarchy_of;

  int_<4> int4;

  typedef hierarchy_of< int_<4>::value_type, int_<4> >::type base;

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<0> >)
                    , mpl_integral_< base >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<1> >)
                    , mpl_integral_< base::parent >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<2> >)
                    , mpl_integral_< base::parent::parent >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<3> >)
                    , mpl_integral_< base::parent::parent::parent >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<4> >)
                    , mpl_integral_< base::parent::parent::parent::parent >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<5> >)
                    , mpl_integral_< base::parent::parent::parent::parent::parent >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<6> >)
                    , mpl_integral_ < base::parent::parent::parent
                                          ::parent::parent::parent
                                    >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<7> >)
                    , mpl_integral_ < base::parent::parent::parent
                                          ::parent::parent::parent
                                          ::parent
                                    >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<8> >)
                    , mpl_integral_ < base::parent::parent::parent
                                          ::parent::parent::parent
                                          ::parent::parent
                                    >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<9> >)
                    , mpl_integral_ < base::parent::parent::parent
                                          ::parent::parent::parent
                                          ::parent::parent::parent
                                    >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<10> >)
                    , mpl_integral_ < base::parent::parent::parent
                                          ::parent::parent::parent
                                          ::parent::parent::parent
                                          ::parent
                                    >
                    );

  NT2_TEST_EXPR_TYPE( int4
                    , (nth_hierarchy< _, int_<21> >)
                    , (hierarchy_of< int_<4>::value_type, int_<4> >::type)
                    );
}
