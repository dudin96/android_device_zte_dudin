$(call inherit-product, device/zte/dudin/full_dudin.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_RELEASE_NAME := dudin
PRODUCT_NAME := cm_dudin

PRODUCT_GMS_CLIENTID_BASE := android-zte
