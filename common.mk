#
# Copyright (C) 2012 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

COMMON_PATH := device/samsung/smdk4412-common

DEVICE_PACKAGE_OVERLAYS := $(COMMON_PATH)/overlay

# RRO (Runtime Resource Overlay)
PRODUCT_ENFORCE_RRO_TARGETS += *
PRODUCT_ENFORCE_RRO_EXCLUDED_OVERLAYS  += * \
    $(COMMON_PATH)/overlay-lineage/lineage-sdk \
    $(COMMON_PATH)/overlay/hardware

PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=0

# Component overrides
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/component-overrides.xml:$(TARGET_COPY_OUT_VENDOR)/etc/sysconfig/component-overrides.xml

# Init files
PRODUCT_PACKAGES += \
    ueventd.smdk4x12.rc

PRODUCT_COPY_FILES := \
    $(COMMON_PATH)/rootdir/init.smdk4x12.rc:root/init.smdk4x12.rc \
    $(COMMON_PATH)/rootdir/init.smdk4x12.usb.rc:root/init.smdk4x12.usb.rc \
    $(COMMON_PATH)/rootdir/init.trace.rc:root/init.trace.rc

# init.d
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/tweaks.rc:system/vendor/etc/init/tweaks.rc

# Enable iorapd
PRODUCT_PROPERTY_OVERRIDES += \
	ro.iorapd.enable=true \
	iorapd.perfetto.enable=true \
	iorapd.readahead.enable=true

# RIL subscription workaround
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/restart_rild.sh:system/vendor/bin/restart_rild.sh \
    $(LOCAL_PATH)/configs/rild_restart.rc:system/vendor/etc/init/rild_restart.rc

# Shim providing strdup8to16 for RIL
PRODUCT_PACKAGES += \
    libCutils

# Gps
PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/gps.conf:system/etc/gps.conf \
    $(COMMON_PATH)/configs/gps_debug.conf:$(TARGET_COPY_OUT_SYSTEM)/etc/gps_debug.conf

# USB
PRODUCT_PACKAGES += \
    android.hardware.usb@1.0-service.basic \
    com.android.future.usb.accessory

# Use legacy ADB USB support
PRODUCT_PROPERTY_OVERRIDES += \
    ro.adb.nonblocking_ffs=false

# Trust HAL
#PRODUCT_PACKAGES += \
#    vendor.lineage.trust@1.0-service

# Battery
PRODUCT_PROPERTY_OVERRIDES += \
    ro.config.small_battery=true

# Light
PRODUCT_PACKAGES += \
    android.hardware.light@2.0-service.samsung

# Charger
PRODUCT_PROPERTY_OVERRIDES += \
    ro.charger.enable_suspend=true

# Audio
PRODUCT_PACKAGES += \
    android.hardware.audio@7.0-impl \
    android.hardware.audio.effect@7.0-impl \
    android.hardware.audio.effect@2.0-service \
    android.hardware.audio.service \
    audio.a2dp.default \
    audio.primary.smdk4x12 \
    audio.r_submix.default \
    audio.usb.default \
    tinymix

PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/audio_effects.conf:system/etc/audio_effects.conf \
    $(COMMON_PATH)/audio/silence.wav:system/etc/sound/silence.wav \
    $(COMMON_PATH)/configs/audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_configuration.xml \
    $(COMMON_PATH)/configs/a2dp_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/a2dp_audio_policy_configuration.xml \
    $(COMMON_PATH)/configs/usb_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/usb_audio_policy_configuration.xml

PRODUCT_COPY_FILES += \
    frameworks/av/services/audiopolicy/config/audio_policy_volumes.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_volumes.xml \
    frameworks/av/services/audiopolicy/config/default_volume_tables.xml:$(TARGET_COPY_OUT_VENDOR)/etc/default_volume_tables.xml

# Bluetooth
PRODUCT_PACKAGES += \
    android.hardware.bluetooth@1.0-impl \
    android.hardware.bluetooth@1.0-service \
    libbt-vendor

# Graphics
PRODUCT_PACKAGES += \
    AdvancedDisplay \
    android.hardware.graphics.allocator@2.0-impl-exynos4 \
    android.hardware.graphics.mapper@2.0-impl-exynos4 \
    android.hardware.graphics.composer@2.1-impl \
    hwcomposer.exynos4 \
    gralloc.exynos4 \
    libUMP \
    libMali \
    libEGL_mali \
    libfimc \
    libfimg \
    libhwjpeg \
    libsecion \
    libsync

# Camera
PRODUCT_PACKAGES += \
    android.hardware.camera.provider@2.5-impl \
    android.hardware.camera.provider@2.5-service \
    camera.device@1.0-impl \
    gCam

PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/80cfw:system/etc/init.d/80cfw

# Sensors
PRODUCT_PACKAGES += \
    android.hardware.sensors@1.0-impl

# Vibrator
PRODUCT_PACKAGES += \
    android.hardware.vibrator@1.0-impl \
    android.hardware.vibrator@1.0-service

# Keymaster
PRODUCT_PACKAGES += \
    android.hardware.keymaster@3.0-impl \
    android.hardware.authsecret@1.0-service \
    android.hardware.gatekeeper@1.0-service.software

# Misc stuff
PRODUCT_PACKAGES += \
    libnetcmdiface \
    libstagefright-shim \
    libC

# Health
PRODUCT_PACKAGES += \
    android.hardware.health@2.0-impl \
    android.hardware.health@2.0-service

# DRM
PRODUCT_PACKAGES += \
    android.hardware.drm@1.0-impl \
    android.hardware.drm@1.0-service

# MFC API
PRODUCT_PACKAGES += \
    libsecmfcdecapi \
    libsecmfcencapi

# OMX
PRODUCT_PACKAGES += \
    libhwconverter \
    libstagefrighthw \
    libSEC_OMX_Resourcemanager \
    libSEC_OMX_Core \
    libOMX.SEC.AVC.Decoder \
    libOMX.SEC.M4V.Decoder \
    libOMX.SEC.WMV.Decoder \
    libOMX.SEC.AVC.Encoder \
    libOMX.SEC.M4V.Encoder
#   libOMX.SEC.VP8.Decoder

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/mediaserver.rc:system/etc/init/mediaserver.rc

PRODUCT_PROPERTY_OVERRIDES += \
    media.settings.xml=/vendor/etc/media_profiles.xml \
    debug.stagefright.ccodec=0 \
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true \
    debug.stagefright.omx_default_rank.sw-audio=1 \
    debug.stagefright.omx_default_rank=0 \
    vendor.mediacodec.binder.size=4 \
    media.stagefright.thumbnail.prefer_hw_codecs=true

PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/media_profiles.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles.xml \
    $(COMMON_PATH)/configs/media_profiles.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_profiles_V1_0.xml \
    $(COMMON_PATH)/configs/media_codecs.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_telephony.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_telephony.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video_le.xml

# Memory Optimizations
PRODUCT_PROPERTY_OVERRIDES += \
    ro.lmk.use_psi=false \
    ro.lmk.critical=0 \
    ro.lmk.low=950 \
    ro.vendor.qti.am.reschedule_service=true \
    ro.vendor.qti.sys.fw.use_trim_settings=true \
    ro.vendor.qti.sys.fw.trim_empty_percent=50 \
    ro.vendor.qti.sys.fw.trim_cache_percent=100 \
    ro.vendor.qti.sys.fw.empty_app_percent=25

# Reduces GC frequency of foreground apps by 50%
PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.foreground-heap-growth-multiplier=2.0

# Filesystem management tools
PRODUCT_PACKAGES += \
    make_ext4fs \
    setup_fs

# Live Wallpapers
PRODUCT_PACKAGES += \
    Galaxy4 \
    HoloSpiralWallpaper \
    LiveWallpapers \
    LiveWallpapersPicker \
    MagicSmokeWallpapers \
    NoiseField \
    PhaseBeam \
    VisualizationWallpapers \
    librs_jni

# Wifi
PRODUCT_PACKAGES += \
    android.hardware.wifi@1.0-service-lazy.legacy \
    android.hardware.wifi.supplicant@1.0 \
    macloader \
    wificond \
    libwpa_client \
    hostapd \
    dhcpcd.conf \
    WifiOverlay \
    wpa_supplicant \
    wpa_supplicant.conf

PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0 \
    wifi.supplicant_scan_interval=30 \
    net.tethering.noprovisioning=true

PRODUCT_COPY_FILES += \
    $(COMMON_PATH)/configs/wpa_supplicant_overlay.conf:system/vendor/etc/wifi/wpa_supplicant_overlay.conf \
    $(COMMON_PATH)/configs/p2p_supplicant_overlay.conf:system/vendor/etc/wifi/p2p_supplicant_overlay.conf

# These are the hardware-specific features
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.camera.autofocus.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.camera.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.location.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.location.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.touchscreen.multitouch.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.touchscreen.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.sip.voip.xml \
    frameworks/native/data/etc/android.software.sip.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.sip.xml

# Feature live wallpaper
PRODUCT_COPY_FILES += \
    packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.live_wallpaper.xml

PRODUCT_TAGS += dalvik.gc.type-precise

# Keylayouts
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/excluded-input-devices.xml:system/etc/excluded-input-devices.xml

# Stylus gestures
PRODUCT_PACKAGES += \
    org.lineageos.keyhandler

# Graphics
PRODUCT_PROPERTY_OVERRIDES += \
    ro.zygote.disable_gl_preload=1 \
    ro.opengles.version=131072 \
    ro.bq.gpu_to_cpu_unsupported=1 \
    debug.hwui.render_dirty_regions=false

# Include exynos4 platform specific parts
TARGET_HAL_PATH := hardware/samsung/exynos4/hal
TARGET_OMX_PATH := hardware/samsung/exynos/multimedia/openmax
$(call inherit-product, hardware/samsung/exynos4x12.mk)

# Shipping API level
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_k.mk)

# Include non-opensource parts
$(call inherit-product, vendor/samsung/smdk4412-common/smdk4412-common-vendor.mk)

# Include Lineage sepolicy for Exynos
#$(call inherit-product, device/fluid/sepolicy/exynos/sepolicy.mk)

TARGET_SYSTEM_PROP += \
    $(COMMON_PATH)/smdk4x12.prop

# Art
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    dalvik.vm.dex2oat-threads=1 \
    dalvik.vm.image-dex2oat-threads=1

# Use go
$(call inherit-product, $(LOCAL_PATH)/go_defaults.mk)

# Apply Dalvik config for 1G phone
$(call inherit-product, frameworks/native/build/phone-xhdpi-1024-dalvik-heap.mk)

# Include debugging props
$(call inherit-product, device/samsung/smdk4412-common/system_prop_debug.mk)
