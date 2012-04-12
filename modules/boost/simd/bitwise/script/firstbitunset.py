[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function  find the first bit unset (beginning with the least',
                          'significant bit) in a0, and return the bit pattern in which',
                          'this bit is the only bit set.'],
         'return' : ['always returns an integer value'],   
          'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_integer<T, unsigned>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
         'simd_types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Signmask<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Two<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Signmask<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Two<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                },
             'property_value' : {
                },
             'simd' : {
                },
             'ulp_thresh' : {
                },
            },
        },
    },
]
