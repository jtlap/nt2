/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::class_ function"

#include <nt2/table.hpp>
#include <nt2/include/functions/class.hpp>

#include <boost/mpl/placeholders.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( scalar_class, NT2_TYPES )
{
  using nt2::class_;
  using boost::mpl::_;
  using nt2::meta::as_;

  T x;
  NT2_TEST_EXPR_TYPE( (class_(x))
                    , (_)
                    , (as_<T>)
                    );
}

NT2_TEST_CASE_TPL( table_class, NT2_TYPES )
{
  using nt2::class_;
  using boost::mpl::_;
  using nt2::meta::as_;

  nt2::table<T> x;
  NT2_TEST_EXPR_TYPE( (class_(x))
                    , (_)
                    , (as_<T>)
                    );
}

NT2_TEST_CASE_TPL( expr_class, NT2_TYPES )
{
  using nt2::class_;
  using boost::mpl::_;
  using nt2::meta::as_;

  nt2::table<T> x;
  NT2_TEST_EXPR_TYPE( (class_(x+x*T(2)))
                    , (_)
                    , (as_<T>)
                    );
}
