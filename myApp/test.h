//
//  test.h
//  myApp
//
//  Created by chents on 2020/6/29.
//  Copyright © 2020 chents. All rights reserved.
//

#ifndef test_h
#define test_h

#include <stdio.h>
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"

void setStatus(int status);
void rec_audio(void);

#endif /* test_h */
