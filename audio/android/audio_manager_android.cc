// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/audio/android/audio_manager_android.h"

#include "base/logging.h"
#include "media/audio/android/audio_track_output_android.h"
#include "media/audio/audio_manager.h"
#include "media/audio/fake_audio_input_stream.h"

// Maximum number of output streams that can be open simultaneously.
static const int kMaxOutputStreams = 10;

AudioManager* CreateAudioManager() {
  return new AudioManagerAndroid();
}

AudioManagerAndroid::AudioManagerAndroid() {
  SetMaxOutputStreamsAllowed(kMaxOutputStreams);
}

AudioManagerAndroid::~AudioManagerAndroid() {
  audio_thread_->Stop();
}

bool AudioManagerAndroid::HasAudioOutputDevices() {
  return true;
}

bool AudioManagerAndroid::HasAudioInputDevices() {
  return false;
}

void AudioManagerAndroid::MuteAll() {
  NOTIMPLEMENTED();
}

void AudioManagerAndroid::UnMuteAll() {
  NOTIMPLEMENTED();
}

AudioOutputStream* AudioManagerAndroid::MakeLinearOutputStream(
      const AudioParameters& params) {
  DCHECK_EQ(AudioParameters::AUDIO_PCM_LINEAR, params.format);
  return AudioTrackOutputStream::MakeStream(params);
}

AudioOutputStream* AudioManagerAndroid::MakeLowLatencyOutputStream(
      const AudioParameters& params) {
  DCHECK_EQ(AudioParameters::AUDIO_PCM_LOW_LATENCY, params.format);
  return AudioTrackOutputStream::MakeStream(params);
}

AudioInputStream* AudioManagerAndroid::MakeLinearInputStream(
    const AudioParameters& params, const std::string& device_id) {
  DCHECK_EQ(AudioParameters::AUDIO_PCM_LINEAR, params.format);
  return FakeAudioInputStream::MakeFakeStream(params);
}

AudioInputStream* AudioManagerAndroid::MakeLowLatencyInputStream(
    const AudioParameters& params, const std::string& device_id) {
  DCHECK_EQ(AudioParameters::AUDIO_PCM_LOW_LATENCY, params.format);
  return FakeAudioInputStream::MakeFakeStream(params);
}
