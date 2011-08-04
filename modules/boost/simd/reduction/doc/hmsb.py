[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'special' : ['reduction'],  
         'type_defs' : [],
         'types' : ['integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],   
             'simd_included' : ['#include <nt2/include/functions/bits.hpp>',
                                '#include <nt2/include/functions/shri.hpp>'],
             'cover_included' : ['#include <nt2/include/functions/bits.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
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
                        "        iT z = boost::simd::bits(a0[0])&1;",
                        "        for(int i = 0; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          z |= boost::simd::bits(a0[i])&1<<i;",
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
            },
        },
    },
]
