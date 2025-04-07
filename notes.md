Pour spécifier une adresse IP locale précise lors de la connexion à un serveur distant en utilisant des sockets en C, vous devez lier (bind) votre socket à l'adresse IP locale souhaitée avant d'appeler la fonction `connect()`. Voici comment vous pouvez le faire :

1. Créez le socket.
2. Utilisez `bind()` pour lier le socket à l'adresse IP locale souhaitée.
3. Appelez `connect()` pour vous connecter à l'adresse IP distante.

Voici un exemple de code qui illustre ces étapes :

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in local_addr, remote_addr;
    char *local_ip = "192.168.1.100"; // Adresse IP locale souhaitée
    char *remote_ip = "192.168.1.1";  // Adresse IP distante
    int remote_port = 12345;          // Port distant

    // Créer le socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse locale
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = inet_addr(local_ip);
    local_addr.sin_port = 0; // Le système choisira un port local libre

    // Lier le socket à l'adresse IP locale
    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse distante
    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr(remote_ip);
    remote_addr.sin_port = htons(remote_port);

    // Se connecter à l'adresse distante
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Envoyer des données
    char *message = "Hello, server!";
    if (send(sockfd, message, strlen(message), 0) < 0) {
        perror("send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Recevoir des données
    char buffer[1024];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);
    }

    if (bytes_received < 0) {
        perror("recv");
    }

    // Fermer le socket
    close(sockfd);

    return 0;
}
```

Dans cet exemple :
- `local_ip` est l'adresse IP locale que vous souhaitez utiliser pour la connexion.
- `remote_ip` et `remote_port` sont l'adresse IP et le port du serveur distant auquel vous souhaitez vous connecter.
- La fonction `bind()` est utilisée pour lier le socket à l'adresse IP locale spécifiée avant d'appeler `connect()`.

Assurez-vous que l'adresse IP locale que vous spécifiez est bien configurée sur votre machine et qu'elle est disponible pour être utilisée par votre application.

---

## Liens utiles
- [Unix Stack Exchange - Force programs to bind to an interface, not IP address](https://unix.stackexchange.com/questions/648718/force-programs-bind-to-an-interface-not-ip-address)
