/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#ifdef USE_VTX_TABLE
#include <string.h>
#include "pg/vtx_table.h"
#include "drivers/vtx_table.h"
#endif

#include "pg/rx.h"
#include "pg/motor.h"

#include "io/vtx.h"
#include "io/ledstrip.h"

#include "rx/rx.h"

#include "fc/config.h"
#include "fc/rc_modes.h"
#include "fc/rc_controls.h"
#include "fc/controlrate_profile.h"

#include "osd/osd.h"

#include "flight/pid.h"
#include "flight/imu.h"

#include "drivers/motor.h"

#include "sensors/gyro.h"
#include "sensors/battery.h"

void targetConfiguration(void)
{
    pidProfilesMutable(0)->pid[PID_ROLL].P  = 66;
    pidProfilesMutable(0)->pid[PID_ROLL].I  = 40;
    pidProfilesMutable(0)->pid[PID_ROLL].D  = 44;
    pidProfilesMutable(0)->pid[PID_ROLL].F  = 20;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 72;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 45;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 43;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 20;
    pidProfilesMutable(0)->pid[PID_YAW].P   = 95;
    pidProfilesMutable(0)->pid[PID_YAW].I   = 45;
    pidProfilesMutable(0)->pid[PID_YAW].F   = 0;
    pidProfilesMutable(0)->pid[PID_LEVEL].P = 40;
    pidProfilesMutable(0)->pid[PID_LEVEL].I = 40;
    pidProfilesMutable(0)->pid[PID_LEVEL].D = 40;
    pidProfilesMutable(0)->levelAngleLimit = 85;
    pidProfilesMutable(0)->d_min[FD_ROLL] = 15;
    pidProfilesMutable(0)->d_min[FD_PITCH] = 17;

    controlRateProfilesMutable(0)->rates[FD_ROLL]   = 73;
    controlRateProfilesMutable(0)->rates[FD_PITCH]  = 73;
    controlRateProfilesMutable(0)->rates[FD_YAW]    = 73;
    controlRateProfilesMutable(0)->rcExpo[FD_ROLL]  = 15;
    controlRateProfilesMutable(0)->rcExpo[FD_PITCH] = 15;
    controlRateProfilesMutable(0)->rcExpo[FD_YAW]   = 15;
    controlRateProfilesMutable(0)->dynThrPID        = 55;

#ifdef USE_VTX_TABLE
    const uint16_t vtxTablePowerValues[VTX_TABLE_MAX_POWER_LEVELS] = {0, 1};
    const char *vtxTablePowerLabels[VTX_TABLE_MAX_POWER_LEVELS] = {"MIN", "MAX"};
    vtxTableConfigMutable()->powerLevels = 2;

    #if defined(USE_VTX_US_TABLE)
        const uint16_t vtxTableFrequency[VTX_TABLE_MAX_BANDS][VTX_TABLE_MAX_CHANNELS] = {
            {5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725}, // Boscam A
            {5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866}, // Boscam B
            {5705, 5685, 5665,    0, 5885, 5905,    0,    0}, // Boscam E
            {5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880}, // FatShark
            {5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917}, // RaceBand
            {5732, 5765, 5828, 5840, 5866, 5740,    0,    0}, // IMD6
        };
        const char *vtxTableBandNames[VTX_TABLE_MAX_BANDS] = {
            "BOSCAM A", "BOSCAM B", "BOSCAM E", "FATSHARK", "RACEBAND", "    IMD6",
        };
        const char vtxTableBandLetters[VTX_TABLE_MAX_BANDS] = "ABEFRI";
        const char *vtxTableChannelNames[VTX_TABLE_MAX_CHANNELS] = {
            "1", "2", "3", "4", "5", "6", "7", "8",
        };
        vtxTableConfigMutable()->bands = 6;
        vtxTableConfigMutable()->channels = 8;

    #else
        const uint16_t vtxTableFrequency[VTX_TABLE_MAX_BANDS][VTX_TABLE_MAX_CHANNELS] = {
            {5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725}, // Boscam A
            {5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866}, // Boscam B
            {5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945}, // Boscam E
            {5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880}, // FatShark
            {5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917}, // RaceBand
            {5732, 5765, 5828, 5840, 5866, 5740,    0,    0}, // IMD6
        };
        const char *vtxTableBandNames[VTX_TABLE_MAX_BANDS] = {
            "BOSCAM A", "BOSCAM B", "BOSCAM E", "FATSHARK", "RACEBAND", "    IMD6",
        };
        const char vtxTableBandLetters[VTX_TABLE_MAX_BANDS] = "ABEFRI";
        const char *vtxTableChannelNames[VTX_TABLE_MAX_CHANNELS] = {
            "1", "2", "3", "4", "5", "6", "7", "8",
        };
        vtxTableConfigMutable()->bands = 6;
        vtxTableConfigMutable()->channels = 8;

    #endif

    for (int band = 0; band < VTX_TABLE_MAX_BANDS; band++) {
        for (int channel = 0; channel < VTX_TABLE_MAX_CHANNELS; channel++) {
            vtxTableConfigMutable()->frequency[band][channel] = vtxTableFrequency[band][channel];
        }
        vtxTableStrncpyWithPad(vtxTableConfigMutable()->bandNames[band], vtxTableBandNames[band], VTX_TABLE_BAND_NAME_LENGTH);
        vtxTableConfigMutable()->bandLetters[band] = vtxTableBandLetters[band];
    }

    for (int channel = 0; channel < VTX_TABLE_MAX_CHANNELS; channel++) {
        vtxTableStrncpyWithPad(vtxTableConfigMutable()->channelNames[channel], vtxTableChannelNames[channel], VTX_TABLE_CHANNEL_NAME_LENGTH);
    }

    for (int level = 0; level < VTX_TABLE_MAX_POWER_LEVELS; level++) {
        vtxTableConfigMutable()->powerValues[level] = vtxTablePowerValues[level];
        vtxTableStrncpyWithPad(vtxTableConfigMutable()->powerLabels[level], vtxTablePowerLabels[level], VTX_TABLE_POWER_LABEL_LENGTH);
    }

    for (int band = 0; band < VTX_TABLE_MAX_BANDS; band++) {
        vtxTableConfigMutable()->isFactoryBand[band] = false;
    }

#endif /* USE_VTX_TABLE */

    strcpy(pilotConfigMutable()->name, "BeeBrain Pro");

    pidConfigMutable()->pid_process_denom = 1;

    imuConfigMutable()->small_angle = 180;

#if defined(BEEBRAIN_PRO_DSM)
    rxConfigMutable()->mincheck = 1165;
    rxConfigMutable()->rssi_channel = AUX5 + 1;
    for (uint8_t rxRangeIndex = 0; rxRangeIndex < NON_AUX_CHANNEL_COUNT; rxRangeIndex++) {

        rxChannelRangeConfig_t *channelRangeConfig = rxChannelRangeConfigsMutable(rxRangeIndex);

        channelRangeConfig->min = 1160;
        channelRangeConfig->max = 1840;
    }

    rxFailsafeChannelConfigsMutable(AUX5)->mode = RX_FAILSAFE_MODE_SET;
    rxFailsafeChannelConfigsMutable(AUX5)->step = 10;
#endif

    vtxSettingsConfigMutable()->band = 5;
    vtxSettingsConfigMutable()->channel = 8;
    vtxSettingsConfigMutable()->power = 1;

    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_BRUSHED;
    motorConfigMutable()->dev.motorPwmRate = 25000;
    motorConfigMutable()->minthrottle = 1030;

    batteryConfigMutable()->vbatmincellvoltage = 290;
    batteryConfigMutable()->vbatmaxcellvoltage = 440;
    batteryConfigMutable()->vbatfullcellvoltage = 410;
    batteryConfigMutable()->vbatwarningcellvoltage = 310;

    modeActivationConditionsMutable(0)->modeId          = BOXARM;
    modeActivationConditionsMutable(0)->auxChannelIndex = AUX1 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(0)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(0)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(1)->modeId          = BOXANGLE;
    modeActivationConditionsMutable(1)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(1)->range.startStep = CHANNEL_VALUE_TO_STEP(900);
    modeActivationConditionsMutable(1)->range.endStep   = CHANNEL_VALUE_TO_STEP(1300);

    modeActivationConditionsMutable(2)->modeId          = BOXHORIZON;
    modeActivationConditionsMutable(2)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(2)->range.startStep = CHANNEL_VALUE_TO_STEP(1300);
    modeActivationConditionsMutable(2)->range.endStep   = CHANNEL_VALUE_TO_STEP(1700);

    modeActivationConditionsMutable(3)->modeId          = BOXFLIPOVERAFTERCRASH;
    modeActivationConditionsMutable(3)->auxChannelIndex = AUX3 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(3)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(3)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    osdConfigMutable()->item_pos[OSD_ITEM_TIMER_2]      = OSD_POS( 1, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_RSSI_VALUE]        = OSD_POS( 1, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_VTX_CHANNEL]       = OSD_POS(10, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_WARNINGS]          = OSD_POS(10, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_CRAFT_NAME]        = OSD_POS(10, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_FLYMODE]           = OSD_POS(18, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE] = OSD_POS(24, 10) | OSD_PROFILE_1_FLAG;
#if defined(BEEBRAIN_PRO_DSM)
    osdConfigMutable()->item_pos[OSD_CURRENT_DRAW]      = OSD_POS(23, 11) | OSD_PROFILE_1_FLAG;
#endif

    ledStripStatusModeConfigMutable()->ledConfigs[0] = DEFINE_LED(7, 7,  8, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[1] = DEFINE_LED(8, 7, 13, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[2] = DEFINE_LED(9, 7, 11, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
}

#endif /* USE_TARGET_CONFIG */