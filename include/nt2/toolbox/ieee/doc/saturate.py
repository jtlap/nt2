[ ## this file was manually modified by jt
    {
     'functor' : {
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
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['saturate<uint16_t>(a0)'],
                },
             'property_value' : {
                 'default' : ['a0>nt2::Valmax<uint16_t>() ? nt2::Valmax<uint16_t>() : a0'],
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
