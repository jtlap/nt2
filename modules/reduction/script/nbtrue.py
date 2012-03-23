[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename nt2::meta::as_integer<sT>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['reduction'],  
         'type_defs' : ['typedef typename nt2::meta::scalar_of<T>::type sT;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [],
             'unsigned_int_' : [],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' :  'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()::value','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' :  'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' :  'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' :  'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::One<T>()' :  {'result' : 'cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::nbtrue(a0)'],
                },
             'property_value' : {
                 'default' : ['a0!=0'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        T z = a0[0] != 0;",
                        "        for(nt2::uint32_t i = 1; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          z+=a0[i] != 0 ;",
                        "        }",
                        "        NT2_TEST_EQUAL( v,z);",
                            ]
               },
            },
        },
    },
]
