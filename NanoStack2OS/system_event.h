#ifndef _SYSTEM_EVENT_H_
#define _SYSTEM_EVENT_H_
/*
 * Copyright ARM Ltd 2014
 */

 #ifdef __cplusplus
extern "C" {
#endif

#include "ns_types.h"

 /**
  * \enum error_t
  * \brief System generic error.
  */
typedef enum error_t
{
	eOK = 0,	/*!< no error */
	eFALSE = 1, /*!< no result */
	eBUSY = 2,	/*!< resource busy */
	eSYSTEM		/*!< error code readable in sys_error */
}error_t;
#include "tasklet_api.h"

typedef enum arm_nwk_interface_status_type_e
{
	ARM_NWK_BOOTSTRAP_READY = 0, /**< Interface configured Bootstrap is ready*/
	ARM_NWK_RPL_INSTANCE_FLOODING_READY, /**< RPL instance have been flooded */
	ARM_NWK_SET_DOWN_COMPLETE, /**< Interface DOWN command successfully */
	ARM_NWK_NWK_SCAN_FAIL, 	/**< Interface have not detect any valid network*/
	ARM_NWK_IP_ADDRESS_ALLOCATION_FAIL, /*!*< IP address allocation fail(ND, DHCPv4 or DHCPv6 */
	ARM_NWK_DUPLICATE_ADDRESS_DETECTED, /*!*< User specific GP16 was not valid */
	ARM_NWK_AUHTENTICATION_START_FAIL, /**< No valid Authentication server detected behind access point */
	ARM_NWK_AUHTENTICATION_FAIL,	/**< Network authentication fail by Handshake */
	ARM_NWK_NWK_CONNECTION_DOWN, /*!*< No connection between Access point or Default Router */
	ARM_NWK_NWK_PARENT_POLL_FAIL, /*!*< Sleepy host poll fail 3 time */
	ARM_NWK_PHY_CONNECTION_DOWN, /*!*< Interface PHY cable off or serial port interface not respond anymore */
} arm_nwk_interface_status_type_e;

typedef enum arm_library_event_type_e
{
	ARM_LIB_TASKLET_INIT_EVENT, /**< Tasklet Init come always when generate tasklet*/
	ARM_LIB_NWK_INTERFACE_EVENT,	/**< Interface Bootstrap  or state update event */
	ARM_LIB_SYSTEM_TIMER_EVENT, /*!*< System Timer event */
	APPLICATION_EVENT, /**< Application specific event */
} arm_library_event_type_e;


typedef struct arm_event_s
{
	int8_t receiver; /**< Event handler Tasklet ID */
	int8_t sender; /**< Event sender Tasklet ID */
	uint8_t event_type; /**< This will be typecast arm_library_event_type_e */
	uint8_t event_id; /**< Timer ID, NWK interface ID or application specific ID */
	void *data_ptr; /**< Application could share data pointer tasklet to tasklet */
	void (*cb_fptr)(uint8_t); /**< Application could share data pointer tasklet to tasklet */
	uint32_t event_data;
} arm_event_s;

typedef void (*idle_cb_t)(void *);


extern int8_t ns_timer_start(int8_t ns_timer_id, uint16_t slots);
extern int8_t ns_timer_stop(int8_t ns_timer_id);
extern int8_t ns_timer_sleep(void);
extern int8_t ns_timer_register(void (*timer_interrupt_handler)(int8_t, uint16_t));
extern int8_t ns_timer_unregister(int8_t ns_timer_id);

extern void core_timer_tick_update(uint32_t ticks);
extern uint32_t core_timer_shortest_tick(void);
extern void core_timer_sleep_balance(uint32_t ticks);
extern void set_core_timer_period(uint8_t snperiod);

extern int8_t timer_sys_wakeup(void);
extern void timer_sys_disable(void);
extern void timer_runtime_ticks_sleep_update(uint32_t sleep_ticks);
extern int8_t timer_sys_event(uint8_t snmessage, uint32_t time);
extern int8_t timer_sys_event_cancel(uint8_t snmessage);

extern void event_init(void);
extern error_t event_cb_send(void (*fptr)(uint8_t) , uint8_t event, uint8_t snpriority);
extern  int8_t event_get_active_tasklet(void);
extern  void event_set_active_tasklet(int8_t tasklet);
extern int8_t arm_ns_event_send(arm_event_s *event);
extern noreturn void event_dispatch(void);
extern void event_register_idle_cb(idle_cb_t idle_cb, void *idle_cb_param);
extern int8_t arm_ns_tasklet_create(void (*tasklet_func_ptr)(arm_event_s*));


#ifdef __cplusplus
}
#endif

#endif /*_SYSTEM_EVENT_H_*/
