//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::container_traits"

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/container_traits.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check pointer_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pointer )
{
  using nt2::meta::pointer_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( pointer_<float>::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( pointer_<float&>::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( pointer_<float const>::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( pointer_<float const&>::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( pointer_< vector<float> >::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( pointer_< vector<float>& >::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( pointer_< vector<float> const >::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( pointer_< vector<float> const& >::type
                  , float const*
                  );
}

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Allocator>
  struct value_of< std::vector<T, Allocator> >
  {
    typedef T type;
  };
} } }

////////////////////////////////////////////////////////////////////////////////
// Check reference_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( reference )
{
  using nt2::meta::reference_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( reference_<float>::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( reference_<float&>::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( reference_<float const>::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( reference_<float const&>::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( reference_< vector<float> >::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( reference_< vector<float>& >::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( reference_< vector<float> const >::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( reference_< vector<float> const& >::type
                  , float const&
                  );
}


////////////////////////////////////////////////////////////////////////////////
// Check pointer_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( const_pointer )
{
  using nt2::meta::const_pointer_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( const_pointer_<float>::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( const_pointer_<float&>::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( const_pointer_<float const>::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( const_pointer_<float const&>::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( const_pointer_< vector<float> >::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( const_pointer_< vector<float>& >::type
                  , float*
                  );

  NT2_TEST_TYPE_IS( const_pointer_< vector<float> const >::type
                  , float const*
                  );

  NT2_TEST_TYPE_IS( const_pointer_< vector<float> const& >::type
                  , float const*
                  );
}

////////////////////////////////////////////////////////////////////////////////
// Check const_reference_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( const_reference )
{
  using nt2::meta::const_reference_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( const_reference_<float>::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( const_reference_<float&>::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( const_reference_<float const>::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( const_reference_<float const&>::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( const_reference_< vector<float> >::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( const_reference_< vector<float>& >::type
                  , float&
                  );

  NT2_TEST_TYPE_IS( const_reference_< vector<float> const >::type
                  , float const&
                  );

  NT2_TEST_TYPE_IS( const_reference_< vector<float> const& >::type
                  , float const&
                  );
}

////////////////////////////////////////////////////////////////////////////////
// Check value_type_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( value_type )
{
  using nt2::meta::value_type_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( value_type_< float >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< float& >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< float const >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< float const& >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< vector<float> >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< vector<float>& >::type
                  , float
                  );

  NT2_TEST_TYPE_IS( value_type_< vector<float> const >::type
                  , float
                  );
  NT2_TEST_TYPE_IS( value_type_< vector<float> const& >::type
                  , float
                  );
}

////////////////////////////////////////////////////////////////////////////////
// Check size_type_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_type )
{
  using nt2::meta::size_type_;
  using boost::is_same;
  using std::vector;

  NT2_TEST_TYPE_IS( size_type_< float >::type
                  , std::size_t
                  );

  NT2_TEST_TYPE_IS( size_type_< float& >::type
                  , std::size_t
                  );

  NT2_TEST_TYPE_IS( size_type_< float const >::type
                  , std::size_t
                  );

  NT2_TEST_TYPE_IS( size_type_< float const& >::type
                  , std::size_t
                  );

  NT2_TEST_TYPE_IS( size_type_< vector<float> >::type
                  , std::size_t
                  );
  NT2_TEST_TYPE_IS( size_type_< vector<float>& >::type
                  , std::size_t
                  );
  NT2_TEST_TYPE_IS( size_type_< vector<float> const >::type
                  , std::size_t
                  );
  NT2_TEST_TYPE_IS( size_type_< vector<float> const& >::type
                  , std::size_t
                  );
}
