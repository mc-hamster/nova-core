#ifndef NOVANOW_H
#define NOVANOW_H

#include "../SimonaMessage.h"

void novaNowSetup();
void novaNowLoop();
void sendSimonaMessage(const SimonaMessage &simMsg);

#endif // NOVANOW_H