/*
 * Copyright (C) 2017-2022 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file       pwm.h
 * @brief      header file for pwm driver
 * @version    V1.0
 * @date       28. Apr 2020
 * @model      pwm
 ******************************************************************************/

#ifndef _DRV_PWM_H_
#define _DRV_PWM_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PWM_POLARITY_HIGH = 0,                           ///< high level
    PWM_POLARITY_LOW                                 ///< low level
} csi_pwm_polarity_t;

typedef enum {
    PWM_CAPTURE_POLARITY_POSEDGE = 0,                ///< Posedge Edge
    PWM_CAPTURE_POLARITY_NEGEDGE,                    ///< Negedge Edge
    PWM_CAPTURE_POLARITY_BOTHEDGE                    ///< Both Edge
} csi_pwm_capture_polarity_t;

typedef enum {
    PWM_EVENT_CAPTURE_POSEDGE = 0,                   ///< Capture Posedge Event
    PWM_EVENT_CAPTURE_NEGEDGE,                       ///< Capture Negedge Event
    PWM_EVENT_CAPTURE_BOTHEDGE,                      ///< Capture Bothedge Event
    PWM_EVENT_ERROR,                                 ///< Error
} csi_pwm_event_t;

typedef struct csi_pwm csi_pwm_t;

struct csi_pwm {
    csi_dev_t      dev;
    void           (*callback)(csi_pwm_t *pwm, csi_pwm_event_t event, uint32_t ch, uint32_t time_us, void *arg);
    void           *arg;
    void           *priv;
};

/**
  \brief       Initialize PWM Interface. Initializes the resources needed for the PWM interface
  \param[in]   pwm    pwm handle to operate
  \param[in]   idx    pwm idx
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_init(csi_pwm_t *pwm, uint32_t idx);

/**
  \brief       De-initialize PWM Interface. stops operation and releases the software resources used by the interface
  \param[in]   pwm    pwm handle to operate
  \return      None
*/
void csi_pwm_uninit(csi_pwm_t *pwm);

/**
  \brief       Config pwm out mode
  \param[in]   pwm               pwm handle to operate
  \param[in]   channel           channel num
  \param[in]   period_us         the PWM period in us
  \param[in]   pulse_width_us    the PMW pulse width in us
  \param[in]   polarity          the PWM polarity \ref csi_pwm_polarity_t
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_out_config(csi_pwm_t *pwm,
                               uint32_t channel,
                               uint32_t period_us,
                               uint32_t pulse_width_us,
                               csi_pwm_polarity_t polarity);

/**
  \brief       Start generate pwm signal
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_out_start(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Stop generate pwm signal
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      None
*/
void csi_pwm_out_stop(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Config pwm capture mode
  \param[in]   pwm         pwm handle to operate
  \param[in]   channel     channel num
  \param[in]   polarity    pwm capture polarity \ref csi_pwm_capture_polarity_t
  \param[in]   count       pwm capture polarity count
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_config(csi_pwm_t *pwm,
                                   uint32_t channel,
                                   csi_pwm_capture_polarity_t polarity,
                                   uint32_t count);

/**
  \brief       Start pwm capture
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_start(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Stop pwm capture
  \param[in]   pwm        pwm handle to operate
  \param[in]   channel    channel num
  \return      None
*/
void csi_pwm_capture_stop(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Attach pwm callback
  \param[in]   pwm         pwm handle to operate
  \param[in]   callback    callback func
  \param[in]   arg         callback's param
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_attach_callback(csi_pwm_t *pwm, void *callback, void *arg);

/**
  \brief       Detach pwm callback
  \param[in]   pwm    pwm handle to operate
  \return      None
*/
void csi_pwm_detach_callback(csi_pwm_t *pwm);

/**
  \brief       Enable pwm power manage
  \param[in]   pwm    pwm handle to operate
  \return      error code \ref csi_error_t
*/
csi_error_t csi_pwm_enable_pm(csi_pwm_t *pwm);

/**
  \brief       Disable pwm power manage
  \param[in]   pwm    pwm handle to operate
  \return      None
*/
void csi_pwm_disable_pm(csi_pwm_t *pwm);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_PWM_H_ */
