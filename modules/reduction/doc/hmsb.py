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
         'types' : ['real_', 'signed_int_', 'unsigned_int_']
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
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
            },
         'specific_values' : {
             'signed_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Signmask<T>()' : {'result' : 'r_t((1 << nt2::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'nt2::Allbits<T>()' : {'result' : 'r_t((1 << nt2::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Allbits<T>()' : {'result' : 'r_t((1 << nt2::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::shri(nt2::Mone<nt2::int32_t>(),int(32-nt2::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::shri(nt2::Mone<nt2::int32_t>(),int(32-nt2::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::shri(nt2::Mone<nt2::int32_t>(),int(32-nt2::meta::cardinal_of<vT>::value))','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Signmask<T>()' : {'result' : 'r_t((1 << nt2::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                 'nt2::Allbits<T>()' : {'result' : 'r_t((1 << nt2::meta::cardinal_of<vT>::value) - 1)','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::hmsb(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::b_and(a0, nt2::Signmask<r_t>()) != 0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        nt2::int32_t z = 0;",
                        "        nt2::uint32_t N = cardinal_of<n_t>::value;",
                        "        for(nt2::uint32_t i = 0; i< N; ++i)",
                        "        {",
                        "          z |= nt2::bits(a0[i]) >> (sizeof(iT)*CHAR_BIT - 1) << i;"
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
            },
        },
    },
]
