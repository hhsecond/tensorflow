# Settings for Xtensa toolchain for hifimini_staging kernels.
# REQUIRED:
#   - RI2019.2 Toolkit (for xt-clang/xt-clang++).
#   - XTENSA_CORE: The name of the core to use, will cause a compiler exception
#                  without providing a core.

ifeq ($(TARGET), xtensa_hifimini_staging)
  TARGET_ARCH := xtensa_hifimini_staging

  PLATFORM_ARGS = \
    -DTF_LITE_MCU_DEBUG_LOG \
    --xtensa-core=$(XTENSA_CORE) \
    -mcoproc \
    -DXTENSA -DMAX_RFFT_PWR=9 -DMIN_RFFT_PWR=MAX_RFFT_PWR \
    -fdata-sections \
    -ffunction-sections \
    -fno-exceptions \
    -fno-unwind-tables \
    -fno-use-cxa-atexit \
    -fmessage-length=0 \
    -fno-threadsafe-statics

  TARGET_TOOLCHAIN_PREFIX := xt-
  CXX_TOOL := clang++
  CC_TOOL := clang

  CXXFLAGS += $(PLATFORM_ARGS)
  CCFLAGS += $(PLATFORM_ARGS)

  LDFLAGS += -Wl,-gc-sections

  TEST_SCRIPT := tensorflow/lite/micro/testing/test_xtensa_hifimini_staging_binary.sh

  # TODO(b/156962140): This manually maintained list of excluded examples is
  # quite error prone.
  EXCLUDED_EXAMPLE_TESTS := \
    tensorflow/lite/micro/examples/image_recognition_experimental/Makefile.inc \
    tensorflow/lite/micro/examples/magic_wand/Makefile.inc \
    tensorflow/lite/micro/examples/micro_speech/Makefile.inc \
    tensorflow/lite/micro/examples/network_tester/Makefile.inc \
    tensorflow/lite/micro/examples/person_detection/Makefile.inc \
    tensorflow/lite/micro/examples/person_detection_experimental/Makefile.inc
  MICRO_LITE_EXAMPLE_TESTS := $(filter-out $(EXCLUDED_EXAMPLE_TESTS), $(MICRO_LITE_EXAMPLE_TESTS))

endif
