# FileTransfer

## Description

This is a simple program to transfer files through network by using TCP on any port

The programs only works with IPv4 addresses

## Running the program

### Sending

```shell
./FileTransfer -s localIPv4 remoteIPv4 port filename
```

### Receiving

```shell
./FileTransfer -r localIPv4 remoteIPv4 port filename
```

### Important thing to know

Currently, the program can only receive if the sender is ready to send, otherwise you'll get an error.