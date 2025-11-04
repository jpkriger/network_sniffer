###### Builder: compila o binário do túnel ######
FROM alpine:3.20 AS builder
RUN apk add --no-cache build-base linux-headers make
WORKDIR /src
# Copiamos as fontes do túnel (reutilizando as do client1)
COPY ./client1/Makefile ./
COPY ./client1/traffic_tunnel.c ./
COPY ./client1/tunnel.c ./
COPY ./client1/tunnel.h ./
RUN make all && install -m 0755 traffic_tunnel /traffic_tunnel

###### Runtime: binário + ferramentas de rede ######
FROM alpine:3.20
RUN apk add --no-cache bash curl net-tools iproute2 iptables
WORKDIR /app
# Binário compilado
COPY --from=builder /traffic_tunnel /app/traffic_tunnel
# Script de configuração do servidor chamado pelo binário
COPY ./server.sh /app/server.sh
RUN chmod +x /app/traffic_tunnel /app/server.sh && mkdir -p /app/logs

# Mantém o container vivo quando necessário
CMD ["bash", "-lc", "tail -f /dev/null"]
