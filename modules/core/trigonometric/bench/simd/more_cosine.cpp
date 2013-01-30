//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_BENCH_MODULE "nt2 trigonometric toolbox - cosine/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// timing Test behavior of trigonometric components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/trigonometric/include/functions/cosine.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/toolbox/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cmath>
typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;

//////////////////////////////////////////////////////////////////////////////
// simd runtime benchmark for functor<cosine_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cosine_;
using nt2::tag::fast_cos_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, (V1) ,(V2))
namespace nnnn01 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(fast_cos_,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nnnn1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(fast_cos_,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nnn01 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_pio4_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nnn1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_pio4_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn01 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_small>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_small>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n01 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace n011 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_small>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace n11 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_small>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn011 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn11 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_medium>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn1 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::direct_medium>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}
namespace nn0111 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_medium>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
}
namespace nn111 {
  typedef float T;
  typedef boost::dispatch::meta::as_integer<T>::type iT;
  typedef boost::simd::native<T,ext_t> vT;
  NT2_TIMING(cosine_<nt2::clipped_medium>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
}


// namespace n11 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


// namespace n02 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace n2 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }

// namespace n21 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }

// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }

// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,T(-1.0e15),T(1.0e15))))
// }

// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::small_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


// namespace m01 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace m02 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }namespace m1 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace m2 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace m11 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace m21 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace m111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace m211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace m111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace m211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace m111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }
// namespace m211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::medium_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }

// namespace n01 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }
// namespace n02 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-nt2::Pi<T>()/4,nt2::Pi<T>()/4)))
// }namespace n1 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace n2 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-20*nt2::Pi<T>(),20*nt2::Pi<T>())))
// }
// namespace n11 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n21 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-60*nt2::Pi<T>(),60*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,-10000*nt2::Pi<T>(),10000*nt2::Pi<T>())))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,T(-1.0e38),T(1.0e38))))
// }
// namespace n111 {
//   typedef float T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }
// namespace n211 {
//   typedef double T;
//   typedef boost::dispatch::meta::as_integer<T>::type iT;
//   typedef boost::simd::native<T,ext_t> vT;
//   NT2_TIMING(cosine_<nt2::big_>,(RS(vT,nt2::Nan < T>(),nt2::Nan < T>())))
// }


#undef RS
