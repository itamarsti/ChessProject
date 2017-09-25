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


bool mainSettingFlow(boardGame* board);
bool cmdToActSetting(boardGame* board, SETTING_COMMAND cmd);




#endif /* SETTINGFLOW_H_ */
