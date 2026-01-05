# WSL  설치

https://learn.microsoft.com/ko-kr/windows/wsl/install

- 윈도우11에서 설정
    
    `Linux용 윈도우 하위 시스템 체크`, `Virtual Machine Platform` 체크 → 재부팅
    
    <img width="415" height="841" alt="image" src="https://github.com/user-attachments/assets/0b0c3fd5-6f72-408c-84b3-7cca5940d444" />

    
- **WSL 업데이트:** 버전이 낮은 경우, 다음 명령어로 업데이트합니다.
    - PowerShell
    
    ```c
    **wsl --update
    
    업데이트 확인 중입니다.
    Linux용 Windows 하위 시스템 버전을 2.6.3(으)로 업데이트하는 중입니다.**
    ```
    
- 우분투 설치
    
    명령창에서설치
    
    ```c
     wsl --list --online
     
     wsl --install -d Ubuntu-24.04
    ```
    
    Username & Password 설정
    (ubuntupi/**1234**)
    
    ---
    
    - microsoft store에서 설치 ⇒ 24.04
        
        아래는 store를 통한 설치
        
        Microsoft Store → ubuntu 24.04 LTS 설치 → 열기 → Unix Username & Password 설정
        (ubuntupi/**1234**)
        
        VSCode 화면 왼쪽 아래 ><(Open a RemoteWindow) → WSL
        
        Open Folder → `/home/`ubuntupi/, OK
        
        <img width="1152" height="756" alt="image" src="https://github.com/user-attachments/assets/cd385acb-c182-4ab5-95f8-f7b30a47028b" />

        
- 네트워킹 설정

[power shell]

<img width="579" height="144" alt="image" src="https://github.com/user-attachments/assets/e342e72f-6673-49c5-8f0b-42988e569d64" />

[wsl2 전용 가상 네트워크 , windows가 가상 라우터 역할]

- wsl 리눅스는 이 네트워크 안에 있음

<img width="648" height="146" alt="image" src="https://github.com/user-attachments/assets/7629b067-6b64-4d55-9c7d-b433d9bf39c4" />


- 게이트웨이란?
    - 내 내트웨크를 벗어나 다른 네트워크로 나갈 때 반드시 거쳐야 하는 출구
    - 목적지가 내 서브넷 안이면 -> 직접 보냄
    - 목적지가 내 서브넷 밖이면 -> 게이트웨이에게 보냄

[wsl에서 ip addr]

<img width="921" height="288" alt="image" src="https://github.com/user-attachments/assets/da44e818-82c0-4166-b97f-459c8e9efc99" />


    WSL Settgings ⇒ mirror
    - window ip가 그대로 wsl에서 동작하도록 사용
        (지금은 해줄 필요 없음)
    
<img width="1602" height="520" alt="image" src="https://github.com/user-attachments/assets/a3700ee1-4870-4c29-afc1-8f224ed8309f" />

    
- wsl에 우분투 24.04가 설치되어 있고, 추가로 이 버전을 바탕으로 새로운 우분투를 설치하기
    
    ```c
    wsl --install Ubuntu-24.04 --name RasPI
    ```
    
    기존 설치된 것 제거하기
    
    ```c
    wsl --unregister ubuntu
    ```
    
    - 기존 이미지 제거
        
        ```bash
        wsl --unregister -d ubuntu
        
        다시 설치
        
        wsl --install -d Ubuntu-20.04
        ```
        
        기존 배포반 제거
        
        ```markdown
        wsl --unregister Ubuntu_Migrated
        ```


---

ls -al을 할 때 하드웨어를 접근할 수 있는 권한이 필요한데,
shell에서 권한을 가지고 있는 프로그램을 짜놨다.

리눅스에서는 pwd, ls 등을 shell이 지원을 해준다.
지금 쓰고 있는 shell은 bash라고 한다.

Cshell같은 경우는 기능이 별로 없다.
bash shall을 쓰는 경우 oh my bash 사용하는걸 추천

---

- oh my bash
    
    https://github.com/ohmybash/oh-my-bash
    
    ```c
    bash -c "$(curl -fsSL https://raw.githubusercontent.com/ohmybash/oh-my-bash/master/tools/install.sh)"
    ```
    
    OSH_THEME="lambda”
    

---

\\wsl.localhost\Apache6\home\apache6\apache6-sr-linux-sdk-evt1_sr_mini_v2\build-output\buildroot\images

- wsl에서 code를 실행하려면 윈도우에 있는 code의 위치를 알려주어야한다.
    
    그러기 위해선 .bashrc에 윈도우 경로를 알려주어야 한다. 
    
    ```c
    export PATH=/opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/snap/bin:/mnt/c/Users/hanki/AppData/Local/Programs/Microsoft\ VS\ Code/bin
    ```
    
- makefile이 폴더별로 있어서 빌드를 상황에 따라 하려면? ⇒ task.json
