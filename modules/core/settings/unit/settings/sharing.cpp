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
    typedef option<nt2::shared_, nt2::tag::sharing_, some_semantic_> opt;

    NT2_TEST( (match_option< nt2::shared_, nt2::tag::sharing_ >::value) );
  }

  {
    typedef option<nt2::owned_, nt2::tag::sharing_, some_semantic_> opt;

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
                      ,(option< _, nt2::tag::sharing_, some_semantic_>)
                      ,(shared_)
                      );

  NT2_TEST_EXPR_TYPE( (owned_())
                      ,(option< _, nt2::tag::sharing_, some_semantic_>)
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
                            , some_semantic_
                            >::type
                    )
                  , owned_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::sharing_
                            , some_semantic_
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
                            , some_semantic_
                            >::type
                    )
                  , (shared_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(owned_)
                            , nt2::tag::sharing_
                            , some_semantic_
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
                            , some_semantic_
                            >::type
                    )
                  , shared_
                  );

  NT2_TEST_TYPE_IS( (option < settings(owned_,shared_)
                            , nt2::tag::sharing_
                            , some_semantic_
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

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(shared_,owned_)
                                      )
                            , nt2::tag::sharing_
                            , some_semantic_
                            >::type
                    )
                  , shared_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(owned_,shared_)
                                      )
                            , nt2::tag::sharing_
                            , some_semantic_
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
                              , container<int, settings(), some_semantic_>
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
  using nt2::memory::array_buffer;
  using nt2::memory::fixed_allocator;
  using boost::simd::allocator_adaptor;

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , container < int
                                          , settings(automatic_, of_size_<2,7>)
                                          , some_semantic_
                                          >
                              >
                      )
                    , (array_buffer<int, integral_c<std::size_t,14> >)
                    );

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , container < int
                                          , settings( dynamic_
                                                    , of_size_<2,2>
                                                    , std::allocator<int>
                                                    )
                                          , some_semantic_
                                          >
                              >
                      )
                    , (buffer<int,allocator_adaptor<std::allocator<int> > >)
                    );
}
