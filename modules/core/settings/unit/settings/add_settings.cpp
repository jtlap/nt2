//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/add_settings.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( add_nothing_to_settings )
{
  using nt2::settings;
  using nt2::meta::add_settings;

  typedef settings empty();
  typedef settings base(int);

  NT2_TEST_TYPE_IS( add_settings<empty>::type         , empty );
  NT2_TEST_TYPE_IS( add_settings<base>::type          , int   );
  NT2_TEST_TYPE_IS( (add_settings<empty,empty>::type) , empty );
  NT2_TEST_TYPE_IS( (add_settings<base,empty>::type)  , base  );
}

NT2_TEST_CASE( add_settings_to_nothing )
{
  using nt2::settings;
  using nt2::meta::add_settings;

  typedef settings empty();

  NT2_TEST_TYPE_IS( (add_settings<empty, int>::type)
                  , int
                  );
}

NT2_TEST_CASE( add_option_to_setting )
{
  using nt2::settings;
  using nt2::meta::add_settings;

  typedef settings base(float);

  NT2_TEST_TYPE_IS( (add_settings<float, int>::type)
                  , (settings(int,float))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base, int>::type)
                  , (settings(int,base))
                  );
}

NT2_TEST_CASE( add_options_to_setting )
{
  using nt2::settings;
  using nt2::meta::add_settings;

  typedef settings base(float);
  typedef settings newer(int);

  NT2_TEST_TYPE_IS( (add_settings<base, newer>::type)
                  , (settings(int,float))
                  );
}

NT2_TEST_CASE( add_options_to_settings )
{
  using nt2::settings;
  using nt2::meta::add_settings;

  typedef settings base(void*);
  typedef settings base2(void*,void**);
  typedef settings new2(int,float);
  typedef settings new3(int,float,char);
  typedef settings new4(int,float,char,double);

  NT2_TEST_TYPE_IS( (add_settings<base, new2>::type)
                  , (settings(int,float,void*))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base, new3>::type)
                  , (settings(int,float,char,void*))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base, new4>::type)
                  , (settings(int,float,char,double,void*))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base2, new2>::type)
                  , (settings(int,float,base2))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base2, new3>::type)
                  , (settings(int,float,char,base2))
                  );

  NT2_TEST_TYPE_IS( (add_settings<base2, new4>::type)
                  , (settings(int,float,char,double,base2))
                  );
}
