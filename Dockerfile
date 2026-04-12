FROM debian:stable-slim

RUN apt-get update && apt-get install -y \
    gcc-avr \
    binutils-avr \
    avr-libc \
    make \
    # git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work

CMD ["/bin/bash"]
# CMD ["make"]

# to build:
## docker build -t teensy .

# run make (current dir as mounted volume)
## docker run -it --rm -v $(pwd):/work teensy
## make
# or
## docker run -it --rm -v $(pwd):/work teensy make