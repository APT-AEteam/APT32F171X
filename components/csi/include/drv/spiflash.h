/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     spiflash.h
 * @brief    header file for spiflash driver
 * @version  V1.0
 * @date     02. June 2017
 * @model    spiflash
 ******************************************************************************/
#ifndef _DRV_SPIFLASH_H_
#define _DRV_SPIFLASH_H_


#include <stdint.h>

#include <drv/gpio.h>
#include <drv/spi.h>
#include <drv/qspi.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
* \brief  Build a flash ID
* \param [in] vendor_id    Vendor id(8bit)
* \param [in] device_id    Flash device id (ID15~ID0) 16bit
* \return    24bit flash id
*/

#define FLASH_ID_BUILD(VENDOR_ID,DEVICE_ID)

/**
* \struct csi_spiflash_lock_info_t
* \ flash use status register 1 to protect data in memory array
* \ different flash vendor support different  protect region (top/bottom/none)
*   also support different protect number
*   status1 register bif field show as follow
*   7          |6           |5            |4     |3     |2     |1     |0
*   ---------------------------------------------------------------------
*   vensor def | vendor def | vendor def  | BP2  | BP1  |  BP0 | WEL  | BUSY
* \ protect type
* \ protect block size : vendor define ,user should check flash datasheet of vendor
*                      : use w25q64fw as example , min protect block size is 128 KB
* \ TOP      : protect address from flash top address
* \ BOTTOM   : protect address from flash bottom address
* \ SEC      : protect addres base on sector unit and protect region only must not exceed one block
* \ BPx      : protect start addres base on TOP/BOTTOM feature,and BPx value denote protect number
* \            BP[x..0]'s value : 2^(n-1) protect block unit, ex, BP[x..0] = 5, protect block number = 2^(5-1) = 16
* \            if BP[x..0] = 0  denote protect none
* \            if BP[x..0]'s all bis is 1 ,denote protect all flash
* \
* \ NOTE:
* \        only  support SEC = 0
* \        only  support CMP = 0
* \
*
* Sample table portion for 8MB flash (Winbond w25q64fw):
*
*   SEC  |  TB   |  BP2  |  BP1  |  BP0  |  Prot Length  | Protected Portion
*  --------------------------------------------------------------------------
*    X   |   X   |   0   |   0   |   0   |  NONE         | NONE
*    0   |   0   |   0   |   0   |   1   |  128 KB       | Upper 1/64
*    0   |   0   |   0   |   1   |   0   |  256 KB       | Upper 1/32
*    0   |   0   |   0   |   1   |   1   |  512 KB       | Upper 1/16
*    0   |   0   |   1   |   0   |   0   |  1 MB         | Upper 1/8
*    0   |   0   |   1   |   0   |   1   |  2 MB         | Upper 1/4
*    0   |   0   |   1   |   1   |   0   |  4 MB         | Upper 1/2
*    X   |   X   |   1   |   1   |   1   |  8 MB         | ALL
*  ------|-------|-------|-------|-------|---------------|-------------------
*    0   |   1   |   0   |   0   |   1   |  128 KB       | Lower 1/64
*    0   |   1   |   0   |   1   |   0   |  256 KB       | Lower 1/32
*    0   |   1   |   0   |   1   |   1   |  512 KB       | Lower 1/16
*    0   |   1   |   1   |   0   |   0   |  1 MB         | Lower 1/8
*    0   |   1   |   1   |   0   |   1   |  2 MB         | Lower 1/4
*    0   |   1   |   1   |   1   |   0   |  4 MB         | Lower 1/2
*
*/

typedef enum {
    LOCK_TP_NONE,
    LOCK_TP_TOP,
    LOCK_TP_BOTTOM,
    LOCK_TP_DUAL
} csi_spiflash_lock_region_t;

typedef enum {
    SPIFLASH_DATA_1_LINE  = 1,
    SPIFLASH_DATA_2_LINES = 2,
    SPIFLASH_DATA_4_LINES = 4
} csi_spiflash_data_line_t;

typedef union {
    csi_spi_t   spi;
    csi_qspi_t  qspi;
} csi_spi_qspi_t;

/**
\brief Flash information
*/
typedef struct {
    char    *flash_name;                  ///< Name string of spiflash
    uint32_t flash_id;                    ///< JEDEC ID  = manufature ID <<16 | device ID (ID15~ID0)
    uint32_t flash_size;                  ///< Flash chip size
    uint32_t xip_addr;                    ///< If use qspi controler to access flash ,code can be ececuted on flash ,the addr is xip addr
    uint32_t sector_size;                 ///< Sector size
    uint32_t page_size;                   ///< Page size for read or program
} csi_spiflash_info_t;

/**
\brief Flash control block
*/
typedef struct {
    csi_spi_qspi_t spi_qspi;               ///< Spi/qspi handle
    void (*spi_cs_callback)(csi_gpio_pin_state_t value);
    void           *flash_prv_info;        ///< Point to vendor private feature struct
    int32_t (*spi_send)(void *spi, uint8_t cmd, uint32_t addr, uint32_t addr_size, const void *data, uint32_t size);
    int32_t (*spi_receive)(void *spi, uint8_t cmD, uint32_t addr, uint32_t addr_size, void *data, uint32_t size);
    void           *priv;                  ///< User private param
} csi_spiflash_t;

/**
  \brief       Initialize SPIFLASH with spi controler  and probe flash device
  \param[in]   spi        SPIFLASH handle
  \param[in]   spi_idx    SPI controler index
  \param[in]   spi_cs     GPIO info for chip select,if NULL, not use gpio cs
  \return      Error code
*/
csi_error_t csi_spiflash_spi_init(csi_spiflash_t *spiflash, uint32_t spi_idx, void *spi_cs_callback);

/**
  \brief       Initialize SPIFLASH with qspi controler  and probe flash device
  \param[in]   spiflash    SPIFLASH handle
  \param[in]   qspi_idx    QSPI controler index
  \return      Error code
*/
csi_error_t csi_spiflash_qspi_init(csi_spiflash_t *spiflash, uint32_t qspi_idx);

/**
  \brief       De-initialize SPIFLASH Interface based on spi controler. stops operation and releases the software resources used by the interface
  \param[in]   handle    SPIFLASH handle to operate
  \return      Error code
*/
void csi_spiflash_spi_uninit(csi_spiflash_t *spiflash);

/**
  \brief       De-initialize SPIFLASH Interface based on qspi controler. stops operation and releases the software resources used by the interface
  \param[in]   handle    SPIFLASH handle to operate
  \return      Error code
*/
void csi_spiflash_qspi_uninit(csi_spiflash_t *spiflash);


/**
  \brief       get flash device infomation
  \param[in]   handle        SPIFLASH handle to operate
  \param[in]   flash_info    User storage to get flash vendor info after flash init
  \return      spiflash_info_t
*/

csi_error_t csi_spiflash_get_flash_info(csi_spiflash_t *spiflash, csi_spiflash_info_t *flash_info);


/**
  \brief       Read data from Flash
  \param[in]   handle    SPIFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[out]  data      Pointer to a buffer storing the data read from Flash
  \param[in]   cnt       Number of data items to read
  \return      If receive successful, this function shall return the num of data witch is received successfulful
               otherwise, the function shall return Error code
*/
int32_t csi_spiflash_read(csi_spiflash_t *spiflash, uint32_t offset, void *data, uint32_t size);

/**
  \brief       Program data to Flash
  \param[in]   handle    SPIFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   data      Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   cnt       Number of data items to program
  \return      If program successful, this function shall return the num of data witch is program successfulful
               otherwise, the function shall return Error code
*/
int32_t csi_spiflash_program(csi_spiflash_t *spiflash, uint32_t offset, const void *data, uint32_t size);

/**
  \brief       Erase Flash Sector
  \param[in]   handle    SPIFLASH handle to operate
  \param[in]   offset    Data address, offset address relative to zero
  \param[in]   size      Length to be erased
  \return      Error code
*/
csi_error_t csi_spiflash_erase(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Read flash status register
  \param[in]   handle    SPIFLASH handle to operate
  \param[in]   cmd       Cmd code
  \param[out]  data      Data buf to save flash status register
  \param[in]   size      Register length in byte
  \return      Error code
*/
csi_error_t csi_spiflash_read_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size);

/**
  \brief       Write status register
  \param[in]   handle    SPIFLASH handle to operate
  \param[in]   cmd       Cmd code
  \param[out]  data      Data buf to save flash status register
  \param[in]   size      Register length in byte
  \return      Error code
*/
csi_error_t csi_spiflash_write_reg(csi_spiflash_t *spiflash, uint8_t cmd_code, uint8_t *data, uint32_t size);


/**
  \brief       Enable spiflash write protection
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Lock size
  \return      Error code
*/
csi_error_t csi_spiflash_lock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Enable spiflash write protection
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Unlock size
  \return      Error code
*/
csi_error_t csi_spiflash_unlock(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       check flash is locked(write protect)
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   offset      Protect flash offset,offset need protect block size aligned
  \param[in]   size        Locked size
  \return      0:unlocked if query region overlay with locked region 1: locked if query reigon is fully in locked region
*/
int csi_spiflash_is_locked(csi_spiflash_t *spiflash, uint32_t offset, uint32_t size);

/**
  \brief       Set QSPI data line
  \param[in]   spiflash    SPIFLASH handle to operate
  \param[in]   line        SPIFLASH data line mode
  \return      Error code
*/
csi_error_t csi_spiflash_config_data_line(csi_spiflash_t *spiflash, csi_spiflash_data_line_t line);


#ifdef __cplusplus
}
#endif

#endif /* _DRV_SPIFLASH_H_ */
