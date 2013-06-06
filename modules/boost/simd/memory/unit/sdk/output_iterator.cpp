/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/memory/output_iterator.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <vector>

NT2_TEST_CASE_TPL(types, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_iterator;
  using boost::simd::pack;

  NT2_TEST_TYPE_IS( typename iterator_traits< output_iterator<T> >::value_type
                  , (pack<T>)
                  );
}

NT2_TEST_CASE_TPL(distance, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_iterator;
  using boost::simd::output_begin;
  using boost::simd::output_end;
  using boost::simd::pack;

  std::vector<T> data(pack<T>::static_size*3);

  output_iterator<T> b = output_begin(data.begin());
  output_iterator<T> e = output_end(data.end());

  NT2_TEST_EQUAL( std::distance(b,e), 3);
}

NT2_TEST_CASE_TPL(iteration, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_iterator;
  using boost::simd::output_begin;
  using boost::simd::output_end;
  using boost::simd::pack;
  using boost::simd::splat;

  std::vector<T> ref(pack<T>::static_size*3);
  std::vector<T> data(pack<T>::static_size*3);

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = (i/pack<T>::static_size)+1;

  output_iterator<T> b = output_begin(data.begin());
  output_iterator<T> e = output_end(data.end());

  int i=0;
  while(b != e)
    *b++ = splat< pack<T> >(++i);

  NT2_TEST_EQUAL( data, ref );
}
