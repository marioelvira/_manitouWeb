#ifdef __cplusplus
extern "C" {
#endif

#ifndef _IO_H_
#define _IO_H_

///////////////////
// IO definition //
///////////////////
/*
 *               --------
 *           A0 -|      |- GPIO16 -> D0 <- MOTOR MARCHA
 *           G  -|      |- GPIO5  -> D1 <> SCL*
 *           VU -|      |- GPIO4  -> D2 <> SDA*
 * S3 <- GPIO10 -|      |- GPIO0  -> D3 -> RELE CORTE
 * S2 <-  GPIO9 -|      |- GPIO2  -> D4 -> LED*
 * S1 <-   MOSI -|      |- 3V
 *           CS -|      |- G
 * S0 <-   MISO -|      |- GPIO14 -> D5 <- AGUA
 * SK <-   SCLK -|      |- GPIO12 -> D6 -> ALARMA
 *            G -|      |- GPIO13 -> D7 <- ACEITE
 *           3V -|      |- GPIO15 -> D8
 *           EN -|      |- GPIO3  -> RX
 *          RST -|      |- GPIO1  -> TX
 *            G -|      |- G
 *          VIN -|      |- 3V
 *               --------
 */

#define DI_MOTOR          16
#define DO_RELE_CORTE      0
#define DO_LED             2
#define DI_AGUA           14
#define DO_ALARMA         12
#define DI_ACEITE         13

#define IN_STATUS_INIT    0
#define IN_STATUS_ON      1
#define IN_STATUS_OFF     2

// Status definition
#define DOUT_ON       0
#define DOUT_OFF      1

#define IO_ON         1
#define IO_OFF        0

#endif // _IO_H_

#ifdef __cplusplus
} // extern "C"
#endif
