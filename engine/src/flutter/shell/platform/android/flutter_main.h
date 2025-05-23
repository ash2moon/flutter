// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_ANDROID_FLUTTER_MAIN_H_
#define FLUTTER_SHELL_PLATFORM_ANDROID_FLUTTER_MAIN_H_

#include <jni.h>

#include "flutter/common/settings.h"
#include "flutter/fml/macros.h"
#include "flutter/runtime/dart_service_isolate.h"
#include "flutter/shell/platform/android/android_rendering_selector.h"

namespace flutter {

class FlutterMain {
 public:
  ~FlutterMain();

  static bool Register(JNIEnv* env);

  static FlutterMain& Get();

  const flutter::Settings& GetSettings() const;
  flutter::AndroidRenderingAPI GetAndroidRenderingAPI();

  static AndroidRenderingAPI SelectedRenderingAPI(
      const flutter::Settings& settings,
      int api_level);

 private:
  const flutter::Settings settings_;
  const flutter::AndroidRenderingAPI android_rendering_api_;
  DartServiceIsolate::CallbackHandle vm_service_uri_callback_ = 0;

  explicit FlutterMain(const flutter::Settings& settings,
                       flutter::AndroidRenderingAPI android_rendering_api);

  static void Init(JNIEnv* env,
                   jclass clazz,
                   jobject context,
                   jobjectArray jargs,
                   jstring kernelPath,
                   jstring appStoragePath,
                   jstring engineCachesPath,
                   jlong initTimeMillis,
                   jint api_level);

  void SetupDartVMServiceUriCallback(JNIEnv* env);

  FML_DISALLOW_COPY_AND_ASSIGN(FlutterMain);
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_ANDROID_FLUTTER_MAIN_H_
