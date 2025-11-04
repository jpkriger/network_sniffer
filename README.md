# network_sniffer

Ambiente de laboratório com três containers Docker interligados em uma rede bridge customizada:

- proxy (172.31.66.1): ponto central para observação/registro de tráfego
- client1 (172.31.66.2): cliente que fará requisições periódicas ao Google
- client2 (172.31.66.3): cliente que fará requisições periódicas à Wikipedia

O arquivo `docker-compose.yml` define os serviços e a rede `labredes_net` (sub-rede 172.31.66.0/24). Cada container executa um script utilitário `traffic_tunnel` (placeholder) e, no caso dos clientes, um loop com `curl`.

## Estrutura

```
docker-compose.yml
proxy/
	├─ Dockerfile
	├─ traffic_tunnel
	└─ logs/
			└─ .gitkeep
client1/
	├─ Dockerfile
	├─ traffic_tunnel
	└─ client1.sh
client2/
	├─ Dockerfile
	├─ traffic_tunnel
	└─ client2.sh
```

## Pré‑requisitos

- Docker e Docker Compose (plugin) instalados e funcionando
- Permissão para rodar containers privilegiados

## Como executar

1) Construir e subir os serviços em segundo plano:

```bash
docker compose up --build -d
```

2) Verificar o status:

```bash
docker compose ps
```

3) Acompanhar logs (exemplos):

```bash
docker logs -f proxy
docker logs -f client1
docker logs -f client2
```

4) Conferir conectividade entre containers (opcional):

```bash
docker exec -it client1 ping -c 3 172.31.66.3   # ping client2
docker exec -it client2 ping -c 3 172.31.66.1   # ping proxy
```

5) Encerrar o ambiente:

```bash
docker compose down
```

## Notas

- O script `traffic_tunnel` atual é um placeholder para sua lógica de tunelamento/observação (iptables, pcap, etc.). Ele apenas registra eventos e (no `proxy`) grava em `/app/logs` (montado em `./proxy/logs`).
- Os scripts `client1.sh` e `client2.sh` são pontos de extensão para configurar rotas, iptables ou outras inicializações específicas de cada cliente.
