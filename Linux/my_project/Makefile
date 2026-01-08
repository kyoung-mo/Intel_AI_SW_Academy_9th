# 1. 컴파일러 및 옵션 설정
CC = gcc
# CFLAGS: -fPIC를 여기에 넣어서 모든 .o 파일이 공유 라이브러리용으로 만들어지게 합니다.
CFLAGS = -Wall -g -I./include -fPIC
LDFLAGS = -L./lib -lmymath

# 2. 디렉토리 설정
SRC_DIR = src
APP_DIR = app
LIB_DIR = lib
BIN_DIR = bin

# --------------------------------------------------------
# [핵심 변경 1] 소스 파일 및 오브젝트 파일 목록화
# --------------------------------------------------------
# 라이브러리에 포함될 소스 파일들을 나열합니다.
LIB_SRCS = $(SRC_DIR)/add.c $(SRC_DIR)/substract.c 

# 위 소스 파일 목록에서 .c를 .o로 바꾼 목록을 자동으로 생성합니다.
# 결과: src/mymath.o src/multiply.o
LIB_OBJS = $(LIB_SRCS:.c=.o)

# 3. 최종 타겟 파일 이름
LIB_STATIC = $(LIB_DIR)/libmymath.a
LIB_SHARED = $(LIB_DIR)/libmymath.so
EXE_STATIC = $(BIN_DIR)/main_static
EXE_SHARED = $(BIN_DIR)/main_shared

# 4. 기본 타겟
all: directories $(EXE_STATIC) $(EXE_SHARED)

# 5. 디렉토리 생성
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)

# --------------------------------------------------------
# 빌드 규칙
# --------------------------------------------------------

# [핵심 변경 2] 패턴 규칙 (Pattern Rule) 사용
# src 폴더의 모든 .c 파일을 .o 파일로 컴파일하는 공통 규칙입니다.
# 파일이 100개로 늘어나도 이 규칙 하나면 됩니다.
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# (1) 정적 라이브러리 (.a) 생성
# $^ : 의존성 목록 전체 (즉, src/mymath.o src/multiply.o 모두 포함)
$(LIB_STATIC): $(LIB_OBJS)
	ar rcs $@ $^

# (2) 공유 라이브러리 (.so) 생성
$(LIB_SHARED): $(LIB_OBJS)
	$(CC) -shared -o $@ $^

# (3) 실행 파일 생성 (정적 링크)
$(EXE_STATIC): $(APP_DIR)/main.c $(LIB_STATIC)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lmymath

# (4) 실행 파일 생성 (공유 링크)
$(EXE_SHARED): $(APP_DIR)/main.c $(LIB_SHARED)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lmymath

# --------------------------------------------------------
# 정리 (Clean)
# --------------------------------------------------------
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(LIB_DIR)/*
	rm -f $(BIN_DIR)/*

.PHONY: all clean directories