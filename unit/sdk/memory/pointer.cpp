/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::pointer"

#include <nt2/sdk/memory/pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/memory/meta/make_aligned.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ inner types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_typedefs)
{
  using nt2::memory::pointer_;
  using boost::is_same;

  NT2_TEST( (is_same<pointer_<double>::element_type   ,double       >::value) );
  NT2_TEST( (is_same<pointer_<void>::element_type     ,void         >::value) );
  NT2_TEST( (is_same<pointer_<double>::pointer        ,double*      >::value) );
  NT2_TEST( (is_same<pointer_<void>::pointer          ,void*        >::value) );
  NT2_TEST( (is_same<pointer_<double>::reference      ,double&      >::value) );
  NT2_TEST( (is_same<pointer_<void>::reference        ,void         >::value) );
  NT2_TEST( (is_same<pointer_<double>::const_reference,double const&>::value) );
  NT2_TEST( (is_same<pointer_<void>::const_reference  ,void         >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_default_ctor)
{
  using nt2::memory::pointer_;

  pointer_<double>  pd;
  pointer_<void>    pv;

  NT2_TEST( !pd.get() );
  NT2_TEST( !pv.get() );
}
////////////////////////////////////////////////////////////////////////////////
// Test pointer_ explicit ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_explicit_ctor)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd( &v );
  pointer_<void>   pv( &v );

  NT2_TEST_EQUAL(pd.get(),&v);
  NT2_TEST_EQUAL(pv.get(),&v);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ copy ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_copy_ctor)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd( &v );
  pointer_<double> pdc( pd );
  pointer_<void>   pv( &v );
  pointer_<void>   pvc( pv );

  NT2_TEST_EQUAL(pdc.get(),&v);
  NT2_TEST_EQUAL(pvc.get(),&v);

}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ reset
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_reset_ptr)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd;
  pointer_<void>   pv;

  NT2_TEST(!pd);
  NT2_TEST(!pv);

  pd.reset( &v );
  pv.reset( &v );

  NT2_TEST_EQUAL(pd.get(),&v);
  NT2_TEST_EQUAL(pv.get(),&v);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ reset from pointer_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_reset_pointer)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd(&v);
  pointer_<double> pdc;
  pointer_<void>   pv(&v);
  pointer_<void>   pvc;

  pdc.reset( pd );
  pvc.reset( pv );

  NT2_TEST_EQUAL(pdc.get(),&v);
  NT2_TEST_EQUAL(pvc.get(),&v);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ swap
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_swap)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd(&v);
  pointer_<double> pdc;
  pointer_<void>   pv(&v);
  pointer_<void>   pvc;

  pdc.swap( pd );
  pvc.swap( pv );

  NT2_TEST_EQUAL(pdc.get(),&v);
  NT2_TEST_EQUAL(pvc.get(),&v);
  NT2_TEST(!pd);
  NT2_TEST(!pv);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ assignment
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_assignment)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd(&v);
  pointer_<double> pdc;
  pointer_<void>   pv(&v);
  pointer_<void>   pvc;

  pdc = pd;
  pvc = pv;

  NT2_TEST_EQUAL(pd.get(),&v);
  NT2_TEST_EQUAL(pv.get(),&v);
  NT2_TEST_EQUAL(pdc.get(),&v);
  NT2_TEST_EQUAL(pvc.get(),&v);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ dereferencing
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_dereferencing)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd(&v);

  v = 3.14159;
  NT2_TEST_EQUAL(*pd,3.14159);

  *pd = 2.1778;
  NT2_TEST_EQUAL(v,2.1778);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ array like access
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(pointer_array_dereferencing)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<double>::type v;
  pointer_<double> pd(&v);

  v = 3.14159;
  NT2_TEST_EQUAL(pd[0],3.14159);

  pd[0] = 2.1778;
  NT2_TEST_EQUAL(v,2.1778);
}

////////////////////////////////////////////////////////////////////////////////
// Test pointer_ member access
////////////////////////////////////////////////////////////////////////////////
struct foo
{
  int v;
  void f() { v++; };
};

NT2_TEST_CASE(pointer_member)
{
  using nt2::meta::make_aligned;
  using nt2::memory::pointer_;

  make_aligned<foo>::type v;
  pointer_<foo> pd(&v);

  v.v = 314;
  NT2_TEST_EQUAL(pd->v,314);

  pd->f();
  NT2_TEST_EQUAL(v.v,315);
}
