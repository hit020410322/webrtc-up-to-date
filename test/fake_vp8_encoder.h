/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef TEST_FAKE_VP8_ENCODER_H_
#define TEST_FAKE_VP8_ENCODER_H_

#include <stddef.h>
#include <stdint.h>
#include <memory>
#include <vector>

#include "api/video/encoded_image.h"
#include "api/video_codecs/video_codec.h"
#include "api/video_codecs/video_encoder.h"
#include "api/video_codecs/vp8_temporal_layers.h"
#include "common_types.h"  // NOLINT(build/include)
#include "modules/include/module_common_types.h"
#include "modules/video_coding/include/video_codec_interface.h"
#include "rtc_base/sequenced_task_checker.h"
#include "rtc_base/thread_annotations.h"
#include "system_wrappers/include/clock.h"
#include "test/fake_encoder.h"

namespace webrtc {
namespace test {

class FakeVP8Encoder : public FakeEncoder {
 public:
  explicit FakeVP8Encoder(Clock* clock);
  virtual ~FakeVP8Encoder() = default;

  int32_t InitEncode(const VideoCodec* config,
                     int32_t number_of_cores,
                     size_t max_payload_size) override;

  int32_t Release() override;

  EncoderInfo GetEncoderInfo() const override;

 private:
  void SetupTemporalLayers(const VideoCodec& codec);
  void PopulateCodecSpecific(CodecSpecificInfo* codec_specific,
                             size_t size_bytes,
                             FrameType frame_type,
                             int stream_idx,
                             uint32_t timestamp);

  std::unique_ptr<RTPFragmentationHeader> EncodeHook(
      EncodedImage* encoded_image,
      CodecSpecificInfo* codec_specific) override;

  rtc::SequencedTaskChecker sequence_checker_;

  std::vector<std::unique_ptr<Vp8TemporalLayers>> temporal_layers_
      RTC_GUARDED_BY(sequence_checker_);
};

}  // namespace test
}  // namespace webrtc

#endif  // TEST_FAKE_VP8_ENCODER_H_
