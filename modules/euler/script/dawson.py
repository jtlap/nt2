[ ## this file was manually modified by jt
    {
     'functor' : {
            'description' :['Dawson function','\par Formula',
                            '\\\\f[ D(a_0)=e^{-x^2}\int_0^{a_0} e^{-t^2}}dt'],
             
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 22/02/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 22/02/2011',
            },
         'ranges' : {
             'real_' : [['T(-100)', 'T(100)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Minf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                 'nt2::Mone<T>()' : {'result' : '-0.53807950691276840161','ulp_thresh' : '0',},
                 'nt2::Nan<T>()' : {'result' : 'nt2::Nan<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>()' : {'result' : '0.53807950691276840161','ulp_thresh' : '0',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'default' : ['nt2::dawson(a0)'],
                },
             'property_value' : {
                 'default' : ['nt2::dawson(a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0.5'],
                },
            },
        },
    },
]
