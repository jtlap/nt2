[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'special' : ['swar'],  
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 24/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 24/02/2011',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()'],['0','nt2::meta::cardinal_of<T>::value-1']],
             'real_' : [['T(-100)', 'T(100)'],['0','nt2::meta::cardinal_of<T>::value-1']],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::Inf<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Inf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::Nan<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'signed_int_' : {
                 'nt2::Mone<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Mone<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::Zero<ivT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::lookup(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
             'scalar_simul' :{
                    'default' : [
                        "        for(uint32_t i=0; i<cardinal_of<n_t>::value; i++)",      
                        "        {",
                        "           NT2_TEST_EQUAL(v[i],a0[a1[i]]);",
                        "        }",
                            ]
               },
           },
        },
    },
]
