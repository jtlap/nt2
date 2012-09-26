#ifndef NT2_MODULES_TRIGONOMETRIC_EXHAUSTIVE_SIMD_SIN_FLOAT_HPP
#define NT2_MODULES_TRIGONOMETRIC_EXHAUSTIVE_SIMD_SIN_FLOAT_HPP

template <class T>
void exhaust_test_sin(const T& mini,const T& maxi);

template <>
void exhaust_test_sin<float>(const float& mini,const float& maxi)
  {
    typedef boost::simd::native<float,ext_t>  n_t;
    typedef typename nt2::meta::as_integer<n_t>::type   in_t;
    typedef typename nt2::meta::call<nt2::tag::sin_(float)>::type r_t;
    typedef typename nt2::meta::call<nt2::tag::sin_(n_t)>::type r_t;
    float mini = Valmin<float>;
    float maxi = Valmax<float>;
    const nt2::uint32_t N = nt2::meta::cardinal_of<n_t>::value;
    const in_t vN = nt2::splat<in_t>(N);
    const nt2::uint32_t M =  10;
    nt2::uint32_t histo[M+1];
    for(nt2::uint32_t i = 0; i < M; i++) histo[i] = 0;
    float a[N];
    a[0] = mini;
    for(nt2::uint32_t i = 1; i < N; i++)
      a[i] = nt2::successor(a[i-1], 1);
    n_t a0 = nt2::load<n_t>(&a[0],0);
    nt2::uint32_t k = 0,j = 0;
    std::cout << "a line of points to wait for... be patient!" << std::endl;
    for(; a0[N-1] < maxi; a0 = nt2::successor(a0, vN))
      {
        n_t z =  nt2::sin(a0);
        for(nt2::uint32_t i = 0; i < N; i++)
          {
             float v = repfunc(a0[i]);
             float sz = z[i];
             ++histo[nt2::min(M, nt2::iround(2*nt2::ulpdist(v, sz)))];
             ++k;
             if (k%100000000 == 0){
               std::cout << "." << std::flush; ++j;
               if (j == 80){std::cout << std::endl; j = 0;}
             }
          }
        }
      std::cout << "exhaustive test for " << std::endl;
      std::cout << " nt2::sin versus ::cephes_sinl(a0) " << std::endl;
      std::cout << " in simd mode and float type" << std::endl;
      for(nt2::uint32_t i = 0; i < M; i++)
        std::cout << i/2.0 << " -> " << histo[i] << std::endl;
      std::cout << k << " values computed" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      for(nt2::uint32_t i = 0; i < M; i++)
        std::cout << i/2.0 << " -> "
                  << (histo[i]*100.0/k) << "%" << std::endl;
  }



#endif
