//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <boost/simd/memory/allocator.hpp>

#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( sharing_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;

  {
    NT2_TEST( (match_option< nt2::shared_, nt2::tag::sharing_ >::value) );
  }

  {
    NT2_TEST( (match_option< nt2::owned_, nt2::tag::sharing_ >::value) );
  }
}

NT2_TEST_CASE( single_sharing_ )
{
  using nt2::shared_;
  using nt2::owned_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (shared_())
                      ,(option< _, nt2::tag::sharing_, some_kind_>)
                      ,(shared_)
                      );

  NT2_TEST_EXPR_TYPE( (owned_())
                      ,(option< _, nt2::tag::sharing_, some_kind_>)
                      ,(owned_)
                      );
}

NT2_TEST_CASE( sharing_default )
{
  using nt2::shared_;
  using nt2::owned_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , owned_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , owned_
                  );
}

NT2_TEST_CASE( single_settings_sharing_ )
{
  using nt2::shared_;
  using nt2::owned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(shared_)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , (shared_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(owned_)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , (owned_)
                  );
}

NT2_TEST_CASE( multi_settings_sharing_ )
{
  using nt2::shared_;
  using nt2::owned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(shared_,owned_)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , shared_
                  );

  NT2_TEST_TYPE_IS( (option < settings(owned_,shared_)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , owned_
                  );
}

NT2_TEST_CASE( nested_settings_sharing_ )
{
  using nt2::shared_;
  using nt2::owned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  typedef settings shadow(double,int);
  typedef settings option1(shared_,owned_);
  typedef settings option2(owned_,shared_);

  NT2_TEST_TYPE_IS( (option < settings(shadow,option1)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , shared_
                  );

  NT2_TEST_TYPE_IS( (option < settings(shadow,option2)
                            , nt2::tag::sharing_
                            , some_kind_
                            >::type
                    )
                  , (owned_)
                  );
}

template<class U, class C>
struct  apply_
{
  typedef typename boost::mpl::apply <U , C>::type type;
};

NT2_TEST_CASE( shared_output )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::shared_;
  using nt2::memory::container;
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;

  NT2_TEST_EXPR_TYPE( shared_()
                    , (apply_ < _
                              , container<some_kind_, int, settings()>
                              >
                      )
                    , (buffer<int, fixed_allocator<int> >)
                    );
}

NT2_TEST_CASE( owned_output )
{
  using boost::mpl::_;
  using boost::mpl::integral_c;
  using nt2::owned_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::memory::buffer;
  using nt2::memory::container;
  using boost::simd::aligned_array;
  using nt2::memory::fixed_allocator;

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , container < some_kind_
                                          , int
                                          , settings(automatic_, of_size_<2,7>)
                                          >
                              >
                      )
                    , (aligned_array<int, 14 >)
                    );

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , container < some_kind_
                                          , int
                                          , settings( dynamic_
                                                    , of_size_<2,2>
                                                    , std::allocator<int>
                                                    )
                                          >
                              >
                      )
                    , (buffer<int,std::allocator<int> >)
                    );
}
