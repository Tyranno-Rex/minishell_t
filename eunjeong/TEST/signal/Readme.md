클러스터 맥 GUL Library의 readline 설치

GNU 라이브러리를 사용하려면 brew로 readline 라이브러리를 설치해주어야 한다.
brew install readline 로 라이브러리를 설치하고 brew info readline 를 터미널에 입력하면
readline 라이브러리가 어디에 위치하여 있는지 상세히 나와있다.

나중에 makefile할때 flag를 줘야한다.
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include

출처 : "https://velog.io/@sham/minishell%EA%B3%BC-readline"


*개인 윈도우 wsl 설치 및 사용*
sudo apt-get install -y libreadline-dev 윈도우 WSL 설치 방법
gcc signal.c -lreadline -> 으로 컴파일 해야함