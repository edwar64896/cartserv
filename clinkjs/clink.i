%module clink
%include "typemaps.i"
%{
#include "clink.h"
%}
#include <stdint.h>
#include <libserialport.h>

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

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

%extend sd788t_param_change {
        int pc_transport_mode_change() {
                return ($self->parflags1 & (1 << 0));
        }
        int pc_arm_tracks_change() {
                return ($self->parflags1 & (1 << 1));
        }
        int pc_meter_ballistics_change() {
                return ($self->parflags1 & (1 << 6));
        }
        int pc_meter_peak_hold_change() {
                return ($self->parflags1 & (1 << 7));
        }
        int pc_input_to_tracks_routing_change() {
                return ($self->parflags2 & (1 << 0));
        }
        int pc_input_to_tracks_prepostfade_change() {
                return ($self->parflags2 & (1 << 1));
        }
        int pc_output_routing_change() {
                return ($self->parflags2 & (1 << 2));
        }
        int pc_sample_rate_change() {
                return ($self->parflags2 & (1 << 4));
        }
        int pc_bit_depth_change() {
                return ($self->parflags2 & (1 << 5));
        }
        int pc_timecode_frame_rate_change() {
                return ($self->parflags3 & (1 << 0));
        }
};

extern sd788t_sp_port           *sd788t_connect(unsigned char nsport);
extern uint8_t                  sd788t_get_transport(sd788t_sp_port * INPUT);
extern float                    sd788t_get_temperature(sd788t_sp_port * INPUT);
extern uint8_t                  sd788t_ctrl_transport(sd788t_sp_port * INPUT, uint8_t INPUT) ;
extern sd788t_param_change      sd788t_get_parameter_change_status(sd788t_sp_port * INPUT);
extern sd788t_tc                sd788t_get_timecode( sd788t_sp_port * INPUT );
