###### Builder ######
FROM alpine:3.20 AS builder
RUN apk add --no-cache build-base linux-headers make
WORKDIR /src
COPY Makefile traffic_tunnel.c tunnel.c tunnel.h ./
RUN make all && install -m 0755 traffic_tunnel /traffic_tunnel

###### Runtime ######
FROM alpine:3.20
RUN apk add --no-cache bash curl net-tools iproute2
WORKDIR /app
COPY --from=builder /traffic_tunnel /app/traffic_tunnel
COPY client1.sh /app/client1.sh
RUN chmod +x /app/traffic_tunnel /app/client1.sh

CMD ["bash", "-lc", "tail -f /dev/null"]
