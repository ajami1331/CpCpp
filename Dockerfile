FROM gcc as builder

RUN apt update && apt install -y python3 python3-pip python3-dev

WORKDIR /app/

RUN pip3 install online-judge-verify-helper

COPY . .

RUN git config --global pull.rebase false

RUN oj-verify run