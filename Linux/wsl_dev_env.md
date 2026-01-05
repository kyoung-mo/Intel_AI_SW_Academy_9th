# WSL에서 Native 개발환경 구축

## 1. 기본 개발 도구 및 필수 라이브러리 설치

먼저 Ubuntu 터미널을 열고 시스템을 업데이트한 뒤, 컴파일러(GCC), 빌드 도구(CMake), 그리고 MP4 재생을 위한 멀티미디어 라이브러리를 설치해야 합니다.

apt -> 의존성을 관리해주는 툴
update를 해줘야 패키지들 위치 등을 갱신해주는 역할

```c
# 패키지 목록 업데이트
sudo apt update && sudo apt upgrade -y

# 기본 빌드 도구 및 CMake 설치
sudo apt install -y build-essential cmake gdb pkg-config

# 멀티미디어 재생을 위한 라이브러리 (FFmpeg 및 SDL2)
# SDL2는 화면 출력 및 오디오 재생을 위해 널리 사용됩니다.
sudo apt install -y libsdl2-dev libavcodec-dev libavformat-dev libswscale-dev libavdevice-dev
```

## 2. VS Code 연동 및 확장 프로그램

WSL에서 VS Code를 사용하는 가장 효율적인 방법은 **Remote Development** 기능을 사용하는 것입니다.

- [ ]  wsl내에서 code .
- [ ]  profile → Native
1. **VS Code 설치**: Windows에 VS Code가 설치되어 있어야 합니다.
2. **확장 프로그램 설치**: VS Code 내에서 다음 항목들을 설치하세요.
    - **WSL**: Microsoft 제작 (필수)
    - **C/C++ Extension Pack**: Microsoft 제작 (IntelliSense 및 디버깅)
    - **CMake Tools**: Microsoft 제작 (CMake 빌드 자동화)
3. **연결**: WSL 터미널에서 프로젝트 폴더를 만든 후 `code .`을 입력하면 해당 폴더가 VS Code와 연결됩니다.


```bash
11:25:14 mo@DESKTOP-HMRIDMH project → ll
total 8.0K
-rw-r--r-- 1 mo mo   58 Jan  5 11:24 hello.c
drwxr-xr-x 3 mo mo 4.0K Jan  5 11:14 my_player/
11:25:17 mo@DESKTOP-HMRIDMH project → ls -al
total 16
drwxr-xr-x 3 mo mo 4096 Jan  5 11:24 .
drwxr-x--- 6 mo mo 4096 Jan  5 11:25 ..
-rw-r--r-- 1 mo mo   58 Jan  5 11:24 hello.c
drwxr-xr-x 3 mo mo 4096 Jan  5 11:14 my_player
```

declare? 헤더파일에 있음함수의 이름, 원형만 있는것
undefined? 라이브러리에 있음

ld : 링커 / 컴파일한 오브젝트 파일들을 모아 실행할때 사용하는것이 ld

gcc : 링크, 컴파일, 어셈블러도 만들어주는 역할?
- 링크, 컴파일, 어셈블러 변환? 뭔지 공부

cd . -> ?
cd .. -> ?
cd ... -> ?

- 실행 시 `./a.out`을 해주는 이유
    - `.`(현재 디렉터리)는 기본적으로 PATH에 포함되지 않기 때문이다.
  

`hello.c` , `hello.o` 

## 3. CMake 프로젝트 구조 만들기

간단한 MP4 재생기 프로젝트 구조를 예시로 들어보겠습니다.

### 프로젝트 폴더 구성

```c
my_player/
├── CMakeLists.txt
└── main.c
```

### CMakeLists.txt 작성

```c
mkdir my_player
cd my_player
```

FFmpeg와 SDL2 라이브러리를 찾아 연결해주는 설정입니다.

```c
cmake_minimum_required(VERSION 3.10)
project(MP4Player C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# PkgConfig 모듈 로드
find_package(PkgConfig REQUIRED)

# FFmpeg 및 SDL2 라이브러리 체크 (importlib 제거)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(SWSCALE REQUIRED libswscale)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SDL2 REQUIRED sdl2)

# 실행 파일 생성
add_executable(mp4_player main.c)

# 인클루드 경로 추가
target_include_directories(mp4_player PRIVATE 
    ${AVCODEC_INCLUDE_DIRS} 
    ${AVFORMAT_INCLUDE_DIRS} 
    ${SWSCALE_INCLUDE_DIRS} 
    ${AVUTIL_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
)

# 라이브러리 링크
target_link_libraries(mp4_player 
    ${AVCODEC_LIBRARIES} 
    ${AVFORMAT_LIBRARIES} 
    ${SWSCALE_LIBRARIES} 
    ${AVUTIL_LIBRARIES}
    ${SDL2_LIBRARIES}
)
```

## 4. MP4 재생 로직 (개요)

C 언어로 MP4를 직접 재생하려면 FFmpeg 라이브러리를 사용하여 **디코딩** 과정을 거쳐야 합니다.

**주요 단계:**

1. **avformat_open_input()**: MP4 파일을 엽니다.
2. **avcodec_find_decoder()**: 해당 파일의 코덱(H.264 등)을 찾습니다.
3. **av_read_frame()**: 파일에서 패킷을 읽어옵니다.
4. **avcodec_send_packet() / receive_frame()**: 압축된 데이터를 디코딩하여 원본 프레임을 얻습니다.
5. **SDL_UpdateTexture()**: 디코딩된 프레임을 화면에 출력합니다.

### MP4 재생기 예제 코드 (`main.c`)

```c
#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return -1;
    }

    // 1. FFmpeg 초기화 및 파일 열기
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0) return -1;

    // 스트림 정보 찾기
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) return -1;

    // 비디오 스트림 찾기
    int videoStream = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    if (videoStream == -1) return -1;

    // 2. 코덱 설정
    AVCodecParameters *pCodecParameters = pFormatCtx->streams[videoStream]->codecpar;
    const AVCodec *pCodec = avcodec_find_decoder(pCodecParameters->codec_id);
    AVCodecContext *pCodecCtx = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCtx, pCodecParameters);
    avcodec_open2(pCodecCtx, pCodec, NULL);

    // 3. SDL2 초기화 (윈도우 생성)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) return -1;
    SDL_Window *window = SDL_CreateWindow("WSL MP4 Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                          pCodecCtx->width, pCodecCtx->height, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, 
                                             pCodecCtx->width, pCodecCtx->height);

    // 4. 프레임 변환 설정 (YUV to RGB/etc)
    struct SwsContext *sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                                pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P,
                                                SWS_BILINEAR, NULL, NULL, NULL);

    AVPacket *pPacket = av_packet_alloc();
    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameYUV = av_frame_alloc();
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);

    // 5. 재생 루프 (디코딩 및 출력)
    while (av_read_frame(pFormatCtx, pPacket) >= 0) {
        if (pPacket->stream_index == videoStream) {
            if (avcodec_send_packet(pCodecCtx, pPacket) == 0) {
                while (avcodec_receive_frame(pCodecCtx, pFrame) == 0) {
                    // YUV 포맷으로 변환
                    sws_scale(sws_ctx, (uint8_t const *const *)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, 
                              pFrameYUV->data, pFrameYUV->linesize);

                    // SDL로 화면 업데이트
                    SDL_UpdateYUVTexture(texture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0],
                                         pFrameYUV->data[1], pFrameYUV->linesize[1],
                                         pFrameYUV->data[2], pFrameYUV->linesize[2]);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                }
            }
            SDL_Delay(33); // 간단한 FPS 제어 (약 30fps)
        }
        av_packet_unref(pPacket);
    }

    // 메모리 해제
    av_free(buffer);
    av_frame_free(&pFrame);
    av_frame_free(&pFrameYUV);
    avcodec_free_context(&pCodecCtx);
    avformat_close_input(&pFormatCtx);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

## 5. 빌드 및 실행

1. **빌드**: VS Code 하단의 `CMake: [Release]: Ready` 버튼을 누르거나 터미널에서 다음을 입력합니다.

```c
mkdir build
cd build
cmake ..
make
```

1. **실행**: WSL2는 이제 GUI 환경(WSLg)을 지원하므로, 별도의 설정 없이도 실행 시 창이 뜹니다.

```c
./mp4_player ../korea.mp4
```

- 중지는 `ps` 명령어를 통해 실행중인 파일 확인 후, `kill -9 [PID]`를 입력하여 강제 종료 가능

  - 리눅스 ps 명령어 정리
    - ps : process status
    - 현재 실행중인 프로세스 목록을 확인하는 명령어
    - 옵션은 `System V` / `BSD` 2 가지가 있음
          - System V : - 사용, `ps-ef`
          - BSD : - 없음 , `ps aux`, `ps u`

- `ps -ef`
    - `-e` : 모든 프로세스
    - `-f` : full format
 
- `ps aux`
    - a : 다른 사용자 포함
    - u : 사용자 기준 출력
    - x : 터미널 없는 프로세스
 
- `ps -u`
    - 현재 사용자 + 현재 터미널
    - 리소스 비율 표시
    - 특정 사용자 : `ps -u username`
    - 내가 실행한 것만 `ps -u`
 


### 6. 디버깅

1. .vscode/launch.json

```c
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch", // 설정 이름
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/cal", // 실행 파일 경로
            "args": ["1", "2", "add"], // <--- 이곳에 인자를 넣습니다.
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

<img width="963" height="775" alt="image" src="https://github.com/user-attachments/assets/6503b5fe-8b85-4f88-a4ef-97d0e6c55acc" />

`0A 00 00 00`으로 기록되는 이유? 리틀앤디언 방식 기록

### 7. 주의 사항 (WSL 환경)

- **WSLg 활성화**: Windows 11 또는 Windows 10(특정 빌드 이상)에서는 WSLg가 내장되어 있어 GUI 창이 자동으로 뜹니다. 만약 창이 뜨지 않는다면 `echo $DISPLAY`를 입력하여 환경 변수가 설정되어 있는지 확인하세요.
- **성능**: WSL 내에서 하드웨어 가속(GPU)을 사용하지 않는 경우 CPU 사용량이 높을 수 있습니다. 위 예제는 이해를 돕기 위한 **소프트웨어 디코딩** 방식입니다
