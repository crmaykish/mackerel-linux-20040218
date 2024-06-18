#ifndef __MACKEREL_SERIAL_H
#define __MACKEREL_SERIAL_H

// #define FT245_WRITE_DATA(scc, dat) ( *(scc).output = (dat) )
// #define FT245_READ_DATA(scc) ( *(scc).input) 
// #define FT245_READ_STATUS_RDF(scc) ( *(scc).status_rdf) 
// #define FT245_READ_STATUS_TXE(scc) ( *(scc).status_txe) 

// #define FT245_STATUS_BIT 1

typedef struct _mackerel_port {
        volatile u8 *output;
        volatile u8 *input;
        volatile u8 *status_rdf;
        volatile u8 *status_txe;
        int vecnum;
} mackerel_port;

/* forward declaration */
struct tty_struct;

typedef struct _mackerel_info {
    struct _mackerel_port portaddrs;
    /* per-port runtime info goes here */
    int magic;
    int line;
    int irq;
    struct tty_struct *tty;
} mackerel_info;

#endif /* __MACKEREL_SERIAL_H */
