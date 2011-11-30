[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['returns a scalar integer value composed by the highiest bits.',
                          'of each vector element'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'special' : ['reduction'],  
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_']
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],   
             'simd_included' : ['#include <boost/simd/include/functions/bits.hpp>',
                                '#include <boost/simd/include/functions/shri.hpp>'],
             'cover_included' : ['#include <boost/simd/include/functions/bits.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
            },
         'specific_values' : {
             'signed_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::hmsb(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::b_and(a0, boost::simd::Signmask<r_t>()) != 0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        int z = 0;",
                        "        int N = cardinal_of<n_t>::value;",
                        "        for(int i = 0; i< N; ++i)",
                        "        {",
                        "          z |= boost::simd::bits(a0[i]) >> (sizeof(iT)*CHAR_BIT - 1) << (N-i-1);"
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
            },
        },
    },
]
