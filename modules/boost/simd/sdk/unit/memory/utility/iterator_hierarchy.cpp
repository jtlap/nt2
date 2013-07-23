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

NT2_TEST_CASE_TPL(typed_ptr, BOOST_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;
  using boost::dispatch::meta::iterator_;

  T* p = 0;
  T* const pc = 0;
  T const* cp = 0;
  T const* const cpc = 0;

  typedef typename boost::dispatch::meta::hierarchy_of<T,T*>::type base;
  typedef typename boost::dispatch::meta::hierarchy_of<T,T const*>::type cbase;

  NT2_TEST_EXPR_TYPE( p   , (nth_hierarchy<_, int_<0> >), iterator_<base>  );
  NT2_TEST_EXPR_TYPE( pc  , (nth_hierarchy<_, int_<0> >), iterator_<base>  );
  NT2_TEST_EXPR_TYPE( cp  , (nth_hierarchy<_, int_<0> >), iterator_<cbase> );
  NT2_TEST_EXPR_TYPE( cpc , (nth_hierarchy<_, int_<0> >), iterator_<cbase> );
}
