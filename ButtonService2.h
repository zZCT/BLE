/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BLE_BUTTON_SERVICE_H__
#define __BLE_BUTTON_SERVICE_H__

#include <string>

static  int cnt=0;

class ButtonService {
public:
    const static uint16_t BUTTON_SERVICE_UUID              = 0xA000;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID = 0xA001;

    ButtonService(BLE &_ble, int buttonPressedInitial) :
        ble(_ble), buttonState(BUTTON_STATE_CHARACTERISTIC_UUID, &buttonPressedInitial, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&buttonState};
        GattService         buttonService(ButtonService::BUTTON_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        ble.gattServer().addService(buttonService);
    }

    void updateButtonState(bool newState) {

        char a[]={'b','0','7','9','0','1','1','5','1'};
        int ar[9];
        for(int i=0;i<9;i++)
            ar[i]=int(a[i]);
        ble.gattServer().write(buttonState.getValueHandle(), (uint8_t *)(ar+(cnt%9)), sizeof(int));
        cnt++;
    }

private:
    BLE                              &ble;
    ReadOnlyGattCharacteristic<int>  buttonState;
};

#endif /* #ifndef __BLE_BUTTON_SERVICE_H__ */
