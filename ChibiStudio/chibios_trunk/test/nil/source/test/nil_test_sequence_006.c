/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "hal.h"
#include "nil_test_root.h"

/**
 * @file    nil_test_sequence_006.c
 * @brief   Test Sequence 006 code.
 *
 * @page nil_test_sequence_006 [6] Synchronous Messages
 *
 * File: @ref nil_test_sequence_006.c
 *
 * <h2>Description</h2>
 * This module implements the test sequence for the Synchronous
 * Messages subsystem.
 *
 * <h2>Conditions</h2>
 * This sequence is only executed if the following preprocessor condition
 * evaluates to true:
 * - CH_CFG_USE_MESSAGES
 * .
 *
 * <h2>Test Cases</h2>
 * - @subpage nil_test_006_001
 * .
 */

#if (CH_CFG_USE_MESSAGES) || defined(__DOXYGEN__)

/****************************************************************************
 * Shared code.
 ****************************************************************************/

/*
 * Messager thread.
 */
static THD_FUNCTION(messager, p) {

  chMsgSend(p, 'A');
  chMsgSend(p, 'B');
  chMsgSend(p, 'C');
  chMsgSend(p, 'D');
}

/****************************************************************************
 * Test cases.
 ****************************************************************************/

/**
 * @page nil_test_006_001 [6.1] Messages Server loop
 *
 * <h2>Description</h2>
 * A messenger thread is spawned that sends four messages back to the
 * tester thread.<br> The test expect to receive the messages in the
 * correct sequence and to not find a fifth message waiting.
 *
 * <h2>Test Steps</h2>
 * - [6.1.1] Starting the messenger thread.
 * - [6.1.2] Waiting for four messages then testing the receive order.
 * .
 */

static void nil_test_006_001_execute(void) {
  thread_t *tp, *tp1;
  msg_t msg;

  /* [6.1.1] Starting the messenger thread.*/
  test_set_step(1);
  {
    thread_config_t tc = {
      chThdGetPriorityX() - 1,
      "messager",
      wa_common,
      THD_WORKING_AREA_END(wa_common),
      messager,
      chThdGetSelfX()
    };
    tp1 = chThdCreate(&tc);
  }

  /* [6.1.2] Waiting for four messages then testing the receive
     order.*/
  test_set_step(2);
  {
    unsigned i;

    for (i = 0; i < 4; i++) {
      tp = chMsgWait();
      msg = chMsgGet(tp);
      chMsgRelease(tp, msg);
      test_emit_token(msg);
    }
    chThdWait(tp1);
    test_assert_sequence("ABCD", "invalid sequence");
  }
}

static const testcase_t nil_test_006_001 = {
  "Messages Server loop",
  NULL,
  NULL,
  nil_test_006_001_execute
};

/****************************************************************************
 * Exported data.
 ****************************************************************************/

/**
 * @brief   Array of test cases.
 */
const testcase_t * const nil_test_sequence_006_array[] = {
  &nil_test_006_001,
  NULL
};

/**
 * @brief   Synchronous Messages.
 */
const testsequence_t nil_test_sequence_006 = {
  "Synchronous Messages",
  nil_test_sequence_006_array
};

#endif /* CH_CFG_USE_MESSAGES */
