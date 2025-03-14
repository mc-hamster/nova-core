#ifndef NOVANOW_H
#define NOVANOW_H

#include "../SimonaMessage.h"

/**
 * @brief Initialize the NovaNow module
 * 
 * Sets up the initial state and preferences for the NovaNow LED control system.
 * Should be called once during system startup before using other functions.
 */
void novaNowSetup();

/**
 * @brief Main processing loop for NovaNow
 * 
 * Handles message queue processing and updates LED animations based on the current
 * Simona game state. This should be called regularly in the main loop.
 */
void novaNowLoop();

/**
 * @brief Send a Simona game message to be processed by NovaNow
 * 
 * Queues a SimonaMessage for processing by the NovaNow system. The message will be
 * processed in the next call to novaNowLoop() and may trigger LED animations based
 * on the game state contained in the message.
 * 
 * @param simMsg Reference to the SimonaMessage to be sent
 */
void sendSimonaMessage(const SimonaMessage &simMsg);

#endif // NOVANOW_H