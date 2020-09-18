#ifndef _PID_CONTROLER_H
#define _PID_CONTROLER_H
#define NULL_POINTER_EXCEPTION 1
#ifdef TEST
#define STATIC
#else
#define STATIC static
#endif
typedef struct pid_controler_struct* pid_controler;
pid_controler pid_controler_ctor(float kp, float ki, float kd);
float pid_controler_get_kp(pid_controler this);
float pid_controler_get_ki(pid_controler this);
float pid_controler_get_kd(pid_controler this);
void pid_controler_set_kp(pid_controler this, float kp);
void pid_controler_set_ki(pid_controler this, float ki);
void pid_controler_set_kd(pid_controler this, float kd);
void pid_controler_set_out_min(pid_controler this, float out_min);
void pid_controler_set_out_max(pid_controler this, float out_max);
float pid_controler_calculate_output(pid_controler this, float input, float setpoint,float d_time);
#endif // _PID_CONTROLER_H
