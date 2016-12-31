#
# Copyright (C) 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# inherit from common msm8226-common
-include device/zte/msm8226-common/BoardConfigCommon.mk

DEVICE_PATH := device/zte/dudin

# Vendor Unification Init
TARGET_INIT_VENDOR_LIB := libinit_dudin
TARGET_RECOVERY_DEVICE_MODULES := libinit_dudin
TARGET_UNIFIED_DEVICE := true

# Assert
TARGET_OTA_ASSERT_DEVICE := dudin,dudin_umtsds,dudin_ds,XT1072,XT1078,XT1079

# Kernel
TARGET_KERNEL_CONFIG := dudin_defconfig

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 10444800
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 10526720
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1157627904
BOARD_USERDATAIMAGE_PARTITION_SIZE := 5207080960

# Properties
TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

# inherit from the proprietary version
-include vendor/zte/dudin/BoardConfigVendor.mk
