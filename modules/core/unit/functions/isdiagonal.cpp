/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isdiagonal function"

#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isdiagonal )
{
  NT2_TEST( nt2::isdiagonal('e') );
  NT2_TEST( nt2::isdiagonal(1)   );
  NT2_TEST( nt2::isdiagonal(1.)  );
  NT2_TEST( nt2::isdiagonal(1.f) );
}

NT2_TEST_CASE( container_isdiagonal )
{
  nt2::table<double > a =  nt2::eye(4);
  NT2_TEST( nt2::isdiagonal(a));
  a = nt2::eye(4); 
  NT2_TEST( nt2::isdiagonal(a));
  a = nt2::eye(4,1);
  NT2_TEST( nt2::isdiagonal(a));
  a = nt2::eye(4); 
  NT2_TEST( nt2::isdiagonal(a));
  a = nt2::ones(4, 1); 
  NT2_TEST( !nt2::isdiagonal(a));
  a = nt2::ones(4,1,1); 
  NT2_TEST( !nt2::isdiagonal(a));
  a = nt2::ones(4,11,1); 
  NT2_TEST( !nt2::isdiagonal(a));

//   NT2_TEST( nt2::isdiagonal( nt2::eye(4))       );
//   NT2_TEST( nt2::isdiagonal( nt2::eye(4,1))     );
//   NT2_TEST( nt2::isdiagonal( nt2::eye(4,3))     );

//   NT2_TEST( !nt2::isdiagonal( nt2::ones(4))       );
//   NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1))     );
//   NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1,1))   );
//   NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1,1,1)) );

}
NT2_TEST_CASE( container_isalmostdiagonal )
{
  nt2::table<double > a =  nt2::eye(4)+0.5*nt2::Eps<double>();
  NT2_TEST( nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::eye(4)+0.5*nt2::Eps<double>(); 
  NT2_TEST( nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::eye(4)+0.5*nt2::Eps<double>(); 
  NT2_TEST( nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::eye(4,1)+0.5*nt2::Eps<double>();
  NT2_TEST( nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::ones(4, 1)+0.5*nt2::Eps<double>(); 
  NT2_TEST( !nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::ones(4,1,1)+0.5*nt2::Eps<double>(); 
  NT2_TEST( !nt2::isdiagonal(a, nt2::Eps<double>()));
  a = nt2::ones(4,11,1)+0.5*nt2::Eps<double>(); 
  NT2_TEST( !nt2::isdiagonal(a, nt2::Eps<double>()));

  NT2_TEST( nt2::isdiagonal( nt2::eye(4))       );
  NT2_TEST( nt2::isdiagonal( nt2::eye(4,1))     );
  NT2_TEST( nt2::isdiagonal( nt2::eye(4,3))     );

  NT2_TEST( !nt2::isdiagonal( nt2::ones(4))       );
  NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1))     );
  NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1,1))   );
  NT2_TEST( !nt2::isdiagonal( nt2::ones(4,1,1,1)) );

}
