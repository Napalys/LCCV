/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2020, Raspberry Pi (Trading) Ltd.
 *
 * options.hpp - common program options
 */

#pragma once

#include <fstream>
#include <iostream>

#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/control_ids.h>
#include <libcamera/property_ids.h>
#include <libcamera/transform.h>

enum Exposure_Modes {
    EXPOSURE_NORMAL = libcamera::controls::ExposureNormal,
    EXPOSURE_SHORT = libcamera::controls::ExposureShort,
    EXPOSURE_CUSTOM = libcamera::controls::ExposureCustom
};

enum Metering_Modes {
    METERING_CENTRE = libcamera::controls::MeteringCentreWeighted,
    METERING_SPOT = libcamera::controls::MeteringSpot,
    METERING_MATRIX = libcamera::controls::MeteringMatrix,
    METERING_CUSTOM = libcamera::controls::MeteringCustom
};

enum WhiteBalance_Modes {
    WB_AUTO = libcamera::controls::AwbAuto,
    WB_NORMAL = libcamera::controls::AwbAuto,
    WB_INCANDESCENT = libcamera::controls::AwbIncandescent,
    WB_TUNGSTEN = libcamera::controls::AwbTungsten,
    WB_FLUORESCENT = libcamera::controls::AwbFluorescent,
    WB_INDOOR = libcamera::controls::AwbIndoor,
    WB_DAYLIGHT = libcamera::controls::AwbDaylight,
    WB_CLOUDY = libcamera::controls::AwbCloudy,
    WB_CUSTOM = libcamera::controls::AwbAuto
};

class Options
{
public:
	Options()
	{
        timeout=1000;
        metering_index = Metering_Modes::METERING_CENTRE;
        exposure_index=Exposure_Modes::EXPOSURE_NORMAL;
        awb_index=WhiteBalance_Modes::WB_AUTO;
        saturation=1.0f;
        contrast=1.0f;
        sharpness=1.0f;
	brightness=0.0f;
	shutter=0.0f;
	gain=0.0f;
	ev=0.0f;
	roi_x=roi_y=roi_width=roi_height=0;
	awb_gain_r=awb_gain_b=0;
        denoise="auto";
        verbose=false;
	transform=libcamera::Transform::Identity;
	camera=0;
	}

	virtual ~Options() noexcept = default;

	virtual void Print() const;

    void setMetering(Metering_Modes meteringmode){metering_index=meteringmode;}
    void setWhiteBalance(WhiteBalance_Modes wb){awb_index = wb;}
    void setExposureMode(Exposure_Modes exp){exposure_index = exp;}

    int getExposureMode(){return exposure_index;}
    int getMeteringMode(){return metering_index;}
    int getWhiteBalance(){return awb_index;}

	bool help;
	bool version;
	bool list_cameras;
	bool verbose;
	uint64_t timeout; // in ms
    unsigned int photo_width, photo_height;
    unsigned int video_width, video_height;
	bool rawfull;
	libcamera::Transform transform;
	float roi_x, roi_y, roi_width, roi_height;
	float shutter;
	float gain;
	float ev;
	float awb_gain_r;
	float awb_gain_b;
	float brightness;
	float contrast;
	float saturation;
	float sharpness;
	float framerate;
	std::string denoise;
	std::string info_text;
	unsigned int camera;
    /// Auto focus on a region e.g. 0.25,0.25,0.5,0.5 works only with mode = AfModeContinuous
    float auto_focus_x = 0, auto_focus_y = 0, auto_focus_width = 0, auto_focus_height = 0;
    /// AfSpeedNormal = 0, AfSpeedFast = 1
    libcamera::controls::AfSpeedEnum auto_focus_speed = libcamera::controls::AfSpeedNormal;
    /// AfRangeNormal = 0, AfRangeMacro = 1, AfRangeFull = 2
    libcamera::controls::AfRangeEnum auto_focus_range = libcamera::controls::AfRangeNormal;
    /// AfModeManual = 0, AfModeAuto = 1, AfModeContinuous = 2
    libcamera::controls::AfModeEnum auto_focus_mode = libcamera::controls::AfModeManual;
    /// Works only with AfModeManual values range from 0 to infinity
    float lens_position = 0.f;

protected:
	int metering_index;
	int exposure_index;
    int awb_index;
};
