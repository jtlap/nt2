[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['saturate the value a0 in the template parameter type T,',
                         'but the value returned is of type A0'],
         'template' : True,
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['unsigned_int_'],
         'special' : ['ieee'],
         'tpl'   : '<uint16_t>',
         'type_defs' : [],
         'types' : ['unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/03/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 20/03/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['saturate<uint16_t>(a0)'],
                },
             'property_value' : {
                 'default' : ['a0>boost::simd::Valmax<uint16_t>() ? boost::simd::Valmax<uint16_t>() : a0'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
