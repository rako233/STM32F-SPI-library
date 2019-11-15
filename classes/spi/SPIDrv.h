/*
 * SPIDrv.h
 *
 *  Created on: Oct 27, 2019
 *      Author: rako
 */

#ifndef EC_SPIDRV_H_
#define EC_SPIDRV_H_

#include "main.h"

#include "spi/SPIDrv.h"

class SPIDrv {
    private:
        SPI_HandleTypeDef *_hspi;
        GPIO_TypeDef *_GPIOx;
        uint32_t _GPIO_Pin;
        HAL_StatusTypeDef _status;

    public:

        SPIDrv(SPI_HandleTypeDef *hspi, GPIO_TypeDef *GPIOx, uint32_t nss_pin):
                    _hspi(hspi), _GPIOx(GPIOx), _GPIO_Pin(nss_pin) {}               // With software NSS


        SPIDrv(SPI_HandleTypeDef *hspi):_hspi(hspi), _GPIOx(NULL), _GPIO_Pin(0) {}  // With hardware controlled NSS

        inline HAL_StatusTypeDef Status() {return _status;};

        inline virtual void SetNSS() {
            if(_GPIOx)
                HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PinState::GPIO_PIN_RESET);
            _status = HAL_StatusTypeDef::HAL_OK;
        }

        inline virtual void ResetNSS() {
            if(_GPIOx)
                HAL_GPIO_WritePin(_GPIOx, _GPIO_Pin, GPIO_PinState::GPIO_PIN_SET);
            _status = HAL_StatusTypeDef::HAL_OK;
        }

        inline virtual void TxNByte(uint8_t *data, uint16_t size) {
            _status = HAL_SPI_Transmit(this->_hspi, data, size, HAL_MAX_DELAY);
        }

        inline virtual void TxRxNByte(uint8_t *txdata, uint8_t *rxdata, uint8_t size) {
            _status = HAL_SPI_TransmitReceive(this->_hspi, txdata, rxdata, size, HAL_MAX_DELAY);
        }
};

#endif /* EC_SPIDRV_H_ */
