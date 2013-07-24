//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/int.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE(void_ptr)
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;
  using boost::dispatch::meta::generic_;
  using boost::dispatch::meta::iterator_;
  using boost::dispatch::meta::void_;

  void* p = 0;
  void* const pc = 0;

  NT2_TEST_EXPR_TYPE( p
                    , (nth_hierarchy<_, int_<0> >)
                    , iterator_<generic_<void_<void*> > >
                    );

  NT2_TEST_EXPR_TYPE( pc
                    , (nth_hierarchy<_, int_<0> >)
                    , iterator_<generic_<void_<void*> > >
                    );
}

NT2_TEST_CASE(typed_ptr)
{
  using boost::dispatch::meta::nth_hierarchy;
  using boost::dispatch::meta::unspecified_;
  using boost::dispatch::meta::iterator_;
  using boost::dispatch::meta::scalar_;
  using boost::dispatch::meta::single_;
  using boost::mpl::int_;
  using boost::mpl::_;

  float*       p = 0;
  float const*  c = 0;
  float* BOOST_DISPATCH_RESTRICT r = 0;
  float const * BOOST_DISPATCH_RESTRICT q = 0;

  NT2_TEST_EXPR_TYPE( p , (nth_hierarchy<_, int_<0> >), iterator_< scalar_< single_<float*> > >  );
  NT2_TEST_EXPR_TYPE( p , (nth_hierarchy<_, int_<16> >), iterator_< unspecified_<float*> >  );

  NT2_TEST_EXPR_TYPE( c , (nth_hierarchy<_, int_<0> >), iterator_< scalar_< single_<float const*> > >  );
  NT2_TEST_EXPR_TYPE( c , (nth_hierarchy<_, int_<16> >), iterator_< unspecified_<float const*> >  );

  NT2_TEST_EXPR_TYPE( r , (nth_hierarchy<_, int_<0> >), iterator_< scalar_< single_<float* BOOST_DISPATCH_RESTRICT> > > );
  NT2_TEST_EXPR_TYPE( r , (nth_hierarchy<_, int_<16> >), iterator_< unspecified_<float* BOOST_DISPATCH_RESTRICT> > );

  NT2_TEST_EXPR_TYPE( q , (nth_hierarchy<_, int_<0> >), iterator_< scalar_< single_<float const* BOOST_DISPATCH_RESTRICT> > > );
  NT2_TEST_EXPR_TYPE( q , (nth_hierarchy<_, int_<16> >), iterator_< unspecified_<float const* BOOST_DISPATCH_RESTRICT> > );
}

NT2_TEST_CASE(typed_ptr_const)
{
  using boost::dispatch::meta::nth_hierarchy;
  using boost::dispatch::meta::unspecified_;
  using boost::dispatch::meta::iterator_;
  using boost::dispatch::meta::scalar_;
  using boost::dispatch::meta::single_;
  using boost::mpl::int_;
  using boost::mpl::_;

  float* const       p = 0;
  float const*  const c = 0;
  float* const BOOST_DISPATCH_RESTRICT r = 0;
  float const * const BOOST_DISPATCH_RESTRICT q = 0;

  NT2_TEST_EXPR_TYPE( p
                    , (nth_hierarchy<_, int_<0> >)
                    , iterator_< scalar_< single_<float*> > >
                    );

  NT2_TEST_EXPR_TYPE( p
                    , (nth_hierarchy<_, int_<16> >)
                    , iterator_< unspecified_<float*> >
                    );

  NT2_TEST_EXPR_TYPE( c
                    , (nth_hierarchy<_, int_<0> >)
                    , iterator_< scalar_< single_<float const*> > >
                    );

  NT2_TEST_EXPR_TYPE( c
                    , (nth_hierarchy<_, int_<16> >)
                    , iterator_< unspecified_<float const*> >
                    );

  NT2_TEST_EXPR_TYPE( r
                    , (nth_hierarchy<_, int_<0> >)
                    , iterator_< scalar_< single_<float* BOOST_DISPATCH_RESTRICT> > >
                    );

  NT2_TEST_EXPR_TYPE( r
                    , (nth_hierarchy<_, int_<16> >)
                    , iterator_< unspecified_<float* BOOST_DISPATCH_RESTRICT> >
                    );

  NT2_TEST_EXPR_TYPE( q , (nth_hierarchy<_, int_<0> >), iterator_< scalar_< single_<float const* BOOST_DISPATCH_RESTRICT> > > );
  NT2_TEST_EXPR_TYPE( q , (nth_hierarchy<_, int_<16> >), iterator_< unspecified_<float const* BOOST_DISPATCH_RESTRICT> > );
}
