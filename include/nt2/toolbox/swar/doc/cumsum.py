[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'vT',
            },
         'special' : ['swar'],   
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_','signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'simd_included' : ['#include <nt2/include/functions/all.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::cumsum(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::cumsum(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        NT2_CREATE_BUF(z,T, cardinal_of<n_t>::value, T(0), T(0));",
                        "        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) z[i]=0;",
                        "        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++) {",
                        "          for( uint32_t k = i; k<cardinal_of<n_t>::value; k++) {",
                        "            z[k]+=a0[i];",
                        "          }",
                        "        }",
                        "        vT zz = load<vT>(&z[0],0);",
                        "        for( uint32_t i = 0; i<cardinal_of<n_t>::value; i++)",      
                        "         {",      
                        "            NT2_TEST_ULP_EQUAL(v[i],zz[i], 16);",      
                        "         }",                
                            ]
               },
           },
        },
    },
]
