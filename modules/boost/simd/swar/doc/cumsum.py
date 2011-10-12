[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['compute the cumulate sum of the vector elements'],   
         'module' : 'boost',
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
             'simd_included' : ['#include <boost/simd/include/functions/all.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::Minf<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['boost::simd::cumsum(a0)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::cumsum(a0)'],
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
