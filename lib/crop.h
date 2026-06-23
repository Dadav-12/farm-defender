#ifndef CROP_H
#define CROP_H

typedef enum
{
    CROP_DRY,
    CROP_WATERED,
    CROP_READY
} CropState;

typedef enum
{
    CROP_WHEAT,
    CROP_TOMATO,
    CROP_CORN,
    CROP_BERRY
} CropType;

typedef struct
{
    float growth_time;
    int sell_value;
} CropData;

typedef struct
{
    int id;
    CropType type;
    CropState state;
    float growth_timer;
} Crop;

#endif