/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MODULES_VIDEO_CODING_PACKET_H_
#define MODULES_VIDEO_CODING_PACKET_H_

#include <stddef.h>
#include <stdint.h>

#include "absl/types/optional.h"
#include "common_types.h"  // NOLINT(build/include)
#include "modules/include/module_common_types.h"
#include "modules/rtp_rtcp/source/rtp_generic_frame_descriptor.h"
#include "modules/rtp_rtcp/source/rtp_video_header.h"

namespace webrtc {

class VCMPacket {
 public:
  VCMPacket();

  VCMPacket(const uint8_t* ptr, size_t size, const WebRtcRTPHeader& rtpHeader);

  VCMPacket(const uint8_t* ptr,
            size_t size,
            const RTPHeader& rtp_header,
            const RTPVideoHeader& video_header,
            FrameType frame_type,
            int64_t ntp_time_ms);

  ~VCMPacket();

  VideoCodecType codec() const { return video_header.codec; }
  int width() const { return video_header.width; }
  int height() const { return video_header.height; }

  bool is_first_packet_in_frame() const {
    return video_header.is_first_packet_in_frame;
  }
  bool is_last_packet_in_frame() const {
    return video_header.is_last_packet_in_frame;
  }

  uint8_t payloadType;
  uint32_t timestamp;
  // NTP time of the capture time in local timebase in milliseconds.
  int64_t ntp_time_ms_;
  uint16_t seqNum;
  const uint8_t* dataPtr;
  size_t sizeBytes;
  bool markerBit;
  int timesNacked;

  FrameType frameType;

  VCMNaluCompleteness completeNALU;  // Default is kNaluIncomplete.
  bool insertStartCode;  // True if a start code should be inserted before this
                         // packet.
  RTPVideoHeader video_header;
  absl::optional<RtpGenericFrameDescriptor> generic_descriptor;

  int64_t receive_time_ms;
};

}  // namespace webrtc
#endif  // MODULES_VIDEO_CODING_PACKET_H_
