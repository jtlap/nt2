//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/storage_size.hpp>
#include <nt2/core/settings/storage_duration.hpp>

#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( storage_size_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;

  {
    NT2_TEST( (match_option< nt2::storage_size_<16> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::storage_size_<16> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::storage_size_<16> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, 16u );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::automatic_ );
  }

  {
    NT2_TEST( (match_option< nt2::storage_size_<-1> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::storage_size_<-1> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::storage_size_<-1> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, std::size_t(-1) );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::dynamic_ );
  }

  {
    NT2_TEST( (match_option< nt2::_1D , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::_1D , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::_1D , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, std::size_t(-1) );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::dynamic_ );
  }

  {
    NT2_TEST( (match_option< nt2::_2D , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::_2D , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::_2D , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, std::size_t(-1) );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::dynamic_ );
  }

  {
    NT2_TEST( (match_option< nt2::_3D , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::_3D , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::_3D , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, std::size_t(-1) );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::dynamic_ );
  }

  {
    NT2_TEST( (match_option< nt2::_4D , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::_4D , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::_4D , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, std::size_t(-1) );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::dynamic_ );
  }

  {
    NT2_TEST( (match_option< nt2::of_size_<1> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::of_size_<1> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::of_size_<1> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, 1u );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::automatic_ );
  }

  {
    NT2_TEST( (match_option< nt2::of_size_<2,4> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::of_size_<2,4> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::of_size_<2,4> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, 8u );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::automatic_ );
  }

  {
    NT2_TEST( (match_option< nt2::of_size_<2,4,6> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::of_size_<2,4,6> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::of_size_<2,4,6> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, 48u );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::automatic_ );
  }

  {
    NT2_TEST( (match_option< nt2::of_size_<2,4,6,10> , nt2::tag::storage_size_ >::value) );
    typedef option<nt2::of_size_<2,4,6,10> , nt2::tag::storage_size_, some_kind_> opt;
    typedef option<nt2::of_size_<2,4,6,10> , nt2::tag::storage_duration_, some_kind_> opt2;
    NT2_TEST_EQUAL( opt::type::storage_size_type::value, 480u );
    NT2_TEST_TYPE_IS( opt2::type::storage_duration_type, nt2::automatic_ );
  }
}

NT2_TEST_CASE( single_storage_size_ )
{
  using nt2::of_size_;
  using nt2::storage_size_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (storage_size_<16>())
                      ,(option< _, nt2::tag::storage_size_, some_kind_>)
                      ,(storage_size_<16>)
                      );

  NT2_TEST_EXPR_TYPE( (storage_size_<-1>())
                      ,(option< _, nt2::tag::storage_size_, some_kind_>)
                      ,(storage_size_<-1>)
                      );

  NT2_TEST_EXPR_TYPE( (of_size_<3,3>())
                      ,(option< _, nt2::tag::storage_size_, some_kind_>)
                      ,(of_size_<3,3>)
                      );
}

NT2_TEST_CASE( storage_size_default )
{
  using nt2::storage_size_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , storage_size_<-1>
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , storage_size_<-1>
                  );
}

NT2_TEST_CASE( single_settings_storage_size_ )
{
  using nt2::of_size_;
  using nt2::storage_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(storage_size_<13>)
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , (storage_size_<13>)
                  );

  NT2_TEST_TYPE_IS( (option < settings(of_size_<5,3>)
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , (of_size_<5,3>)
                  );
}

NT2_TEST_CASE( multi_settings_storage_size_ )
{
  using nt2::storage_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(storage_size_<13>,storage_size_<37>)
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , storage_size_<13>
                  );

  NT2_TEST_TYPE_IS( (option < settings(storage_size_<37>,storage_size_<13>)
                            , nt2::tag::storage_size_
                            , some_kind_
                            >::type
                    )
                  , storage_size_<37>
                  );
}
