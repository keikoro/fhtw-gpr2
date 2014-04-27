# Notes

##TODO

- Makefile for gridserver, vehicleclient, griddisplay
- program gridserver
- program vehicleclient
- program griddisplay

##Sequence of actions

####gridserver
- calculates grid based on user input (getopt)
- waits for input from vehicle client

####vehicle client
- communicates an id (letters A-Z) for a new vehicle

####gridserver
- checks if id is valid (letters A-Z, with ASCII)
- checks if id is not yet taken by another vehicle client (position 0,0)
- if id is free, designates a position to the new vehicle (randomised at first, then count up or down the grid)
- communicates coordinates back to client

####client
- displays coordinates ("Registration OK. Start position: x,y.") (calculate -1,-1 for display)
- let user enter move ("Enter Move:") N,E,S,W for cardinal directions or T for termination

####gridserver
- if T was entered, set vehicle's position to 0,0


