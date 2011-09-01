[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'special' : ['reduction'],  
         'type_defs' : [],
         'simd_types' : ['real_','uint64_t','int64_t','uint32_t','int32_t','uint8_t','int8_t'],
         'types' : ['real_']
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
             'int32_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'int64_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },           
             'int8_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'uint8_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : '4294967295ull','ulp_thresh' : '0',},
                },
             'uint32_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
              'uint64_t' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
            'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Signmask<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'boost::simd::Allbits<T>()' : {'result' : 'r_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
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
