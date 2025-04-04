# Code Citations

## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, poofer
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, pooferA3;
uint16_t pooferB1, pooferB2, pooferB3;
uint16_t pooferC1, pooferC2, pooferC3;
uint16_t pooferD1, pooferD2, pooferD
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, pooferA3;
uint16_t pooferB1, pooferB2, pooferB3;
uint16_t pooferC1, pooferC2, pooferC3;
uint16_t pooferD1, pooferD2, pooferD3;

uint16_t boomerA1, boomerA2, boomerA3;
uint16_t boomerB1, boomerB2, boomerB3;
uint16_t boomerC1, boomerC2, boomerC3
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, pooferA3;
uint16_t pooferB1, pooferB2, pooferB3;
uint16_t pooferC1, pooferC2, pooferC3;
uint16_t pooferD1, pooferD2, pooferD3;

uint16_t boomerA1, boomerA2, boomerA3;
uint16_t boomerB1, boomerB2, boomerB3;
uint16_t boomerC1, boomerC2, boomerC3;
uint16_t boomerD1, boomerD2, boomerD3;

uint16_t starManualPoof, starManualBlow, starManuallowFuel, starManualFuel, starManualZap, starManualSelect;
uint8_t starManualSelectValue =
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
;
uint16_t mainDrunktardSwitch;
uint16_t resetConfigSwitch, resetRebootSwitch;

uint16_t pooferA1, pooferA2, pooferA3;
uint16_t pooferB1, pooferB2, pooferB3;
uint16_t pooferC1, pooferC2, pooferC3;
uint16_t pooferD1, pooferD2, pooferD3;

uint16_t boomerA1, boomerA2, boomerA3;
uint16_t boomerB1, boomerB2, boomerB3;
uint16_t boomerC1, boomerC2, boomerC3;
uint16_t boomerD1, boomerD2, boomerD3;

uint16_t starManualPoof, starManualBlow, starManuallowFuel, starManualFuel, starManualZap, starManualSelect;
uint8_t starManualSelectValue = 0;
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);


```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None,
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 =
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, po
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESP
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, button
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, button
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.add
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot,
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button,
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);

```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESP
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 5", "4", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 6", "5", ControlColor::Alizarin, starManualSelect);
    ESPUI.
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 5", "4", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 6", "5", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 7", "6", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 8", "7", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 5", "4", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 6", "5", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 7", "6", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 8", "7", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 9", "8", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 10", "9", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
//----- (Settings) -----
    // ESPUI.addControl(ControlType::Switcher, "Sleep (Disable)", "", ControlColor::None, settingsTab, &switchExample);

    //----- (Manual) -----

    pooferA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Poof 1", ControlColor::Alizarin, manualTab, buttonCallback);
    pooferA2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferA1, buttonCallback);
    pooferA3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferA1, buttonCallback);

    boomerA1 = ESPUI.addControl(ControlType::Button, "Star Cluster - A", "Boom 1", ControlColor::None, pooferA1, buttonCallback);
    boomerA2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferA1, buttonCallback);
    boomerA3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferA1, buttonCallback);

    pooferB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Poof 1", ControlColor::Emerald, manualTab, buttonCallback);
    pooferB2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferB1, buttonCallback);
    pooferB3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferB1, buttonCallback);

    boomerB1 = ESPUI.addControl(ControlType::Button, "Star Cluster - B", "Boom 1", ControlColor::Emerald, pooferB1, buttonCallback);
    boomerB2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferB1, buttonCallback);
    boomerB3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferB1, buttonCallback);

    pooferC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Poof 1", ControlColor::Peterriver, manualTab, buttonCallback);
    pooferC2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferC1, buttonCallback);
    pooferC3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferC1, buttonCallback);

    boomerC1 = ESPUI.addControl(ControlType::Button, "Star Cluster - C", "Boom 1", ControlColor::Peterriver, pooferC1, buttonCallback);
    boomerC2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferC1, buttonCallback);
    boomerC3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferC1, buttonCallback);

    pooferD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Poof 1", ControlColor::Carrot, manualTab, buttonCallback);
    pooferD2 = ESPUI.addControl(ControlType::Button, "", "Poof 2", ControlColor::None, pooferD1, buttonCallback);
    pooferD3 = ESPUI.addControl(ControlType::Button, "", "Poof 3", ControlColor::None, pooferD1, buttonCallback);

    boomerD1 = ESPUI.addControl(ControlType::Button, "Star Cluster - D", "Boom 1", ControlColor::Carrot, pooferD1, buttonCallback);
    boomerD2 = ESPUI.addControl(ControlType::Button, "", "Boom 2", ControlColor::None, pooferD1, buttonCallback);
    boomerD3 = ESPUI.addControl(ControlType::Button, "", "Boom 3", ControlColor::None, pooferD1, buttonCallback);

    starManualPoof = ESPUI.addControl(ControlType::Button, "Star Manual", "Poof", ControlColor::Carrot, manualTab, buttonCallback);
    starManualBlow = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManuallowFuel = ESPUI.addControl(ControlType::Button, "Star Manual", "Blow & Fuel", ControlColor::Carrot, starManualPoof, buttonCallback);
    starManualZap = ESPUI.addControl(ControlType::Button, "Star Manual", "Zap", ControlColor::Carrot, starManualPoof, buttonCallback);

    starManualSelect = ESPUI.addControl(ControlType::Select, "Star 1", String(starManualSelectValue), ControlColor::Alizarin, starManualPoof, &selectExample);
    ESPUI.addControl(ControlType::Option, "Star 1", "0", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 2", "1", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 3", "2", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 4", "3", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 5", "4", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 6", "5", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 7", "6", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 8", "7", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 9", "8", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 10", "9", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 11", "10", ControlColor::Alizarin, starManualSelect);
    ESPUI.addControl(ControlType::Option, "Star 12", "11", ControlColor::Alizarin
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 15", "14", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 16", "15", ControlColor::Al
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 15", "14", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 16", "15", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 17", "16", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 18", "17", ControlColor
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
, "Star 13", "12", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 14", "13", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 15", "14", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 16", "15", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 17", "16", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 18", "17", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 19", "18", ControlColor::Alizarin, starManualSelect);
        ESPUI.addControl(ControlType::Option, "Star 20", "19",
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);

```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST",
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN",
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peter
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.add
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESP
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.add
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESP
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizar
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15",
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", Control
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider,
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None, lightingUpdatesSlider);

    //    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", "0", ControlColor::Alizarin, lightingTab, &slider);
    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", String(light
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None, lightingUpdatesSlider);

    //    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", "0", ControlColor::Alizarin, lightingTab, &slider);
    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", String(lightUtils->getCfgSin()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingSinSlider);
    ESPUI.addControl(Max, "", "32", None, lightingSinSlider);

    lightingReverse
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None, lightingUpdatesSlider);

    //    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", "0", ControlColor::Alizarin, lightingTab, &slider);
    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", String(lightUtils->getCfgSin()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingSinSlider);
    ESPUI.addControl(Max, "", "32", None, lightingSinSlider);

    lightingReverseSwitch = ESPUI.addControl(ControlType::Switcher, "Reverse", String(lightUtils->getCfgReverse()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingFireSwitch = ESPUI.addControl(ControlType::Switcher, "Fire", String(lightUtils->getCfg
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
---- Tab 3 (Sequences) -----
    seqBoomAll = ESPUI.addControl(ControlType::Button, "Direct Boomers", "All", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    seqBoomLeftRight = ESPUI.addControl(ControlType::Button, "Boomers", "L to R (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);
    seqBoomRightLeft = ESPUI.addControl(ControlType::Button, "Boomers", "R to L (100ms)", ControlColor::Peterriver, seqBoomAll, &buttonCallback);

    starSeq_SEQ_POOF_END_TO_END = ESPUI.addControl(ControlType::Button, "SEQ_POOF_END_TO_END", "SEQ_POOF_END_TO_END", ControlColor::Peterriver, sequencesTab, &buttonCallback);
    starSeq_SEQ_BOOMER_LEFT_TO_RIGHT = ESPUI.addControl(ControlType::Button, "Boomers", "BOOMER_LEFT_TO_RIGHT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOMER_RIGHT_TO_LEFT = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOMER_RIGHT_TO_LEFT", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_FAST = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_FAST", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_WAVE_IN = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_WAVE_IN", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);
    starSeq_SEQ_BOOM_POOF = ESPUI.addControl(ControlType::Button, "Boomers", "SEQ_BOOM_POOF", ControlColor::Peterriver, starSeq_SEQ_POOF_END_TO_END, &buttonCallback);

    //---- Tab -- Lighting
    lightingBrightnessSlider = ESPUI.addControl(ControlType::Slider, "Brightness", String(lightUtils->getCfgBrightness()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingBrightnessSlider);
    ESPUI.addControl(Max, "", "255", None, lightingBrightnessSlider);

    lightingProgramSelect = ESPUI.addControl(ControlType::Select, "Select Program", String(lightUtils->getCfgProgram()), ControlColor::Alizarin, lightingTab, &selectExample);
    ESPUI.addControl(ControlType::Option, "RainbowColors_p", "1", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "RainbowStripeColors_p", "2", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "CloudColors_p", "3", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "PartyColors_p", "4", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "myRedWhiteBluePalette_p", "5", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Random", "6", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "BlackWhite Stripped", "7", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "quagga_gp", "8", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "purplefly_gp", "9", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "butterflytalker_gp", "10", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "carousel_gp", "11", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "autumnrose_gp", "12", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "Purple Gradient - bhw1_33_gp", "13", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "bhw1_22_gp", "14", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "heatmap_gp", "15", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "HeatColors_p", "16", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "LavaColors_p", "17", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "OceanColors_p", "18", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "ForestColors_p", "19", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All White", "20", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Red", "21", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Green", "22", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Blue", "23", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Purple", "24", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Cyan", "25", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "All Yellow", "26", ControlColor::Alizarin, lightingProgramSelect);
    ESPUI.addControl(ControlType::Option, "White Dot", "50", ControlColor::Alizarin, lightingProgramSelect);

    //    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", "100", ControlColor::Alizarin, lightingTab, &slider);
    lightingUpdatesSlider = ESPUI.addControl(ControlType::Slider, "Updates Per Second", String(lightUtils->getCfgUpdates()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "1", None, lightingUpdatesSlider);
    ESPUI.addControl(Max, "", "255", None, lightingUpdatesSlider);

    //    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", "0", ControlColor::Alizarin, lightingTab, &slider);
    lightingSinSlider = ESPUI.addControl(ControlType::Slider, "Sin", String(lightUtils->getCfgSin()), ControlColor::Alizarin, lightingTab, &slider);
    ESPUI.addControl(Min, "", "0", None, lightingSinSlider);
    ESPUI.addControl(Max, "", "32", None, lightingSinSlider);

    lightingReverseSwitch = ESPUI.addControl(ControlType::Switcher, "Reverse", String(lightUtils->getCfgReverse()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingFireSwitch = ESPUI.addControl(ControlType::Switcher, "Fire", String(lightUtils->getCfgFire()), ControlColor::Alizarin, lightingTab, &switchExample);
    lightingLocalDisable = ESPUI.addControl(ControlType::Switcher, "Local Disable", String(lightUtils->getCfgLocalDisable()), ControlColor::Alizarin, lightingTab, &switchExample);

    lightingAuto
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
::Alizarin, lightingTab, &switchExample);
    lightingAutoTime = ESPUI.addControl(ControlType::Slider, "Auto Time", String(lightUtils
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
::Alizarin, lightingTab, &switchExample);
    lightingAutoTime = ESPUI.addControl(ControlType::Slider, "Auto Time", String(lightUtils->getCfgAutoTime() ? lightUtils->getCfgAutoTime() : 30), ControlColor::Alizarin, lightingAuto, &slider);
    ESPUI.addControl(Min, "", "1", None, fogOutputOffMinTime);
    ESPUI.addControl(Max
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
::Alizarin, lightingTab, &switchExample);
    lightingAutoTime = ESPUI.addControl(ControlType::Slider, "Auto Time", String(lightUtils->getCfgAutoTime() ? lightUtils->getCfgAutoTime() : 30), ControlColor::Alizarin, lightingAuto, &slider);
    ESPUI.addControl(Min, "", "1", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "3600", None, fogOutputOffMinTime)
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fog
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESP
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMaxTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMaxTime);

    fogOutputOnMinTime = ESPUI.addControl(ControlType::
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMaxTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMaxTime);

    fogOutputOnMinTime = ESPUI.addControl(ControlType::Slider, "On Time (default: 200 / 1000)", String(ambient->getFogOutputOnMinTime() ? ambient->getFogOutputOnMinTime() : 200), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMaxTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMaxTime);

    fogOutputOnMinTime = ESPUI.addControl(ControlType::Slider, "On Time (default: 200 / 1000)", String(ambient->getFogOutputOnMinTime() ? ambient->getFogOutputOnMinTime() : 200), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "200", None, fogOutputOnMinTime);
    ESPUI.addControl(Max, "", "2000", None, fogOutputOnMinTime);

    fogOutputOnMaxTime = ESPUI.addControl(ControlType::Slider, "", String
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
ESPUI.addControl(ControlType::Slider, "Off Time (default: 5000 / 20000)", String(ambient->getFogOutputOffMinTime() ? ambient->getFogOutputOffMinTime() : 5000), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMinTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMinTime);

    fogOutputOffMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOffMaxTime() ? ambient->getFogOutputOffMaxTime() : 20000), ControlColor::Alizarin, fogOutputOffMinTime, &slider);
    ESPUI.addControl(Min, "", "2000", None, fogOutputOffMaxTime);
    ESPUI.addControl(Max, "", "60000", None, fogOutputOffMaxTime);

    fogOutputOnMinTime = ESPUI.addControl(ControlType::Slider, "On Time (default: 200 / 1000)", String(ambient->getFogOutputOnMinTime() ? ambient->getFogOutputOnMinTime() : 200), ControlColor::Alizarin, fogTab, &slider);
    ESPUI.addControl(Min, "", "200", None, fogOutputOnMinTime);
    ESPUI.addControl(Max, "", "2000", None, fogOutputOnMinTime);

    fogOutputOnMaxTime = ESPUI.addControl(ControlType::Slider, "", String(ambient->getFogOutputOnMaxTime() ? ambient->getFogOutputOnMaxTime() : 1000), ControlColor::Alizarin, fogOutputOnMinTime, &slider);
    ESPUI.addControl(Min, "", "200", None, fogOutputOn
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
addControl(ControlType::Label, "**WARNING**", "Don'
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
addControl(ControlType::Label, "**WARNING**", "Don't even think of doing anything in this tab unless you want to break something!!", ControlColor::Sunflower, resetTab);
    resetConfigSwitch = ESPUI.addControl(ControlType::Switcher, "Reset Configurations", "0", ControlColor::Sunflower, resetTab, &switchExample);
    resetRe
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
addControl(ControlType::Label, "**WARNING**", "Don't even think of doing anything in this tab unless you want to break something!!", ControlColor::Sunflower, resetTab);
    resetConfigSwitch = ESPUI.addControl(ControlType::Switcher, "Reset Configurations", "0", ControlColor::Sunflower, resetTab, &switchExample);
    resetRebootSwitch = ESPUI.addControl(ControlType::Switcher, "Reboot", "0", ControlColor::Sunflower, resetTab, &switchExample);

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.
```


## License: GPL-3.0
https://github.com/mc-hamster/nova-core/blob/caba9cc26ceb01b2b38bcfa3c2b54994fc86b9b0/src/Web.cpp

```
addControl(ControlType::Label, "**WARNING**", "Don't even think of doing anything in this tab unless you want to break something!!", ControlColor::Sunflower, resetTab);
    resetConfigSwitch = ESPUI.addControl(ControlType::Switcher, "Reset Configurations", "0", ControlColor::Sunflower, resetTab, &switchExample);
    resetRebootSwitch = ESPUI.addControl(ControlType::Switcher, "Reboot", "0", ControlColor::Sunflower, resetTab, &switchExample);

    // Enable this option if you want sliders to be continuous (update during move) and not discrete (update on stop)
    // ESPUI.sliderContinuous = true;

    // Optionally use HTTP BasicAuth
    // ESPUI.server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
    // ESPUI->server->begin();
```

