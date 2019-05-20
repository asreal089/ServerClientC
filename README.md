# ServerClientC

Na pasta onde os arquivos se encontram é necessário compilar e rodar os dois arquivos. o
jeito de fazer isso é por meio dos seguintes passos:
1. Abrir terminal no diretório dos arquivos.
2. Rodar os comandos de compilação dos arquivos:
gcc -o client client.c -lpthread
gcc -o server server.c
3. Rodar comando para iniciar o server.
  ./server
4. Abrir outro terminal para executar comando que irá rodar os client
5. Executar comando que roda o client:
  ./client
