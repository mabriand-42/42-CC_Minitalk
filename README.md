# Minitalk #

[![mabriand's 42 minitalk Score](https://badge42.vercel.app/api/v2/cl3y8m48b020709mm5fyc36fq/project/2225086)](https://github.com/JaeSeoKim/badge42)

> The purpose of this project is to code a small data exchange program using UNIX signals.

## Description ##

The objective of this project is yo create a communication program in the form of a client and a
server.
The server launches first by printing its PID. The client then takes the server's PID and the string
 to send as parameters and sends it. Once the serverr has receptionned the string, it prints it.

As bonuses, the server acknoledges every message received by sending back a signal to the client and
 Unicode characters are supported!

<!-- ## Visuals ## -->

## Installation ##

`$ git clone https://github.com/mariebriand/42-CC_Minitalk.git` </br>
`$ cd 42-CC_Minitalk` </br>
`$ make` </br>

You will then end up with two executables: server and client. Split your terminal in two, and launch
each program, starting with server.

## Usage ##

`$ ./server` </br>
`$ ./client [server_PID] [string_to_send]` where server_PID is the first output of the server launch.
</br>

To run the tester: </br>

`$ cd tester` </br>
`$ sh minitalk_tester.sh` </br>

<!-- ## Support ## -->

## Roadmap ##

* Check for the right license (and document myself about open source licenses).
* Add a way to reach me for support.
* Generate and add a visual in the README.md
* Add the official subject from 42intra.

<!-- ## Conributing ## -->

## Authors and acknowledgement ##

The tester was made by [adbenoit-9](https://github.com/adbenoit-9) and cloned from her own project
repository.

<!-- ## License ## -->

## Project status ##

This project is finished, it has passed the 3 needed peer-corrections.

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
