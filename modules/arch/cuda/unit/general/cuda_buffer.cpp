//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/cuda/cuda.hpp>
#include <nt2/sdk/cuda/memory/buffer.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/size.hpp>

#include <iostream>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( cuda_buffer_d, (double) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  T alpha = 5.;
  int incr =1;

  cublasDscal( cudabuffer.size(), alpha ,cudabuffer.data(), incr);
  cudabuffer.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer.size(), entry.size() );
}

NT2_TEST_CASE_TPL( cuda_buffer_d_affect_htd, (double) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(10);
  cudabuffer = entry ;
  T alpha = 5.;
  int incr =1;

  cublasDscal( cudabuffer.size(), alpha ,cudabuffer.data(), incr);
  cudabuffer.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer.size(), entry.size() );
}

NT2_TEST_CASE_TPL( cuda_buffer_d_affect_dtd, (double) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result  = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  nt2::memory::cuda_buffer<T> cudabuffer_1;
  cudabuffer_1 = cudabuffer ;
  T alpha = 5.;
  int incr =1;

  cublasDscal( cudabuffer_1.size(), alpha ,cudabuffer_1.data(), incr);
  cudabuffer_1.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer_1.size(), entry.size() );
}

NT2_TEST_CASE_TPL( cuda_buffer_d_copy, (double) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result  = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  nt2::memory::cuda_buffer<T> cudabuffer_1(cudabuffer);
  T alpha = 5.;
  int incr =1;

  cublasDscal( cudabuffer_1.size(), alpha ,cudabuffer_1.data(), incr);
  cudabuffer_1.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer_1.size(), entry.size() );
}

NT2_TEST_CASE_TPL( cuda_buffer_f, (float) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  T alpha = 5.;
  int incr =1;

  cublasSscal( cudabuffer.size(), alpha ,cudabuffer.data(), incr);
  cudabuffer.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer.size(), entry.size() );
}


NT2_TEST_CASE_TPL( cuda_buffer_f_copy, (float) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result  = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  nt2::memory::cuda_buffer<T> cudabuffer_1(cudabuffer);
  T alpha = 5.;
  int incr =1;

  cublasSscal( cudabuffer_1.size(), alpha ,cudabuffer_1.data(), incr);
  cudabuffer_1.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer_1.size(), entry.size() );
}


NT2_TEST_CASE_TPL( cuda_buffer_f_affect_htd, (float) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(10);
  cudabuffer = entry ;
  T alpha = 5.;
  int incr =1;

  cublasSscal( cudabuffer.size(), alpha ,cudabuffer.data(), incr);
  cudabuffer.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer.size(), entry.size() );
}

NT2_TEST_CASE_TPL( cuda_buffer_f_affect_dtd, (float) )
{
  nt2::table<T> entry  = nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> result  = T(5)* nt2::ones(10,1, nt2::meta::as_<T>());
  nt2::table<T> cuda_dst(nt2::of_size(10,1));
  nt2::memory::cuda_buffer<T> cudabuffer(entry);
  nt2::memory::cuda_buffer<T> cudabuffer_1;
  cudabuffer_1 = cudabuffer ;
  T alpha = 5.;
  int incr =1;

  cublasSscal( cudabuffer_1.size(), alpha ,cudabuffer_1.data(), incr);
  cudabuffer_1.data(cuda_dst);

  NT2_TEST_EQUAL(result, cuda_dst );
  NT2_TEST_EQUAL(cudabuffer_1.size(), entry.size() );
}
