# Nginx Experiments

Some experiments on Nginx custom modules.

Start:

```
$ nix-shell

$ ngx-start
```

Check module is loaded:

```
$ nginx -V
```

Response:

```
$ curl localhost:8080 -i
HTTP/1.1 200 OK
Server: nginx/1.26.0
Date: Tue, 06 Aug 2024 18:47:23 GMT
Content-Type: text/plain
Content-Length: 13
Last-Modified: Thu, 01 Jan 1970 00:00:00 GMT
Connection: keep-alive

Hello, World!
```
