/*
 * settingFlow.h
 *
 *  Created on: 24 баев„ 2017
 *      Author: Itamar
 */

#ifndef SETTINGFLOW_H_
#define SETTINGFLOW_H_

/*
 * settingFlow.c
 *
 *  Created on: 24 баев„ 2017
 *      Author: Itamar
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "settingParser.h"
#include "boardFuncs.h"

/**
 *
 *
 * Managing the reSetting of the Game Board based on the relevant commands.
 * @param board - the Board Game Data structure.
 * @param command - the settings command Data structure.
 * @return
 * True - if start (for starting the game)
 * False - otherwise.
 *
 */
bool mainSettingFlow(boardGame* board);


bool cmdToActSetting(boardGame* board, SETTING_COMMAND cmd);




#endif /* SETTINGFLOW_H_ */
