// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_MAC_VIDEOTOOLBOX_HELPERS_H_
#define MEDIA_BASE_MAC_VIDEOTOOLBOX_HELPERS_H_

#include "base/mac/scoped_cftyperef.h"
#include "media/base/mac/videotoolbox_glue.h"
#include "media/base/media_export.h"

namespace media {

namespace video_toolbox {

// Create a CFDictionaryRef with the given keys and values.
MEDIA_EXPORT base::ScopedCFTypeRef<CFDictionaryRef>
DictionaryWithKeysAndValues(CFTypeRef* keys, CFTypeRef* values, size_t size);

// Create a CFDictionaryRef with the given key and value.
MEDIA_EXPORT base::ScopedCFTypeRef<CFDictionaryRef> DictionaryWithKeyValue(
    CFTypeRef key,
    CFTypeRef value);

// Create a CFArrayRef with the given array of integers.
MEDIA_EXPORT base::ScopedCFTypeRef<CFArrayRef> ArrayWithIntegers(const int* v,
                                                                 size_t size);

// Create a CFArrayRef with the given int and float values.
MEDIA_EXPORT base::ScopedCFTypeRef<CFArrayRef> ArrayWithIntegerAndFloat(
    int int_val,
    float float_val);

// Copy a H.264 frame stored in a CM sample buffer to an Annex B buffer. Copies
// parameter sets for keyframes before the frame data as well.
MEDIA_EXPORT bool CopySampleBufferToAnnexBBuffer(
    CoreMediaGlue::CMSampleBufferRef sbuf,
    bool keyframe,
    std::string* annexb_buffer);
MEDIA_EXPORT bool CopySampleBufferToAnnexBBuffer(
    CoreMediaGlue::CMSampleBufferRef sbuf,
    bool keyframe,
    size_t annexb_buffer_size,
    char* annexb_buffer,
    size_t* used_buffer_size);

// Helper class to add session properties to a VTCompressionSessionRef.
class MEDIA_EXPORT SessionPropertySetter {
 public:
  SessionPropertySetter(
      base::ScopedCFTypeRef<VideoToolboxGlue::VTCompressionSessionRef> session,
      const VideoToolboxGlue* const glue);
  ~SessionPropertySetter();

  bool Set(CFStringRef key, int32_t value);
  bool Set(CFStringRef key, bool value);
  bool Set(CFStringRef key, CFStringRef value);
  bool Set(CFStringRef key, CFArrayRef value);

 private:
  base::ScopedCFTypeRef<VideoToolboxGlue::VTCompressionSessionRef> session_;
  const VideoToolboxGlue* glue_;
};

}  // namespace video_toolbox

}  // namespace media

#endif  // MEDIA_BASE_MAC_VIDEOTOOLBOX_HELPERS_H_
