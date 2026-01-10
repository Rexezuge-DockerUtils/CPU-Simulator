FROM alpine:3 AS builder

RUN apk add --no-cache build-base

COPY Init.c Init.c

RUN gcc -O2 -Wall -Wextra -static -o Init.out Init.c

FROM scratch

COPY --from=builder /Init.out /usr/sbin/init

ENTRYPOINT ["/usr/sbin/init"]
