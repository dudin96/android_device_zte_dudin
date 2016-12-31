/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#define ISMATCH(a,b)    (!strncmp(a,b,PROP_VALUE_MAX))

void gsm_properties(bool msim);
void cdma_properties(const char *cdma_sub, const char *network);

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.radio", radio);

    property_set("ro.product.model", "ZTE V9820");

    if (ISMATCH(radio, "0x3")) {
        /* XT1072 */
        gsm_properties(false);
        property_set("ro.build.description", "dudin_retgb-user 6.0 MPB24.65-34 31 release-keys");
        property_set("ro.build.fingerprint", "zte/dudin_retgb/dudin:6.0/MPB24.65-34/31:user/release-keys");
        property_set("ro.build.product", "dudin");
        property_set("ro.zte.build.customerid", "retgball");
        property_set("ro.product.device", "dudin");
   } else if (ISMATCH(radio, "0xE")) {
        /* XT1077 */
        cdma_properties("0", "10");
        property_set("ro.build.description", "dudin_retcn_ds-user 6.0 MPB24.65-34 31 release-keys");
        property_set("ro.build.fingerprint", "zte/dudin_retcn_ds/dudin_ds:6.0/MPB24.65-34/31:user/release-keys");
        property_set("ro.build.product", "dudin_ds");
        property_set("ro.zte.build.customerid", "retcn");
        property_set("ro.product.device", "dudin_ds");
   } else if (ISMATCH(radio, "0xC")) {
        /* XT1078 */
        gsm_properties(true);
        property_set("ro.build.description", "dudin_retbr_ds-user 6.0 MPB24.65-34 31 release-keys");
        property_set("ro.build.fingerprint", "zte/dudin_retbr_ds/dudin_umtsds:6.0/MPB24.65-34/31:user/release-keys");
        property_set("ro.build.product", "dudin_umtsds");
        property_set("ro.zte.build.customerid", "retbr");
        property_set("ro.product.device", "dudin_umtsds");
    } else if (ISMATCH(radio, "0xD")) {
        /* XT1079 */
        cdma_properties("0", "20");
        property_set("ro.build.description", "dudin_retcn_ds-user 6.0 MPB24.65-34 31 release-keys");
        property_set("ro.build.fingerprint", "zte/dudin_retcn_ds/dudin_ds:6.0/MPB24.65-34/31:user/release-keys");
        property_set("ro.build.product", "dudin_ds");
        property_set("ro.zte.build.customerid", "retcn");
        property_set("ro.product.device", "dudin_ds");
    }

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    INFO("Found radio id %s setting build properties for %s device\n", radio, devicename);
}

void gsm_properties(bool msim)
{
    property_set("persist.radio.multisim.config", "");
    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");

    if (msim) {
        property_set("persist.radio.dont_use_dsd", "true");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("persist.radio.plmn_name_cmp", "1");
        property_set("ro.telephony.ril.config", "simactivation,sim2gsmonly");
    }
}

void cdma_properties(const char *cdma_sub, const char *network)
{
    property_set("DEVICE_PROVISIONED", "1");
    property_set("persist.radio.dont_use_dsd", "true");
    property_set("persist.radio.multisim.config", "dsds");
    property_set("persist.radio.plmn_name_cmp", "1");
    property_set("ril.subscription.types", "NV,RUIM");
    property_set("ro.com.google.clientidbase", "android-zte");
    property_set("ro.com.google.clientidbase.am", "android-zte");
    property_set("ro.com.google.clientidbase.gmm", "android-zte");
    property_set("ro.com.google.clientidbase.ms", "android-zte");
    property_set("ro.com.google.clientidbase.yt", "android-zte");
    property_set("ro.telephony.default_cdma_sub", cdma_sub);
    property_set("ro.telephony.default_network", network);
    property_set("ro.telephony.ril.config", "simactivation");
    property_set("telephony.lteOnCdmaDevice", "1");
}