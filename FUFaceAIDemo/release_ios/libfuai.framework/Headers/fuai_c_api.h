// Copyright (C) 2019 FaceUnity Inc. All rights reserved.

#ifndef FUAI_C_C_API_H_
#define FUAI_C_C_API_H_

#include <stdint.h>

#if defined(_WIN32)
#ifdef FUAI_BUILD_SHARED_LIB
#define FUAI_CAPI_EXPORT __declspec(dllexport)
#else
#define FUAI_CAPI_EXPORT
#endif
#else
#define FUAI_CAPI_EXPORT __attribute__((visibility("default")))
#endif  // _WIN32

#ifdef __cplusplus
extern "C" {
#endif

FUAI_CAPI_EXPORT extern const char* FUAI_Version();

typedef enum FUAI_DataType {
  FUAI_FLOAT = 1,
  FUAI_DOUBLE = 2,
  FUAI_INT64 = 3,
  FUAI_INT32 = 4,
  FUAI_INT16 = 5,
  FUAI_INT8 = 6,
  FUAI_UINT64 = 7,
  FUAI_UINT32 = 8,
  FUAI_UINT16 = 9,
  FUAI_UINT8 = 10,
  FUAI_BOOL = 11,
} FUAI_DataType;

FUAI_CAPI_EXPORT extern void FUAI_VLogSetLevel(int level);

// --------------------------------------------------------------------------
// ImageView

typedef enum FUAI_ImageFormat {
  FUAI_IMAGE_UNKNOWN = 0,
  FUAI_IMAGE_RGB = 1,
  FUAI_IMAGE_BGR = 2,
  FUAI_IMAGE_RGBA = 3,
  FUAI_IMAGE_BGRA = 4,
  FUAI_IMAGE_ARGB = 5,
  FUAI_IMAGE_ABGR = 6,
  FUAI_IMAGE_GRAY = 7,
  FUAI_IMAGE_YUV_NV12 = 8,
  FUAI_IMAGE_YUV_NV21 = 9,
  FUAI_IMAGE_YUV_I420 = 10,
} FUAI_ImageFormat;

typedef enum FUAI_ImageRotation {
  FUAI_IMAGE_ROTATION_0 = 0,
  FUAI_IMAGE_ROTATION_90 = 1,
  FUAI_IMAGE_ROTATION_180 = 2,
  FUAI_IMAGE_ROTATION_270 = 3,
} FUAI_ImageRotation;

typedef struct FUAI_ImageView FUAI_ImageView;

FUAI_CAPI_EXPORT extern FUAI_ImageView* FUAI_NewImageView();

FUAI_CAPI_EXPORT extern void FUAI_DeleteImageView(FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern void FUAI_ImageViewInit(
    FUAI_ImageView* image_view, FUAI_ImageFormat format, int width, int height,
    FUAI_ImageRotation rotation, const uint8_t* data0, int stride0,
    const uint8_t* data1, int stride1, const uint8_t* data2, int stride2);

FUAI_CAPI_EXPORT extern void FUAI_ImageViewSetData(FUAI_ImageView* image_view,
                                                   int index,
                                                   const uint8_t* data);

// --------------------------------------------------------------------------
// CameraView

typedef enum FUAI_CameraViewMode {
  FUAI_CAMERA_VIEW_RGB = 0,
  FUAI_CAMERA_VIEW_BGR = 1,
  FUAI_CAMERA_VIEW_RGBA = 2,
  FUAI_CAMERA_VIEW_BGRA = 3,
  FUAI_CAMERA_VIEW_GRAY = 4,
  FUAI_CAMERA_VIEW_YUV_NV12 = 5,
  FUAI_CAMERA_VIEW_YUV_NV21 = 6,
  FUAI_CAMERA_VIEW_YUV_I420 = 7,
} FUAI_CameraViewMode;

typedef enum FUAI_CameraViewRotate {
  FUAI_CAMERA_VIEW_ROT_0 = 0,
  FUAI_CAMERA_VIEW_ROT_90 = 1,
  FUAI_CAMERA_VIEW_ROT_180 = 2,
  FUAI_CAMERA_VIEW_ROT_270 = 3,
} FUAI_CameraViewRotate;

typedef struct FUAI_CameraView FUAI_CameraView;

FUAI_CAPI_EXPORT extern FUAI_CameraView* FUAI_NewCameraView();

FUAI_CAPI_EXPORT extern void FUAI_DeleteCameraView(
    FUAI_CameraView* camera_view);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetHeight(
    FUAI_CameraView* camera_view, int height);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetWidth(
    FUAI_CameraView* camera_view, int width);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetMode(
    FUAI_CameraView* camera_view, FUAI_CameraViewMode mode);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetDataPoint(
    FUAI_CameraView* camera_view, void* data);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetDataType(
    FUAI_CameraView* camera_view, FUAI_DataType data_type);

FUAI_CAPI_EXPORT extern void FUAI_CameraViewSetRot(FUAI_CameraView* camera_view,
                                                   FUAI_CameraViewRotate rot);

// -------------------------------------------------------------------------
// Timer

FUAI_CAPI_EXPORT extern void FUAI_TimerDisable();

FUAI_CAPI_EXPORT extern int FUAI_TimerPoolGetNumTimers();

FUAI_CAPI_EXPORT extern const char* FUAI_TimerPoolGetTimerName(int index);

FUAI_CAPI_EXPORT extern uint64_t FUAI_TimerPoolGetTimerAverage(int index);

FUAI_CAPI_EXPORT extern uint64_t FUAI_TimerPoolGetTimerCount(int index);

FUAI_CAPI_EXPORT extern uint64_t FUAI_TimerPoolGetTimerMin(int index);

FUAI_CAPI_EXPORT extern uint64_t FUAI_TimerPoolGetTimerMax(int index);

FUAI_CAPI_EXPORT extern void FUAI_TimerPoolResetAllTimers();

// -------------------------------------------------------------------------
// FileBuffer

typedef struct FUAI_FileBuffer FUAI_FileBuffer;

FUAI_CAPI_EXPORT extern FUAI_FileBuffer* FUAI_NewFileBuffer();

FUAI_CAPI_EXPORT extern void FUAI_DeleteFileBuffer(FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern void FUAI_FileBufferSet(FUAI_FileBuffer* buffer,
                                                const char* key,
                                                const char* data,
                                                const int data_size);

FUAI_CAPI_EXPORT extern void FUAI_FileBufferSetFromZipBuffer(
    FUAI_FileBuffer* buffer, const char* zip_buffer, int zip_buffer_size);

FUAI_CAPI_EXPORT extern void FUAI_FileBufferLoadFile(FUAI_FileBuffer* buffer,
                                                     const char* path);

// -------------------------------------------------------------------------
// TfliteModel

typedef struct FUAI_TfliteModel FUAI_TfliteModel;

FUAI_CAPI_EXPORT extern FUAI_TfliteModel* FUAI_NewTfliteModel(
    const char* buffer, int buffer_size, int model_threads);

FUAI_CAPI_EXPORT extern void FUAI_DeleteTfliteModel(FUAI_TfliteModel* model);

FUAI_CAPI_EXPORT extern void FUAI_TfliteModelRun(FUAI_TfliteModel* model);

FUAI_CAPI_EXPORT extern void FUAI_TfliteModelSetInputData(
    FUAI_TfliteModel* model, int index, const void* data, int data_size);

FUAI_CAPI_EXPORT extern const void* FUAI_TfliteModelGetOutputData(
    FUAI_TfliteModel* model, int index);

// -------------------------------------------------------------------------
// tflite dsp

FUAI_CAPI_EXPORT extern void FUAI_TfliteHexagonInitWithPath(
    const char* lib_directory_path);

FUAI_CAPI_EXPORT extern void FUAI_TfliteHexagonTearDown();

// --------------------------------------------------------------------------
// BackgroundSegmenter

typedef struct FUAI_BackgroundSegmenter FUAI_BackgroundSegmenter;

FUAI_CAPI_EXPORT extern FUAI_BackgroundSegmenter* FUAI_NewBackgroundSegmenterV1(
    const char* buffer, int buffer_size, const char* param_string);

FUAI_CAPI_EXPORT extern FUAI_BackgroundSegmenter* FUAI_NewBackgroundSegmenter(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern FUAI_BackgroundSegmenter*
FUAI_NewBackgroundSegmenterFromBundle(const char* data, int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteBackgroundSegmenter(
    FUAI_BackgroundSegmenter* model);

FUAI_CAPI_EXPORT extern void FUAI_BackgroundSegmenterReset(
    FUAI_BackgroundSegmenter* model);

FUAI_CAPI_EXPORT extern void FUAI_BackgroundSegmenterInference(
    FUAI_BackgroundSegmenter* model, const FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern const float* FUAI_BackgroundSegmenterGetResultMask(
    const FUAI_BackgroundSegmenter* model, int* mask_height, int* mask_width);

FUAI_CAPI_EXPORT extern const float* FUAI_BackgroundSegmenterInferenceV1(
    FUAI_BackgroundSegmenter* model, const uint8_t* input_data);

// --------------------------------------------------------------------------
// GestureDetector

typedef enum FUAI_GestureType {
  FUAI_GESTURE_NO_HAND = -1,
  FUAI_GESTURE_UNKNOWN = 0,
  FUAI_GESTURE_THUMB = 1,
  FUAI_GESTURE_KORHEART = 2,
  FUAI_GESTURE_SIX = 3,
  FUAI_GESTURE_FIST = 4,
  FUAI_GESTURE_PALM = 5,
  FUAI_GESTURE_ONE = 6,
  FUAI_GESTURE_TWO = 7,
  FUAI_GESTURE_OK = 8,
  FUAI_GESTURE_ROCK = 9,
  FUAI_GESTURE_CROSS = 10,
  FUAI_GESTURE_HOLD = 11,
  FUAI_GESTURE_GREET = 12,
  FUAI_GESTURE_PHOTO = 13,
  FUAI_GESTURE_HEART = 14,
  FUAI_GESTURE_MERGE = 15,
  FUAI_GESTURE_EIGHT = 16,
  FUAI_GESTURE_HALFFIST = 17,
  FUAI_GESTURE_GUN = 18,
} FUAI_GestureType;

typedef struct FUAI_GestureDetector FUAI_GestureDetector;

FUAI_CAPI_EXPORT extern FUAI_GestureDetector* FUAI_NewGestureDetectorV1(
    const char* model_buffer, int model_buffer_size, const char* param_string);

FUAI_CAPI_EXPORT extern FUAI_GestureDetector* FUAI_NewGestureDetector(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern int FUAI_GestureDetectorDetect(
    FUAI_GestureDetector* model, const float* input_data,
    int* output_num_detections, float* output_boxes, int* output_classes,
    float* output_scores);

FUAI_CAPI_EXPORT extern void FUAI_DeleteGestureDetector(
    FUAI_GestureDetector* model);

typedef struct FUAI_HandDetector FUAI_HandDetector;

FUAI_CAPI_EXPORT extern FUAI_HandDetector* FUAI_NewHandDetectorFromBundle(
    const char* data, int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHandDetector(FUAI_HandDetector* model);

FUAI_CAPI_EXPORT extern void FUAI_HandDetectorProcess(
    FUAI_HandDetector* model, const FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern int FUAI_HandDetectorGetResultNumHands(
    const FUAI_HandDetector* model);

FUAI_CAPI_EXPORT extern const float* FUAI_HandDetectorGetResultHandRect(
    const FUAI_HandDetector* model, int index);

FUAI_CAPI_EXPORT extern FUAI_GestureType FUAI_HandDetectorGetResultGestureType(
    const FUAI_HandDetector* model, int index);

FUAI_CAPI_EXPORT extern float FUAI_HandDetectorGetResultHandScore(
    const FUAI_HandDetector* model, int index);

// --------------------------------------------------------------------------
// HandProcessor

typedef struct FUAI_HandProcessor FUAI_HandProcessor;

FUAI_CAPI_EXPORT extern FUAI_HandProcessor* FUAI_NewHandProcessor(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern FUAI_HandProcessor* FUAI_NewHandProcessorFromBundle(
    const char* data, int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHandProcessor(
    FUAI_HandProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_HandProcessorProcess(
    FUAI_HandProcessor* model, const FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern int FUAI_HandProcessorGetNumResults(
    const FUAI_HandProcessor* model);

FUAI_CAPI_EXPORT extern const float* FUAI_HandProcessorGetResultHandRect(
    const FUAI_HandProcessor* model, int index);

FUAI_CAPI_EXPORT extern FUAI_GestureType FUAI_HandProcessorGetResultGestureType(
    const FUAI_HandProcessor* model, int index);

FUAI_CAPI_EXPORT extern float FUAI_HandProcessorGetResultHandScore(
    const FUAI_HandProcessor* model, int index);

FUAI_CAPI_EXPORT extern int FUAI_HandProcessorGetResultTrackId(
    const FUAI_HandProcessor* model, int index);

// --------------------------------------------------------------------------
// HumanPoseDetector

typedef enum FUAI_HumanState {
  FUAI_HUMAN_NO_BODY = 0,
  FUAI_HUMAN_HALF_LESS_BODY = 1,
  FUAI_HUMAN_HALF_BODY = 2,
  FUAI_HUMAN_HALF_MORE_BODY = 3,
  FUAI_HUMAN_FULL_BODY = 4,
} FUAI_HumanState;

typedef enum FUAI_SceneState {
  FUAI_SCENE_SELFIE = 0,
  FUAI_SCENE_DANCE = 1,
} FUAI_SceneState;

typedef enum FUAI_GroundState {
  FUAI_GROUND_INVALID = 0,
  FUAI_GROUND_VALID = 1,
} FUAI_GroundState;

typedef struct FUAI_HumanPoseDetector FUAI_HumanPoseDetector;

FUAI_CAPI_EXPORT extern FUAI_HumanPoseDetector* FUAI_NewHumanPoseDetector(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern FUAI_HumanPoseDetector*
FUAI_NewHumanPoseDetectorFromBundle(const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHumanPoseDetector(
    FUAI_HumanPoseDetector* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanPoseDetectorInference(
    FUAI_HumanPoseDetector* model, const FUAI_CameraView* camera_view,
    float* output_keypoints);

FUAI_CAPI_EXPORT extern void FUAI_HumanPoseDetectorProcess(
    FUAI_HumanPoseDetector* model, const FUAI_CameraView* camera_view);

FUAI_CAPI_EXPORT extern int FUAI_HumanPoseDetectorHasHuman(
    FUAI_HumanPoseDetector* model);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanPoseDetectorGetResultKeypoint(
    const FUAI_HumanPoseDetector* model, int* size);

// --------------------------------------------------------------------------
// Human3DDetector

typedef struct FUAI_Human3DDetector FUAI_Human3DDetector;

typedef struct FUAI_Human3DDetectorResult FUAI_Human3DDetectorResult;

FUAI_CAPI_EXPORT extern FUAI_Human3DDetector* FUAI_NewHuman3DDetector(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern FUAI_Human3DDetector* FUAI_NewHuman3DDetectorFromBundle(
    const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHuman3DDetector(
    FUAI_Human3DDetector* model);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetScene(
    FUAI_Human3DDetector* model, FUAI_SceneState scene);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetYOffset(
    FUAI_Human3DDetector* model, float y_offset);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetAvatarScale(
    FUAI_Human3DDetector* model, const FUAI_SceneState scene, float scale);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetHalfbodySceneGlobalOffset(
    FUAI_Human3DDetector* model, float x_offset, float y_offset);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetFOV(
    FUAI_Human3DDetector* model, float fov);

FUAI_CAPI_EXPORT extern float FUAI_Human3DDetectorGetFOV(
    FUAI_Human3DDetector* model);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorSetBonemap(
    FUAI_Human3DDetector* model, const char* data, const int size);

FUAI_CAPI_EXPORT extern int FUAI_Human3DDetectorInference(
    FUAI_Human3DDetector* model, const FUAI_CameraView* camera_view,
    FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorReset(
    FUAI_Human3DDetector* model);

FUAI_CAPI_EXPORT extern FUAI_Human3DDetectorResult*
FUAI_NewHuman3DDetectorResult();

FUAI_CAPI_EXPORT extern void FUAI_DeleteHuman3DDetectorResult(
    FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern void FUAI_Human3DDetectorResultReset(
    FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern FUAI_HumanState FUAI_Human3DDetectorResultGetHumanState(
    const FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern const float*
FUAI_Human3DDetectorResultGetTransformArray(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetJoint2ds(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetJointScores(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetBoundingBox(
    const FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern const float*
FUAI_Human3DDetectorResultGetNetworkJoint3ds(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetOpt1Joint3ds(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetOpt2Joint3ds(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern FUAI_GroundState
FUAI_Human3DDetectorResultGetGroundState(
    const FUAI_Human3DDetectorResult* result);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetGroundNormal(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetGroundOrigin(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetFaceBbox(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetHandBboxes(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const FUAI_GestureType*
FUAI_Human3DDetectorResultGetGestureTypes(
    const FUAI_Human3DDetectorResult* result, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_Human3DDetectorResultGetGestureScores(
    const FUAI_Human3DDetectorResult* result, int* size);

// --------------------------------------------------------------------------
// HumanProcessor

typedef struct FUAI_HumanProcessor FUAI_HumanProcessor;

FUAI_CAPI_EXPORT extern FUAI_HumanProcessor* FUAI_NewHumanProcessorFromBundle(
    const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHumanProcessor(
    FUAI_HumanProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorProcess(
    FUAI_HumanProcessor* model, const FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorReset(
    FUAI_HumanProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorResetModules(
    FUAI_HumanProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetSceneState(
    FUAI_HumanProcessor* model, FUAI_SceneState scene_state);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetBonemap(
    FUAI_HumanProcessor* model, const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetFov(
    FUAI_HumanProcessor* model, float fov);

FUAI_CAPI_EXPORT extern float FUAI_HumanProcessorGetFov(
    FUAI_HumanProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetAvatarScale(
    FUAI_HumanProcessor* model, FUAI_SceneState scene_state, float scale);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetAvatarGlobalOffset(
    FUAI_HumanProcessor* model, FUAI_SceneState scene_state, float x, float y,
    float z);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetMaxHumans(
    FUAI_HumanProcessor* model, int max_humans);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetResetEveryNFrames(
    FUAI_HumanProcessor* model, int reset_every_n_frames);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetUseHumanKeypointProcessor(
    FUAI_HumanProcessor* model, int use_human_keypoint_processor);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetUseHumanKeypoint3d(
    FUAI_HumanProcessor* model, int use_human_keypoint3d);

FUAI_CAPI_EXPORT extern void FUAI_HumanProcessorSetUseHumanSegmenter(
    FUAI_HumanProcessor* model, int use_human_segmenter);

FUAI_CAPI_EXPORT extern int FUAI_HumanProcessorGetNumResults(
    const FUAI_HumanProcessor* model);

FUAI_CAPI_EXPORT extern const int FUAI_HumanProcessorGetResultTrackId(
    const FUAI_HumanProcessor* model, int index);

FUAI_CAPI_EXPORT extern const FUAI_HumanState
FUAI_HumanProcessorGetResultHumanState(const FUAI_HumanProcessor* model,
                                       int index);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultRect(
    const FUAI_HumanProcessor* model, int index);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultJoint2ds(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultJointScores(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultJoint3ds(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultTransformArray(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultModelMatrix(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const FUAI_GestureType*
FUAI_HumanProcessorGetResultGestureTypes(const FUAI_HumanProcessor* model,
                                         int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultGestureScores(
    const FUAI_HumanProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern int FUAI_HumanProcessorGetResultActionType(
    const FUAI_HumanProcessor* model, int index);

FUAI_CAPI_EXPORT extern float FUAI_HumanProcessorGetResultActionScore(
    const FUAI_HumanProcessor* model, int index);

FUAI_CAPI_EXPORT extern const float* FUAI_HumanProcessorGetResultHumanMask(
    const FUAI_HumanProcessor* model, int index, int* mask_width,
    int* mask_height);

FUAI_CAPI_EXPORT extern float FUAI_HumanActionMatchDistance(const float* p1,
                                                            int p1_size,
                                                            const float* p2,
                                                            int p2_size);

// --------------------------------------------------------------------------
// HumanMocapTransfer

typedef struct FUAI_HumanMocapTransfer FUAI_HumanMocapTransfer;

FUAI_CAPI_EXPORT extern FUAI_HumanMocapTransfer*
FUAI_NewHumanMocapTransferFromBundle(const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHumanMocapTransfer(
    FUAI_HumanMocapTransfer* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapTransferSetTPoseBonemap(
    FUAI_HumanMocapTransfer* model, const char* bonemap_data,
    const int bonemap_data_size, const char* collidmap_data,
    const int collidmap_data_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapTransferSetAvatarToMocapNameMap(
    FUAI_HumanMocapTransfer* model, const char* namemap_data,
    const int namemap_data_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapTransferProcess(
    FUAI_HumanMocapTransfer* model, const float* mocap_data,
    const int mocap_data_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapTransferProcessOnlyCollision(
    FUAI_HumanMocapTransfer* model, const float* transform_array,
    const int transform_array_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapTransferReset(
    FUAI_HumanMocapTransfer* model);

FUAI_CAPI_EXPORT extern const float*
FUAI_HumanMocapTransferGetResultTransformArray(FUAI_HumanMocapTransfer* model,
                                               int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_HumanMocapTransferGetResultCollisionTransformArray(
    FUAI_HumanMocapTransfer* model, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_HumanMocapTransferGetResultModelMatrix(FUAI_HumanMocapTransfer* model,
                                            int* size);

// --------------------------------------------------------------------------
// HumanMocapCollision

typedef struct FUAI_HumanMocapCollision FUAI_HumanMocapCollision;

FUAI_CAPI_EXPORT extern FUAI_HumanMocapCollision*
FUAI_NewHumanMocapCollisionFromBundle(const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteHumanMocapCollision(
    FUAI_HumanMocapCollision* model);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapCollisionSetBonemap(
    FUAI_HumanMocapCollision* model, const char* bonemap_data,
    const int bonemap_data_size, const char* collidmap_data,
    const int collidmap_data_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapCollisionSetSpecialbone(
    FUAI_HumanMocapCollision* model, const char* specialbone_data,
    const int specialbone_data_size);

FUAI_CAPI_EXPORT extern void FUAI_HumanMocapCollisionProcess(
    FUAI_HumanMocapCollision* model, const float* mocap_data,
    const int mocap_data_size);

FUAI_CAPI_EXPORT extern const float*
FUAI_HumanMocapCollisionGetResultTransformArray(FUAI_HumanMocapCollision* model,
                                                int* size);

// --------------------------------------------------------------------------
// FaceLandmark

typedef struct FUAI_FaceDetectLandmark FUAI_FaceDetectLandmark;

FUAI_CAPI_EXPORT extern FUAI_FaceDetectLandmark* FUAI_NewFaceDetectLandmarkV1(
    const char* detector_config_buffer,
    const char* landmark_camera_config_buffer, const char* detector_buffer,
    int detector_size, const char* landmark_face_model_buffer,
    int face_model_size, const char* landmark_eye_model_buffer,
    int eye_model_size, const char* landmark_eyebrow_model_buffer,
    int eyebrow_model_size, const char* landmark_mouth_model_buffer,
    int mouth_model_size);

FUAI_CAPI_EXPORT extern FUAI_FaceDetectLandmark* FUAI_NewFaceDetectLandmark(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern FUAI_FaceDetectLandmark*
FUAI_NewFaceDetectLandmarkFromBundle(const char* data, int size);

FUAI_CAPI_EXPORT extern int FUAI_FaceDetectLandmarkProcessFrame(
    FUAI_FaceDetectLandmark* model, const FUAI_CameraView* camera_view,
    int* facenum, float* output_landmarks, int* lm_length, float* isface,
    int* id, float* pose);

FUAI_CAPI_EXPORT extern void FUAI_FaceDetectLandmarkProcess(
    FUAI_FaceDetectLandmark* model, const FUAI_CameraView* camera_view);

FUAI_CAPI_EXPORT extern void FUAI_FaceDetectLandmarkFrameSetSmooth(
    FUAI_FaceDetectLandmark* model, float smooth_h);

FUAI_CAPI_EXPORT extern void FUAI_FaceDetectLandmarkFrameReset(
    FUAI_FaceDetectLandmark* model);

FUAI_CAPI_EXPORT extern int FUAI_FaceDetectLandmarkGetResultNumFace(
    FUAI_FaceDetectLandmark* model);

FUAI_CAPI_EXPORT extern int FUAI_FaceDetectLandmarkGetResultLandmarkLength(
    FUAI_FaceDetectLandmark* model);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceDetectLandmarkGetResultLandmarks(
    FUAI_FaceDetectLandmark* model, int index);

FUAI_CAPI_EXPORT extern int FUAI_FaceDetectLandmarkGetResultFaceId(
    FUAI_FaceDetectLandmark* model, int index);

FUAI_CAPI_EXPORT extern float FUAI_FaceDetectLandmarkGetResultFaceScore(
    FUAI_FaceDetectLandmark* model, int index);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceDetectLandmarkGetResultFacePose(
    FUAI_FaceDetectLandmark* model, int index);

FUAI_CAPI_EXPORT extern int FUAI_DeleteFaceDetectLandmark(
    FUAI_FaceDetectLandmark* model);

// --------------------------------------------------------------------------
// FaceCapture

typedef struct FUAI_FaceCaptureManager FUAI_FaceCaptureManager;

FUAI_CAPI_EXPORT extern FUAI_FaceCaptureManager* FUAI_NewFaceCaptureManager(
    const char* param_string, const FUAI_FileBuffer* buffer);

FUAI_CAPI_EXPORT extern int FUAI_FaceCaptureSetScene(
    FUAI_FaceCaptureManager* model, FUAI_SceneState scene);

FUAI_CAPI_EXPORT extern int FUAI_FaceCaptureSetFaceBbox(
    FUAI_FaceCaptureManager* model, float xmin, float ymin, float xmax,
    float ymax);

FUAI_CAPI_EXPORT extern int FUAI_DeleteFaceCaptureManager(
    FUAI_FaceCaptureManager* manager);

FUAI_CAPI_EXPORT extern int FUAI_FaceCaptureManagerProcessFrame(
    FUAI_FaceCaptureManager* manager, const FUAI_CameraView* camera_view);

FUAI_CAPI_EXPORT extern int FUAI_FaceCaptureManagerResetTracking(
    FUAI_FaceCaptureManager* manager);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceCaptureManagerGetResultLandmarks(
    FUAI_FaceCaptureManager* manager, int index, int* size);
FUAI_CAPI_EXPORT extern const float* FUAI_FaceCaptureManagerGetResultIdentity(
    FUAI_FaceCaptureManager* manager, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceCaptureManagerGetResultExpression(
    FUAI_FaceCaptureManager* manager, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceCaptureManagerGetResultRotation(
    FUAI_FaceCaptureManager* manager, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceCaptureManagerGetResultFaceBbox(
    FUAI_FaceCaptureManager* manager, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceCaptureManagerGetResultEyesRotation(FUAI_FaceCaptureManager* manager,
                                             int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceCaptureManagerGetResultTranslation(FUAI_FaceCaptureManager* manager,
                                            int index, int* size);

FUAI_CAPI_EXPORT extern const int FUAI_FaceCaptureManagerGetResultIsFace(
    FUAI_FaceCaptureManager* manager, int index);

FUAI_CAPI_EXPORT extern const int FUAI_FaceCaptureManagerGetResultFaceID(
    FUAI_FaceCaptureManager* manager, int index);

FUAI_CAPI_EXPORT extern const int FUAI_FaceCaptureManagerGetResultTongueCls(
    FUAI_FaceCaptureManager* manager, int index);

FUAI_CAPI_EXPORT extern const float FUAI_FaceCaptureManagerGetResultTongueScore(
    FUAI_FaceCaptureManager* manager, int index);

FUAI_CAPI_EXPORT extern const float FUAI_FaceCaptureManagerGetResultFaceScore(
    FUAI_FaceCaptureManager* manager, int index);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceCaptureManagerGetResultTongueExpression(
    FUAI_FaceCaptureManager* manager, int index, int* size);

FUAI_CAPI_EXPORT extern const float FUAI_FaceCaptureManagerGetResultFocalLength(
    FUAI_FaceCaptureManager* manager);

FUAI_CAPI_EXPORT extern const int FUAI_FaceCaptureManagerGetResultFaceNum(
    FUAI_FaceCaptureManager* manager);

// --------------------------------------------------------------------------
// FaceProcessor
typedef enum FUAI_FaceDetectMode {
  FUAI_FACE_DETECT_MODE_IMAGE = 0,
  FUAI_FACE_DETECT_MODE_VIDEO = 1
} FUAI_FaceDetectMode;

typedef struct FUAI_FaceProcessor FUAI_FaceProcessor;

FUAI_CAPI_EXPORT extern FUAI_FaceProcessor* FUAI_NewFaceProcessorFromBundle(
    const char* data, const int size);

FUAI_CAPI_EXPORT extern void FUAI_DeleteFaceProcessor(
    FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorProcess(
    FUAI_FaceProcessor* model, const FUAI_ImageView* image_view);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorReset(FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetMaxFaces(
    FUAI_FaceProcessor* model, int max_faces);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorResetModules(
    FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseFaceLandmark(
    FUAI_FaceProcessor* model, int use_face_landmark);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseDenseLandmark(
    FUAI_FaceProcessor* model, int use_dense_landmark);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseFaceDde(
    FUAI_FaceProcessor* model, int use_face_dde);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseRotationTranslationFilter(
    FUAI_FaceProcessor* model, int use_filter);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseFaceCapture(
    FUAI_FaceProcessor* model, int use_face_capture);

FUAI_CAPI_EXPORT extern void
FUAI_FaceProcessorSetFaceCaptureUseTongueExpression(
    FUAI_FaceProcessor* model, int face_capture_use_tongue);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseHairSegmenter(
    FUAI_FaceProcessor* model, int use_hair_segmenter);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetUseHeadSegmenter(
    FUAI_FaceProcessor* model, int use_head_segmenter);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetMinFaceRatio(
    FUAI_FaceProcessor* model, float min_face_ratio);

FUAI_CAPI_EXPORT extern void
FUAI_FaceProcessorSetFaceDetectorRetinaMinFaceRatio(FUAI_FaceProcessor* model,
                                                    float min_face_ratio);

FUAI_CAPI_EXPORT extern float FUAI_FaceProcessorGetFov(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetFov(FUAI_FaceProcessor* model,
                                                      float fov_degree);

FUAI_CAPI_EXPORT extern FUAI_FaceDetectMode FUAI_FaceProcessorGetDetectMode(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetDetectMode(
    FUAI_FaceProcessor* model, FUAI_FaceDetectMode mode);

FUAI_CAPI_EXPORT extern int FUAI_FaceProcessorGetDdeNumVertices(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern const int* FUAI_FaceProcessorGetDdeTriangles(
    const FUAI_FaceProcessor* model, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetDdeTexCoords(
    const FUAI_FaceProcessor* model, int* size);

FUAI_CAPI_EXPORT extern void FUAI_FaceProcessorSetFaceDdeShortEdgeFov(
    FUAI_FaceProcessor* model, float fov_degree);

FUAI_CAPI_EXPORT extern float FUAI_FaceProcessorGetFaceDdeShortEdgeFov(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern int FUAI_FaceProcessorGetFaceDdeNumVertices(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern const int* FUAI_FaceProcessorGetFaceDdeTriangles(
    const FUAI_FaceProcessor* model, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetFaceDdeTexCoords(
    const FUAI_FaceProcessor* model, int* size);

FUAI_CAPI_EXPORT extern int FUAI_FaceProcessorGetNumResults(
    const FUAI_FaceProcessor* model);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultRect(
    const FUAI_FaceProcessor* model, int index);

FUAI_CAPI_EXPORT extern int FUAI_FaceProcessorGetResultTrackId(
    const FUAI_FaceProcessor* model, int index);

FUAI_CAPI_EXPORT extern float FUAI_FaceProcessorGetResultConfidenceScore(
    const FUAI_FaceProcessor* model, int index);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultLandmarksExtra(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultPose(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultLeftEyebrowDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultRightEyebrowDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultLeftEyeDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultRightEyeDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultLeftIrisDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultRightIrisDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultUpperLipDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultLowerLipDenseLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultAllLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultLandmark3ds(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultExpression(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultRotation(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultTranslation(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultEyesRotation(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultArmeshVertices(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultTongueExpression(const FUAI_FaceProcessor* model,
                                            int index, int* size);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultHairMask(
    const FUAI_FaceProcessor* model, int index, int* mask_width,
    int* mask_height);

FUAI_CAPI_EXPORT extern const float* FUAI_FaceProcessorGetResultHeadMask(
    const FUAI_FaceProcessor* model, int index, int* mask_width,
    int* mask_height);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultPanoramaInfoLandmarks(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultPanoramaInfoWarpInfoSrcCenter(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern float
FUAI_FaceProcessorGetResultPanoramaInfoWarpInfoDstRectWidth(
    const FUAI_FaceProcessor* model, int index);

FUAI_CAPI_EXPORT extern float
FUAI_FaceProcessorGetResultPanoramaInfoWarpInfoDstRectHeight(
    const FUAI_FaceProcessor* model, int index);

FUAI_CAPI_EXPORT extern const float*
FUAI_FaceProcessorGetResultPanoramaInfoWarpInfoDstRectTopLeft(
    const FUAI_FaceProcessor* model, int index, int* size);

FUAI_CAPI_EXPORT extern float
FUAI_FaceProcessorGetResultPanoramaInfoWarpInfoShortEdgeFovDegree(
    const FUAI_FaceProcessor* model, int index);

// gl to dde

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeRotation(const float* gl,
                                                         int size, float* dde);

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeExpression(const float* gl,
                                                           int size,
                                                           float* dde);

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeTranslation(
    const float* gl_translation, int translation_size, const float* gl_rotation,
    int rotation_size, float* dde_translation);

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeMeshVertices(const float* gl,
                                                             int size,
                                                             float* dde);

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeMeshLandmark3ds(const float* gl,
                                                                int size,
                                                                float* dde);

FUAI_CAPI_EXPORT extern void FUAI_ConvertGLToDdeMeshTriangles(const int* gl,
                                                              int size,
                                                              int* dde);

#ifdef __cplusplus
}
#endif

#endif  // FUAI_C_C_API_H_
