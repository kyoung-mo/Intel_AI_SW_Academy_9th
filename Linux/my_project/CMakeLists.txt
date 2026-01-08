# 1. CMake 최소 버전 및 프로젝트 설정
cmake_minimum_required(VERSION 3.10)
project(MyMathProject)

# 2. 헤더 파일 경로 지정 (-I 옵션 역할)
# include 폴더를 컴파일러가 찾을 수 있게 등록합니다.
include_directories(${CMAKE_SOURCE_DIR}/include)

# 3. 출력 디렉토리 설정 (선택 사항)
# 빌드된 라이브러리는 build/lib, 실행 파일은 build/bin에 모으도록 설정
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# ==========================================
# 4. 정적 라이브러리 (.a) 생성
# ==========================================
# add_library(타겟이름 STATIC 소스파일)
add_library(mymath_static STATIC src/add.c src/substract.c)

# 실제 파일명이 libmymath.a가 되도록 이름을 지정
set_target_properties(mymath_static PROPERTIES OUTPUT_NAME "mymath")


# ==========================================
# 5. 공유 라이브러리 (.so) 생성
# ==========================================
# add_library(타겟이름 SHARED 소스파일)
# CMake는 SHARED 지정 시 자동으로 -fPIC 옵션을 적용합니다.
add_library(mymath_shared SHARED src/add.c src/substract.c)

# 실제 파일명이 libmymath.so가 되도록 이름을 지정
set_target_properties(mymath_shared PROPERTIES OUTPUT_NAME "mymath")


# ==========================================
# 6. 실행 파일 생성 및 링크
# ==========================================

# (1) 정적 라이브러리를 사용하는 실행 파일
add_executable(main_static_app app/main.c)
# target_link_libraries: 링커에게 라이브러리 연결 지시 (-L, -l 역할)
target_link_libraries(main_static_app mymath_static)

# (2) 공유 라이브러리를 사용하는 실행 파일
add_executable(main_shared_app app/main.c)
target_link_libraries(main_shared_app mymath_shared)