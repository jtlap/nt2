[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<scalar,scalar>::type',
            },
         'simd_types' : ['real_'],
         'special' : ['reduction'],  
         'type_defs' : ['typedef T scalar;'],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],
             'no_ulp'     : 'True',   
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(100)'],['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>()' : {'result' : 'nt2::meta::cardinal_of<vT>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : 'nt2::meta::cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::meta::cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : {'result' : 'nt2::meta::cardinal_of<vT>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : 'nt2::meta::cardinal_of<vT>::value','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::dot(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0*a1'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        T z = nt2::Zero<T>();",
                        "        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; ++i)",
                        "        {",
                        "          z += a0[i]*a1[i];",
                        "        }",
                        "        NT2_TEST_ULP_EQUAL( v,z,0.5);",
                            ]
               },
           },
        },
    },
]
