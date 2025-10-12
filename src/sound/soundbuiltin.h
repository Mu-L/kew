/**
 * @file soundbuiltin.[h]
 * @brief Built-in audio backend implementation.
 *
 * Implements a simple internal audio output backend used when no
 * external library is available. Useful for portability and testing.
 */

#ifndef SOUNDBUILTIN_H
#define SOUNDBUILTIN_H

#include <miniaudio.h>

extern ma_data_source_vtable builtin_file_data_source_vtable;

void builtin_read_pcm_frames(ma_data_source *pDataSource, void *pFramesOut, ma_uint64 frameCount, ma_uint64 *pFramesRead);

void builtin_on_audio_frames(ma_device *pDevice, void *pFramesOut, const void *pFramesIn, ma_uint32 frameCount);

#endif
