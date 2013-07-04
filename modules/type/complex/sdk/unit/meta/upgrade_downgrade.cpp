//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(complex, NT2_TYPES)
{
  using boost::dispatch::meta::upgrade;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;
  using std::complex;

  NT2_TEST_TYPE_IS( typename upgrade< complex<T> >::type
                  , complex< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< complex<T>& >::type
                  , complex< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< complex<T> const >::type
                  , complex< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< complex<T> const& >::type
                  , complex< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< complex<T> >::type
                  , complex< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< complex<T>& >::type
                  , complex< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< complex<T> const >::type
                  , complex< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< complex<T> const& >::type
                  , complex< typename downgrade<T>::type >
                  );
}

NT2_TEST_CASE_TPL(dry, NT2_TYPES)
{
  using boost::dispatch::meta::upgrade;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;
  using nt2::dry;

  NT2_TEST_TYPE_IS( typename upgrade< nt2::dry<T> >::type
                  , dry< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< nt2::dry<T>& >::type
                  , dry< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< nt2::dry<T> const >::type
                  , dry< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename upgrade< nt2::dry<T> const& >::type
                  , dry< typename upgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< nt2::dry<T> >::type
                  , dry< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< nt2::dry<T>& >::type
                  , dry< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< nt2::dry<T> const >::type
                  , dry< typename downgrade<T>::type >
                  );

  NT2_TEST_TYPE_IS( typename downgrade< nt2::dry<T> const& >::type
                  , dry< typename downgrade<T>::type >
                  );
}
