// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MOJO_SERVICES_MOJO_DECRYPTOR_H_
#define MEDIA_MOJO_SERVICES_MOJO_DECRYPTOR_H_

#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "media/base/decryptor.h"
#include "media/mojo/interfaces/decryptor.mojom.h"
#include "mojo/public/cpp/bindings/binding.h"

namespace media {

class MojoDecryptor : public Decryptor {
 public:
  explicit MojoDecryptor(interfaces::DecryptorPtr remote_decryptor);
  ~MojoDecryptor() final;

  // Decryptor implementation.
  void RegisterNewKeyCB(StreamType stream_type,
                        const NewKeyCB& key_added_cb) final;
  void Decrypt(StreamType stream_type,
               const scoped_refptr<DecoderBuffer>& encrypted,
               const DecryptCB& decrypt_cb) final;
  void CancelDecrypt(StreamType stream_type) final;
  void InitializeAudioDecoder(const AudioDecoderConfig& config,
                              const DecoderInitCB& init_cb) final;
  void InitializeVideoDecoder(const VideoDecoderConfig& config,
                              const DecoderInitCB& init_cb) final;
  void DecryptAndDecodeAudio(const scoped_refptr<DecoderBuffer>& encrypted,
                             const AudioDecodeCB& audio_decode_cb) final;
  void DecryptAndDecodeVideo(const scoped_refptr<DecoderBuffer>& encrypted,
                             const VideoDecodeCB& video_decode_cb) final;
  void ResetDecoder(StreamType stream_type) final;
  void DeinitializeDecoder(StreamType stream_type) final;

  // Called when keys have changed and an additional key is available.
  void OnKeyAdded();

 private:
  // Called when a buffer is decrypted.
  void OnBufferDecrypted(const DecryptCB& decrypt_cb,
                         interfaces::Decryptor::Status status,
                         interfaces::DecoderBufferPtr buffer);
  void OnAudioDecoded(const AudioDecodeCB& audio_decode_cb,
                      interfaces::Decryptor::Status status,
                      mojo::Array<interfaces::AudioBufferPtr> audio_buffers);
  void OnVideoDecoded(const VideoDecodeCB& video_decode_cb,
                      interfaces::Decryptor::Status status,
                      interfaces::VideoFramePtr video_frame);

  interfaces::DecryptorPtr remote_decryptor_;

  NewKeyCB new_audio_key_cb_;
  NewKeyCB new_video_key_cb_;

  base::WeakPtrFactory<MojoDecryptor> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MojoDecryptor);
};

}  // namespace media

#endif  // MEDIA_MOJO_SERVICES_MOJO_DECRYPTOR_H_
