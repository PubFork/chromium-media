// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_DRM_STORAGE_H_
#define MEDIA_BASE_ANDROID_MEDIA_DRM_STORAGE_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "media/base/media_export.h"
#include "url/origin.h"

namespace media {

// Allows MediaDrmBridge to store and retrieve persistent data. This is needed
// for features like per-origin provisioning and persistent license support.
class MEDIA_EXPORT MediaDrmStorage {
 public:
  struct SessionData {
    SessionData(std::vector<uint8_t> key_set_id, std::string mime_type);
    ~SessionData();

    std::vector<uint8_t> key_set_id;
    std::string mime_type;
  };

  MediaDrmStorage();
  virtual ~MediaDrmStorage();

  // Callback to return whether the operation succeeded.
  using ResultCB = base::OnceCallback<void(bool)>;

  // Callback to return the result of LoadPersistentSession. |key_set_id| and
  // |mime_type| must be non-empty if |success| is true, and vice versa.
  using LoadPersistentSessionCB =
      base::OnceCallback<void(std::unique_ptr<SessionData> session_data)>;

  // Binds |this| to |origin|.
  // TODO(xhwang): The host of the service should know about the last committed
  // origin. We should solely use that origin, or check the |origin| against it.
  // TODO(xhwang): We should NOT use the real origin for provisioning. Use a
  // random origin ID instead.
  virtual void Initialize(const url::Origin& origin) = 0;

  // Called when MediaDrm is provisioned for the origin bound to |this|.
  // The implementation should keep track of the storing time so that the
  // information can be cleared based on selected time range (e.g. for clearing
  // browsing data).
  virtual void OnProvisioned(ResultCB result_cb) = 0;

  // Saves the persistent session info for |session_id| in the storage.
  // The implementation should keep track of the storing time so that the
  // information can be cleared based on selected time range (e.g. for clearing
  // browsing data).
  virtual void SavePersistentSession(const std::string& session_id,
                                     const SessionData& session_data,
                                     ResultCB result_cb) = 0;

  // Loads the persistent session info for |session_id| from the storage.
  virtual void LoadPersistentSession(
      const std::string& session_id,
      LoadPersistentSessionCB load_persistent_session_cb) = 0;

  // Removes the persistent session info for |session_id| from the storage.
  // If the session for |session_id| exists in the storage, it is removed.
  // Otherwise, this call is a no-op. In both cases, the result will be true.
  // The result will be false on other unexpected errors, e.g. connection error
  // to the storage backend.
  virtual void RemovePersistentSession(const std::string& session_id,
                                       ResultCB result_cb) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaDrmStorage);
};

using CreateStorageCB = base::Callback<std::unique_ptr<MediaDrmStorage>()>;

}  // namespace media

#endif  // MEDIA_BASE_ANDROID_MEDIA_DRM_STORAGE_H_
