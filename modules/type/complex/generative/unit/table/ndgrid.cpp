//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ndgrid.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( ndgrid, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::repmat;
  using nt2::reshape;

  nt2::table<cT> ix = nt2::_(T(1),T(7));
  nt2::table<cT> iy = nt2::_(T(1),T(3));
  nt2::table<cT> iz = nt2::_(T(1),T(2));
  nt2::table<cT> w,x,y,z;

  nt2::table<cT> rx = repmat( reshape(ix,7,1),1,3);
  nt2::table<cT> ry = repmat( reshape(iy,1,3),7,1);

  x = nt2::ndgrid(ix,iy);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());

  nt2::tie(x,y) = nt2::ndgrid(ix,iy);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());

  rx = repmat( reshape(ix,7,1,1),1,3,2);
  ry = repmat( reshape(iy,1,3,1),7,1,2);
  nt2::table<cT> rz = repmat( reshape(iz,1,1,2),7,3,1);

  x = nt2::ndgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());

  nt2::tie(x,y) = nt2::ndgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());

  nt2::tie(x,y,z) = nt2::ndgrid(ix,iy,iz);
  NT2_TEST_EQUAL(x,rx);
  NT2_TEST_EQUAL(x.extent(),rx.extent());
  NT2_TEST_EQUAL(y,ry);
  NT2_TEST_EQUAL(y.extent(),ry.extent());
  NT2_TEST_EQUAL(z,rz);
  NT2_TEST_EQUAL(z.extent(),rz.extent());
}
