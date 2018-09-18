#if !defined _clink

#define _GNU_SOURCE
#include <stdio.h>
//#include <sys/types.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <assert.h>
#include <pthread.h>
#include <libserialport.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>

#if defined SWIG
#define EXTERN extern
#define EXT_C extern "C" {
#define EXT_C_END }
#define SW_OUTPUT OUTPUT
#else
#define EXTERN
#define EXT_C
#define EXT_C_END
#define SW_OUTPUT
#endif

#define ewrap(...)	if (__VA_ARGS__ < SP_OK) {printf("lost connection...\n");exit(0);}
#define ewrap2(...)	int j;j=__VA_ARGS__;if (j < SP_OK) {printf("lost connection...\n");return NULL;}

EXT_C

typedef struct sd788t_rxbuf {
	uint8_t size;
	uint8_t status;
	uint8_t readBuf[255];
} sd788t_rxbuf;

typedef struct sd788t_meter_value {
	uint8_t vu;
	uint8_t peak;
} sd788t_meter_value;

typedef struct smpte {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t frames;
} sd788t_smpte;

typedef struct sd788t_tc {
	sd788t_smpte gen;
	sd788t_smpte rx;
	sd788t_smpte fl;
} sd788t_tc;

typedef struct sd788t_param_change {
	uint8_t version;
	uint8_t takeflags;
	uint32_t takehandle;
	uint8_t parflags1;
	uint8_t parflags2;
	uint8_t parflags3;
} sd788t_param_change;

typedef struct sp_port sd788t_sp_port;

/*
 * some function prototypes
 */

#define CALLHEADER	\
	sd788t_sp_port * sp_port; \
sd788t_rxbuf * rxbuf; \
uint8_t retval; \
\
if (sd788t_get_connected(&sp_port)!=SD788T_OK) { \
	return SD788T_CONNECTION_ERROR; \
} \


enum memory_enum {
	L1,L2,SDRAM
};

enum drives_enum {
	ALL_DRIVES,CF,INHDD,EXT
};

enum metrics_enum {
	PROCESS_UTILIZATION,TRANSPORT_UTILIZATION,HEAP_USAGE,STACK_USAGE,MEMORY_USAGE
};

enum transport_control_enum {
	TRANSPORT_STOP,TRANSPORT_PLAY,TRANSPORT_RECORD
};


enum sd788t_error_enum {
	SD788T_BAD_ACK=-2, SD788T_CONNECTION_ERROR=-1, SD788T_OK=0
};

enum sd788t_rxbuf_status{
	SD788T_RXBUF_NULL=-2, SD788T_RXBUF_CHECKSUM_ERROR=-1, SD788T_RXBUF_OK=0
};

/*
 * exception is for use when handling meter retrieval which isn't really up to spec.
 */
EXTERN uint8_t sd788t_user_get_limiters(uint8_t * limiters_bitmask) ;
EXTERN uint8_t sd788t_get_media_select(uint8_t *, char**);
EXTERN uint8_t sd788t_user_get_frame_rate(char ** SW_OUTPUT) ;
EXTERN struct sd788t_rxbuf * sd788t_checkAndSend(int exception, sd788t_sp_port* sp_port,uint8_t * buf, uint8_t bufLen);
EXTERN uint8_t sd788t_user_get_sample_rate(char ** SW_OUTPUT) ;
EXTERN uint8_t sd788t_user_get_bit_depth(char ** bitdepth) ;
EXTERN void sd788t_free_rxbuf(struct sd788t_rxbuf * rxbuf);
EXTERN int sd788t_get_connected(sd788t_sp_port ** psp_port);
EXTERN uint8_t * sd788t_createCommandBuffer(uint8_t command,uint8_t cmddata[],uint8_t cmddatasize,uint8_t *bufsize);

EXTERN sd788t_param_change sd788t_get_parameter_change_status(struct sp_port *);
uint8_t _sd788t_get_parameter_change_status(struct sp_port *, uint8_t *version, uint8_t *takeflags, uint32_t *takehandle, uint8_t *parflags1, uint8_t *parflags2, uint8_t *parflags3 );

EXTERN sd788t_sp_port* sd788t_connect(int nsport);
// 2 params - port handle, output reference variable
EXTERN unsigned char sd788t_get_transport(struct sp_port * INPUT);
unsigned char _sd788t_get_transport(struct sp_port *, unsigned char * );

EXTERN float sd788t_get_temperature(struct sp_port * INPUT);
unsigned char _sd788t_get_temperature(struct sp_port * , float * );

EXTERN unsigned char sd788t_ctrl_transport(struct sp_port * _sp_port, uint8_t uTransport) ;

EXTERN sd788t_tc sd788t_get_timecode( sd788t_sp_port * SW_INPUT );
uint8_t _sd788t_get_timecode( sd788t_sp_port * SW_INPUT, sd788t_smpte * SW_OUTPUT, sd788t_smpte * SW_OUTPUT, sd788t_smpte * SW_OUTPUT) ;

EXTERN uint8_t sd788t_get_setting(uint16_t setting, uint8_t *size, uint16_t *result);
EXTERN uint8_t sd788t_get_sys_metric(uint8_t metric,uint8_t param,float * SW_OUTPUT);
EXTERN uint8_t sd788t_user_get(uint16_t setting,uint16_t * SW_OUTPUT);
EXTERN uint8_t sd788t_get_sw_version(uint8_t * SW_OUTPUT,uint8_t * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_hw_version(uint8_t * SW_OUTPUT,uint8_t * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_productid(uint8_t * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_devicename(char * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_timecode_version(uint8_t * SW_OUTPUT,uint8_t * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_oxford_version(uint8_t * SW_OUTPUT,uint8_t * SW_OUTPUT, uint16_t * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_adc_vext(float *result) ;
EXTERN uint8_t sd788t_get_adc(uint8_t adc,uint16_t *result) ;

/*
 * 
 */
EXTERN uint8_t sd788t_get_track_meters(uint8_t * SW_OUTPUT,sd788t_meter_value * SW_OUTPUT) ;
EXTERN uint8_t sd788t_get_output_meters(uint8_t *nMeters,sd788t_meter_value * meter_values) ;
EXTERN uint8_t sd788t_get_input_meters(uint8_t *nMeters,sd788t_meter_value * meter_values) ;

/*
 * Params: pointer to uint8_t  to hold resulting transport status.
 */
uint8_t sd788t_get_transport(uint8_t * pTransportStatus) ;

/*
 * main internal stuff
 */
EXTERN void sd788t_list_ports(void (* process_ports)(uint8_t port_number, char * port_name, char * port_description)) ;
EXTERN sd788t_sp_port* sd788t_sp_get_port_by_number(int nsport) ;
EXTERN void sd788t_send40(sd788t_sp_port* sp_port);
EXTERN int sd788t_get_connected(sd788t_sp_port ** psp_port) ;
EXTERN struct sd788t_rxbuf * sd788t_checkAndSend(int exception, sd788t_sp_port* sp_port,uint8_t * sendBuf, uint8_t bufLen);
EXTERN uint8_t * sd788t_createCommandBuffer(uint8_t command, uint8_t cmddata[],uint8_t cmddatasize,uint8_t *bufsize) ;
EXTERN char *sd788t_get_channel_name(uint8_t channel) ;
EXTERN struct sd788t_rxbuf * sd788t_create_rxbuf(int size) ;
EXTERN struct sd788t_rxbuf * sd788t_getRxBuf();
EXTERN void sd788t_free_rxbuf(struct sd788t_rxbuf * rxbuf) ;
EXTERN int sd788t_checkIncoming(uint8_t *buf,int bufLen) ;
EXTERN struct sd788t_rxbuf * sd788t_sendCommand(sd788t_sp_port *sp_port,uint8_t command,uint8_t cmddata[],uint8_t cmddatasize) ;

EXT_C_END

#endif
