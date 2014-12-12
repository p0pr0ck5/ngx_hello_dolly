##Name

ngx_hello_dolly - A simple Hello World clone that emulates the Hello Dolly WordPress plugin

## Status

ngx_hello_dolly is stable and tested on Nginx 1.7.8.

## Description

This module functions like a simple 'hello world' module, except that it echoes a random line from the popular song Hello Dolly. This mimics the functionality of the [WordPress Hello Dolly plugin](https://wordpress.org/plugins/hello-dolly/). In action:

```sh
root@dev:~# curl localhost/hello
It's so nice to have you back where you belong
root@dev:~# curl localhost/hello
I can tell, Dolly
root@dev:~# curl localhost/hello
We feel the room swayin'
root@dev:~# curl localhost/hello
You're still goin' strong

```

## Installation

Installation is the same as any other Nginx module. No additional configuration parameters need are required at compile-time beyond `--add-module`. Example:

```sh
 # ./configure --add-module=/path/to/ngx_hello_dolly
```

## Configuration

Hello Dolly requires a single location configuration directive, `hello_dolly`, with no additional options. Requests that match the given location will receive a single line from Hello Dolly. Example:

```Nginx
location /hello {
	hello_dolly;
}
```

##License

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>

##Bugs

Please report bugs by creating a ticket with the GitHub issue tracker.
